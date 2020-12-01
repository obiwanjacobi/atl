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

#ifndef USART_H_
#define USART_H_

#include <stdint.h>
#include <avr/io.h>
#include "UsartConfig.h"
#include "UsartRegisters.h"
#include "UsartTransmit.h"
#include "UsartReceive.h"
#include "PowerReduction.h"

namespace ATL {
namespace MCU {

/** The Usart class is the basis for the Usart ports on the AVR MCU.
 *  \tparam: UsartId is the Usart port this class represents.
 *  \tparam: TransmitT is the class used for transmission (TX). 
 *  By default it is the UsartTransmit template class but the UsartOutputStream class can also be used.
 *  \tparam: ReceiveT is the class used for reception (RX).
 *  By default it is the UsartReceive template class but the UsartInputStream class can also be used.
 */
template<const UsartIds::type UsartId, 
         typename TransmitT = UsartTransmit<UsartId>, 
         typename ReceiveT = UsartReceive<UsartId> >
class Usart
{
public:
    /** Gets the UsartId this instance represents.
     *  Returns the UsartId template parameter.
     */
    inline UsartIds getUsartId() const
    {
        return UsartId;
    }
    
    /// \todo TODO: OpenSync
    
    /** Configures the Usart for asynchronous communication.
     *  The Usart is enabled in the Power Reduction Register.
     *  Receiver and/or Transmitter are not enabled. No interrupts are enabled.
     *  \param config is an instance of UsartConfig information used to open the device.
     *  \return Returns true when successful. Only accepts async config.
     */
    inline bool OpenAsync(const UsartConfig& config)
    {
        UsartModes mode = config.getMode();
        
        if (mode != UsartModes::Async &&
            mode != UsartModes::AsyncDoubleSpeed)
        {
            return false;
        }
        
        PowerReduction::setEnableUsart<UsartId>(true);
        
        UsartRegisters<UsartId>::getUBRR() = config.getUBRR();
        UsartRegisters<UsartId>::getUCSRA() = config.getUCSRA();
        UsartRegisters<UsartId>::getUCSRB() = config.getUCSRB();
        UsartRegisters<UsartId>::getUCSRC() = config.getUCSRC();
        return true;
    }
    
    /** Closes the Usart by closing the transmitter and receiver.
     *  Clears buffer, disables interrupts and disables the receiver and transmitter.
     *  Disables the Usart in the Power Reduction Register.
     */
    inline void Close()
    {
        Receive.Close();
        Transmit.Close();
        PowerReduction::setEnableUsart<UsartId>(false);
    }

    /** The instance of the Transmit class.
     */
    TransmitT Transmit;

    /** The instance of the Receive class.
     */
    ReceiveT Receive;
};

}} // ATL::MCU

#endif /* USART_H_ */