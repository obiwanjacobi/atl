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

#ifndef USARTREGISTERS_H_
#define USARTREGISTERS_H_

#include <stdint.h>
#include "../EnumScope.h"

namespace ATL {
namespace MCU {

/** Indicates the available Usart ports.
 *  Availablilty is based on the presence of the UBRR register.
 */
BeginEnum(UsartIds)
{
    /** Usart 0 */
#ifdef UBRR0
    UsartId0,
#endif
    /** Usart 1 */
#ifdef UBRR1
    UsartId1
#endif
    //UsartId2,
    //UsartId3,
}
EndEnum(UsartIds)

/** The UsartRegisters class is a static class (that cannot be instantiated)
 *  that knows what the registers are for the various Usart ports.
 *  \tparam UsartId indicates the Usart port.
 */
template<const UsartIds::type UsartId>
class UsartRegisters
{
public:
    /** Usart Baud Rate Register
     *  \return Returns a reference to the register.
     */
    inline static volatile uint16_t& getUBRR()
    {
        return _SFR_MEM16(0xC4 + (UsartId * 0x08));
    }

    /** Usart Control and Status Register A
     *  \return Returns a reference to the register.
     */
    inline static volatile uint8_t& getUCSRA()
    {
        return _SFR_MEM8(0xC0 + (UsartId * 0x08));
    }

    /** Usart Control and Status Register B
     *  \return Returns a reference to the register.
     */
    inline static volatile uint8_t& getUCSRB()
    {
        return _SFR_MEM8(0xC1 + (UsartId * 0x08));
    }

    /** Usart Control and Status Register C
     *  \return Returns a reference to the register.
     */
    inline static volatile uint8_t& getUCSRC()
    {
        return _SFR_MEM8(0xC2 + (UsartId * 0x08));
    }
    
    /** Usart Data Register
     *  \return Returns a reference to the register.
     */
    inline static volatile uint8_t& getUDR()
    {
        return _SFR_MEM8(0xC6 + (UsartId * 0x08));
    }
};

}} // ATL::MCU

#endif /* USARTREGISTERS_H_ */