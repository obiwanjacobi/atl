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

#ifndef USARTRECEIVE_H_
#define USARTRECEIVE_H_

#include "UsartRegisters.h"
#include "../Bit.h"
#include "../EnumScope.h"

namespace ATL {
namespace MCU {

/** Indicates the result of a receive operation.
 */
BeginEnum(UsartReceiveResult)
{
    /** Successful. */
    Success,
    /** No data was received or still busy. */
    NotReady,
    /** Too much data is arriving. */
    DataOverRun,
    /** The data bits could not be parsed correctly. */
    FrameError,
    /** Indicates interference or corruption of data. */
    ParityError
}
EndEnum(UsartReceiveResult)


/** The UsartReceive class implements the receive functionality for a Usart port.
 *  \tparam UsartId indicates which Usart port this instance represents.
 */
template<const UsartIds::type UsartId>
class UsartReceive
{
public:
    /** Enables (true) or disables (false) the receiver.
     *  \param enable indicates the state.
     */
    inline void setEnable(bool enable = true)
    {
        Bit<RXEN0>::Set(UsartRegisters<UsartId>::getUCSRB(), enable);
    }
    
    /** Retrieves a value that indicates if the receiver is enabled (true).
     *  \return Returns false when not enabled.
     */
    inline bool getEnable()
    {
        return Bit<RXEN0>::IsTrue(UsartRegisters<UsartId>::getUCSRB());
    }
    
    /** Enables (true) or disables (false) the receiver interrupt.
     *  When turning on interrupts you also have to implement the `ISR(USARTn_RX_vect)` interrupt handler.
     *  \param enable indicates the state.
     */
    inline void setEnableIsCompleteInterrupt(bool enable = true)
    {
        Bit<RXCIE0>::Set(UsartRegisters<UsartId>::getUCSRB(), enable);
    }
    
    /** Retrieves a value that indicates if the receiver interrupt is enabled (true).
     *  \return Returns false when not enabled.
     */
    inline bool getEnableIsCompleteInterrupt()
    {
        return Bit<RXCIE0>::IsTrue(UsartRegisters<UsartId>::getUCSRB());
    }
  
    /** Retrieves a value indicating if reception of data is complete.
     *  \return Returns true if the receive operation is complete.
     */
    inline bool getIsComplete() const
    {
        return Bit<RXC0>::IsTrue(UsartRegisters<UsartId>::getUCSRA());
    }
    
    /** Blocks code execution until the receive operation is complete.
     *  See also `getIsComplete()`.
     */
    inline void WaitIsComplete() const
    {
        while(!getIsComplete());
    }
    
    /** Discards all received data.
     */
    inline void Flush()
    {
        volatile uint8_t data;
        while(!getIsComplete())
        {
            data = UsartRegisters<UsartId>::getUDR();
        }
    }
    
    /** Wait for the receive operation to complete and returns the data.
     *  \return Returns -1 if no data is available.
     */
    inline int16_t Read()
    {
        WaitIsComplete();
        UsartReceiveResult result = getResult();
        int16_t data = ReadInternal();
        if (result != UsartReceiveResult::Success) return -1;
        return data;
    }
    
    /** Wait for the receive operation to complete and returns the data.
     *  \param outResult is set with the result of the receive operation.
     *  \return Returns -1 if no data is available.
     */
    inline int16_t Read(UsartReceiveResult& outResult)
    {
        WaitIsComplete();
        outResult = getResult();
        return ReadInternal();
    }
    
    /** Checks if the receive operation has completed in a non-blocking manner. 
     *  If not false is returned and the outResult is set to `NotReady`.
     *  \param outData will be set with the received data.
     *  \param outResult is set with the result of the receive operation.
     *  \return Returns false if no data is available.
     */
    inline bool TryRead(uint16_t& outData, UsartReceiveResult& outResult)
    {
        if (!getIsComplete())
        {
            outData = 0;
            outResult = UsartReceiveResult::NotReady;
            return false;
        }
        
        outResult = getResult();
        outData = ReadInternal();
        return true;
    }
    
    /** Gives an indication of a receive error has occurred.
     *  Call this method before calling any of the `(Try)Read()` methods.
     *  Note that `DataOverRun` is not considered an error by this method.
     *  \return Returns true if an error has occurred.
     */
    inline bool getHasError() const
    {
        return (UsartRegisters<UsartId>::getUCSRA() & ((1 << FE0)|(1 << UPE0))) > 0;
        //return Bit<FE0>::IsTrue(UsartRegisters<UsartId>::getUCSRA()) ||
            //Bit<UPE0>::IsTrue(UsartRegisters<UsartId>::getUCSRA());
    }
    
    /** Retrieves the Usart port identifier.
     *  \return Returns the UsartId template parameter.
     */
    inline UsartIds getUsartId() const
    {
        return UsartId;
    }

    /** Closes the Usart receiver by disabling interrupts
     *  and disabling the receiver.
     */
    inline void Close()
    {
        setEnableIsCompleteInterrupt(false);
        setEnable(false);
    }

protected:
    /** Reads the receive operation results.
     *  \return Returns a single result. `Success` is returned if no errors occurred.
     */
    inline UsartReceiveResult getResult() const
    {
        if (Bit<FE0>::IsTrue(UsartRegisters<UsartId>::getUCSRA()))
            return UsartReceiveResult::FrameError;
        
        if (Bit<UPE0>::IsTrue(UsartRegisters<UsartId>::getUCSRA()))
            return UsartReceiveResult::ParityError;
        
        if (Bit<DOR0>::IsTrue(UsartRegisters<UsartId>::getUCSRA()))
            return UsartReceiveResult::DataOverRun;
            
        return UsartReceiveResult::Success;
    }
    
    /** Reads the data from the data register.
     *  Includes the 9th bit if this is active.
     *  \return Returns the data without any error checking.
     */
    inline int16_t ReadInternal() const
    {
        int16_t data = 0;
        
        if (getIs9DataBits())
        {
            if (Bit<RXB80>::IsTrue(UsartRegisters<UsartId>::getUCSRB()))
            {
                data = 0x0100;
            }
        }
        
        data |= UsartRegisters<UsartId>::getUDR();
        return data;
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

#endif /* USARTRECEIVE_H_ */