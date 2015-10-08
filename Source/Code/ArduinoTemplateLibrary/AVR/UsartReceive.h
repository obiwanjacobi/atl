#ifndef USARTRECEIVE_H_
#define USARTRECEIVE_H_

#include "UsartRegisters.h"
#include "../Bit.h"
#include "../EnumScope.h"

namespace ATL {
namespace MCU {

BeginEnum(UsartReceiveResult)
{
    Success,
    NotReady,
    DataOverRun,
    FrameError,
    ParityError
}
EndEnum(UsartReceiveResult)

template<const UsartIds::type UsartId>
class UsartReceive
{
public:
    inline void setEnable(bool enable = true)
    {
        Bit<RXEN0>::Set(UsartRegisters<UsartId>::getUCSRB(), enable);
    }
    
    inline bool getEnable()
    {
        return Bit<RXEN0>::IsTrue(UsartRegisters<UsartId>::getUCSRB());
    }
    
    inline void setEnableIsCompleteInterrupt(bool enable = true)
    {
        Bit<RXCIE0>::Set(UsartRegisters<UsartId>::getUCSRB(), enable);
    }
    
    inline bool getEnableIsCompleteInterrupt()
    {
        return Bit<RXCIE0>::IsTrue(UsartRegisters<UsartId>::getUCSRB());
    }
  
    inline bool getIsComplete() const
    {
        return Bit<RXC0>::IsTrue(UsartRegisters<UsartId>::getUCSRA());
    }
    
    inline void WaitIsComplete() const
    {
        while(!getIsComplete());
    }
    
    inline void Flush()
    {
        volatile uint8_t data;
        while(!getIsComplete())
        {
            data = UsartRegisters<UsartId>::getUDR();
        }
    }
    
    inline int16_t Read()
    {
        WaitIsComplete();
        return ReadInternal();
    }
    
    inline int16_t Read(UsartReceiveResult& outResult)
    {
        WaitIsComplete();
        outResult = getResult();
        return ReadInternal();
    }
    
    inline bool TryRead(uint16_t& outData, UsartReceiveResult& outResult)
    {
        if (!getIsComplete())
        {
            outResult = UsartReceiveResult::NotReady;
            return false;
        }
        
        outResult = getResult();
        outData = ReadInternal();
        return true;
    }
    
    // call before Read.
    inline bool getHasError() const
    {
        return (UsartRegisters<UsartId>::getUCSRA() & ((1 << FE0)|(1 << UPE0))) > 0;
        //return Bit<FE0>::IsTrue(UsartRegisters<UsartId>::getUCSRA()) ||
            //Bit<UPE0>::IsTrue(UsartRegisters<UsartId>::getUCSRA());
    }
    
    inline UsartIds getUsartId() const
    {
        return UsartId;
    }

    inline void Close()
    {
        setEnableIsCompleteInterrupt(false);
        setEnable(false);
    }

protected:
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

    inline static bool getIs9DataBits()
    {
        return Bit<UCSZ02>::IsTrue(UsartRegisters<UsartId>::getUCSRB());
    }
};

}} // ATL::MCU

#endif /* USARTRECEIVE_H_ */