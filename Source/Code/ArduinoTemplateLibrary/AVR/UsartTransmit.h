/*
Arduino Template Library https://github.com/obiwanjacobi/atl
Written by Marc Jacobi
Copyright 2012-2015 All Rights Reserved

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef USARTTRANSMIT_H_
#define USARTTRANSMIT_H_

#include "UsartRegisters.h"
#include "../EnumScope.h"
#include "../Bit.h"

namespace ATL {
namespace MCU {

/** Indicates the result of a transmit operation.
 */
BeginEnum(UsartTransmitResult)
{
    /** Successful. */
    Success,
    /** No data was received or still busy. */
    NotReady,
}
EndEnum(UsartTransmitResult)

/** The UsartTransmit class implements the transmit functionality for a Usart port.
 *  \tparam UsartId indicates which Usart port this instance represents.
 */
template<const UsartIds::type UsartId>
class UsartTransmit
{
public:
    /** Enables (true) or disables (false) the transmitter.
     *  \param enable indicates the state.
     */
    inline void setEnable(bool enable = true)
    {
        Bit<TXEN0>::Set(UsartRegisters<UsartId>::getUCSRB(), enable);
    }
    
    /** Retrieves a value that indicates if the transmitter is enabled (true).
     *  \return Returns false when not enabled.
     */
    inline bool getEnable()
    {
        return Bit<TXEN0>::IsTrue(UsartRegisters<UsartId>::getUCSRB());
    }
    
    /** Retrieves a value indicating if transmission of data is complete.
     *  \return Returns true if the transmit operation is complete.
     */
    inline bool getIsComplete() const
    {
        return Bit<TXC0>::IsTrue(UsartRegisters<UsartId>::getUCSRA());
    }
    
    /** Blocks code execution until the transmit operation is complete.
     *  See also `getIsComplete()`.
     */
    inline void WaitIsComplete() const
    {
        while(!getIsComplete());
    }
    
    /** Retrieves a value indicating if another data byte is ready to be transmitted.
     *  This is different from the `getIsComplete()` in that transmission may still be taking place in the shift register,
     *  but the data register is empty and can accept new data.
     *  \return Returns true if the transmit operation can accept more data.
     */
    inline bool getAcceptData() const
    {
        return Bit<UDRE0>::IsTrue(UsartRegisters<UsartId>::getUCSRA());
    }
    
    /** Blocks code execution until the transmit operation can accept new data.
     *  See also `getAcceptData()`.
     */
    inline void WaitAcceptData() const
    {
        while(!getAcceptData());
    }

    /** Enables (true) or disables (false) the transmitter complete interrupt.
     *  When turning on interrupts you also have to implement the `ISR(USARTn_TX_vect)` interrupt handler.
     *  This interrupt is most useful when implementing half-duplex communication where after transmitting, 
     *  the receiver has to be switched on.
     *  \param enable indicates the state.
     */
    inline void setEnableIsCompleteInterrupt(bool enable = true)
    {
        Bit<TXCIE0>::Set(UsartRegisters<UsartId>::getUCSRB(), enable);
    }    
    
    /** Retrieves a value that indicates if the transmitter complete interrupt is enabled (true).
     *  \return Returns false when not enabled.
     */
    inline bool getEnableIsCompleteInterrupt()
    {
        return Bit<TXCIE0>::IsTrue(UsartRegisters<UsartId>::getUCSRB());
    }
  
    /** Enables (true) or disables (false) the transmitter accept data interrupt.
     *  When turning on interrupts you also have to implement the `ISR(USARTn_UDRE_vect)` interrupt handler.
     *  \param enable indicates the state.
     */
    inline void setEnableAcceptDataInterrupt(bool enable = true)
    {
        Bit<UDRIE0>::Set(UsartRegisters<UsartId>::getUCSRB(), enable);
    }
    
    /** Retrieves a value that indicates if the transmitter accept data interrupt is enabled (true).
     *  \return Returns false when not enabled.
     */
    inline bool getEnableAcceptDataInterrupt()
    {
        return Bit<UDRIE0>::IsTrue(UsartRegisters<UsartId>::getUCSRB());
    }
  
    /** Blocks execution until all data has been transmitted.
     *  See also `WaitAcceptData()`
     */
    inline void Flush()
    {
        WaitAcceptData();
        // TODO: quicker way?
    }
    
    /** Blocks until the transmitter accepts data and write data to the data register.
     *  \return Always returns `Success`.
     */
    inline UsartTransmitResult Write(uint16_t data)
    {
        WaitAcceptData();
        WriteInternal(data);
        return UsartTransmitResult::Success;
    }
    
    /** Write the data to the data register when the transmitter accepts data.
     *  When the transmitter is not ready to accept data, false is returned and the outResult is set to `NotReady`.
     *  \param data is the data to send.
     *  \param outResult is set with the result of the transmit operation.
     *  \return Returns true when successful.
     */
    inline bool TryWrite(uint16_t data, UsartTransmitResult& outResult)
    {
        if (!getAcceptData())
        {
            outResult = UsartTransmitResult::NotReady;
            return false;
        }
        
        WriteInternal(data);
        outResult = UsartTransmitResult::Success;
        return true;
    }
    
    /** Retrieves the Usart port identifier.
     *  \return Returns the UsartId template parameter.
     */
    inline UsartIds getUsartId() const
    {
        return UsartId;
    }
    
    /** Closes the Usart transmitter by disabling interrupts
     *  and the transmitter itself.
     */
    inline void Close()
    {
        setEnableIsCompleteInterrupt(false);
        setEnableAcceptDataInterrupt(false);
        setEnable(false);
    }

protected:
    /** Writes the (lower bits) data to the data register without error checking.
     *  Takes the use of 9-data bits into account.
     *  \param data is the data to write.
     */
    inline void WriteInternal(uint16_t data)
    {
        if (getIs9DataBits())
        {
            Bit<TXB80>::Set(UsartRegisters<UsartId>::getUCSRB(), (data & 0x0100) > 0);
        }
        
        UsartRegisters<UsartId>::getUDR() = (uint8_t)(data & 0xFF);
    }

    /** Indicates if 9-data bits is active.
     *  \return Returns true if 9-data bits are used.
     */
    inline static bool getIs9DataBits()
    {
        return Bit<UCSZ02>::IsTrue(UsartRegisters<UsartId>::getUCSRB());
    }
};

}} // ATL::MCU

#endif /* USARTTRANSMIT_H_ */