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

template<const UsartIds::type UsartId, 
         typename TransmitT = UsartTransmit<UsartId>, 
         typename ReceiveT = UsartReceive<UsartId> >
class Usart
{
public:
    inline UsartIds getUsartId() const
    {
        return UsartId;
    }
    
    // TODO: OpenSync
    
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
    
    inline void Close()
    {
        Receive.Close();
        Transmit.Close();
        PowerReduction::setEnableUsart<UsartId>(false);
    }

    TransmitT Transmit;

    ReceiveT Receive;
};

}} // ATL::MCU

#endif /* USART_H_ */