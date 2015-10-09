#ifndef USARTREGISTERS_H_
#define USARTREGISTERS_H_

#include <stdint.h>
#include "../EnumScope.h"

namespace ATL {
namespace MCU {

BeginEnum(UsartIds)
{
#ifdef UBRR0
    UsartId0,
#endif
#ifdef UBRR1
    UsartId1
#endif
    //UsartId2,
    //UsartId3,
}
EndEnum(UsartIds)


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