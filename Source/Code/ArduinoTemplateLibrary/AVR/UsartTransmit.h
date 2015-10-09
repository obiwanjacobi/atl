#ifndef USARTTRANSMIT_H_
#define USARTTRANSMIT_H_

#include "UsartRegisters.h"
#include "../EnumScope.h"
#include "../Bit.h"

namespace ATL {
namespace MCU {

BeginEnum(UsartTransmitResult)
{
    Success,
    NotReady,
    // TODO: errors?
}
EndEnum(UsartTransmitResult)


template<const UsartIds::type UsartId>
class UsartTransmit
{
public:
    inline void setEnable(bool enable = true)
    {
        Bit<TXEN0>::Set(UsartRegisters<UsartId>::getUCSRB(), enable);
    }
    
    inline bool getEnable()
    {
        return Bit<TXEN0>::IsTrue(UsartRegisters<UsartId>::getUCSRB());
    }
    
    inline bool getIsComplete() const
    {
        return Bit<TXC0>::IsTrue(UsartRegisters<UsartId>::getUCSRA());
    }
    
    inline void WaitIsComplete() const
    {
        while(!getIsComplete());
    }
    
    inline bool getWantData() const
    {
        return Bit<UDRE0>::IsTrue(UsartRegisters<UsartId>::getUCSRA());
    }
    
    inline void WaitWantData() const
    {
        while(!getWantData());
    }

    inline void setEnableIsCompleteInterrupt(bool enable = true)
    {
        Bit<TXCIE0>::Set(UsartRegisters<UsartId>::getUCSRB(), enable);
    }    
    
    inline bool getEnableIsCompleteInterrupt()
    {
        return Bit<TXCIE0>::IsTrue(UsartRegisters<UsartId>::getUCSRB());
    }
  
    inline void setEnableWantDataInterrupt(bool enable = true)
    {
        Bit<UDRIE0>::Set(UsartRegisters<UsartId>::getUCSRB(), enable);
    }
    
    inline bool getEnableWantDataInterrupt()
    {
        return Bit<UDRIE0>::IsTrue(UsartRegisters<UsartId>::getUCSRB());
    }
  
    inline void Flush()
    {
        WaitWantData();
        // TODO: quicker way?
    }
    
    inline UsartTransmitResult Write(uint16_t data)
    {
        WaitWantData();
        WriteInternal(data);
        return UsartTransmitResult::Success;
    }
    
    inline bool TryWrite(uint16_t data, UsartTransmitResult& outResult)
    {
        if (!getWantData())
        {
            outResult = UsartTransmitResult::NotReady;
            return false;
        }
        
        WriteInternal(data);
        outResult = UsartTransmitResult::Success;
        return true;
    }
    
    inline UsartIds getUsartId() const
    {
        return UsartId;
    }
    
    inline void Close()
    {
        setEnableIsCompleteInterrupt(false);
        setEnableWantDataInterrupt(false);
        setEnable(false);
    }

protected:
    inline void WriteInternal(uint16_t data)
    {
        if (getIs9DataBits())
        {
            Bit<TXB80>::Set(UsartRegisters<UsartId>::getUCSRB(), (data & 0x0100) > 0);
        }
        
        UsartRegisters<UsartId>::getUDR() = (uint8_t)(data & 0xFF);
    }

    inline static bool getIs9DataBits()
    {
        return Bit<UCSZ02>::IsTrue(UsartRegisters<UsartId>::getUCSRB());
    }
};

}} // ATL::MCU

#endif /* USARTTRANSMIT_H_ */