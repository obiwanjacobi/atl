/*
 * Interrupt.h
 *
 * Created: 12-5-2015 19:49:53
 *  Author: Marc
 */


#ifndef PINCHANGEINTERRUPT_H_
#define PINCHANGEINTERRUPT_H_

#include "Port.h"

namespace ATL
{

/*
 *  A static class that lets you enable and disable interrupts easily.
 *
 *  Use The ISR(Xxx_vect) macro to implement your isr method.
 *  Avoid calling other methods/functions (make them inline) inside the isr.
 *  use the 'volatile' keyword on shared variables.
 */
class Interrupt
{
public:
    // Globally Enables interrupts (status reg).
    inline static void EnableAll(bool enable = true)
    {
        // enable ? sei() : cli(); => compile errors!
        if (enable)
        {
            sei();
        }
        else
        {
            cli();
        }
    }

    // Implement: ISR(PCINT?_vect){ ... }
    // PortA => PCINT0 .... PortD => PCINT3
    // specify pinFlags = 0 to turn of PinChange interrupts.
    inline static void EnablePinChange(const Ports portId, uint8_t pinFlags)
    {
        if (pinFlags == 0)
        {
            PCICR &= ~(1 << portId);
        }
        else
        {
            PCICR |= 1 << portId;

            if (portId < PortD)
            {
                // PCMSK0 + portId
                _SFR_MEM8(0x6B + (uint8_t)portId) = pinFlags;
            }
            else
            {
                PCMSK3 = pinFlags;
            }
        }
    }

    // Implement: ISR(TIMER?_OVF_vect){ ... }
    // counterTimerIndex 0..3 for timer0, timer1 etc.
    inline static void EnableCounterOverflow(const uint8_t counterTimerIndex, bool enable = true)
    {
        if (enable)
        {
            // TIMSK0
            _SFR_MEM8(0x6E + counterTimerIndex) |= 1;
        }
        else
        {
            // TIMSK0
            _SFR_MEM8(0x6E + counterTimerIndex) &= ~1;
        }
    }

    // Implement: ISR(TIMER?_COMPA_vect){ ... }
    // counterTimerIndex 0..3 for timer0, timer1 etc.
    inline static void EnableTimerCompareA(const uint8_t counterTimerIndex, bool enable = true)
    {
        if (enable)
        {
            // TIMSK0
            _SFR_MEM8(0x6E + counterTimerIndex) |= 2;
        }
        else
        {
            // TIMSK0
            _SFR_MEM8(0x6E + counterTimerIndex) &= ~2;
        }
    }

    // Implement: ISR(TIMER?_COMPB_vect){ ... }
    // counterTimerIndex 0..3 for timer0, timer1 etc.
    inline static void EnableTimerCompareB(const uint8_t counterTimerIndex, bool enable = true)
    {
        if (enable)
        {
            // TIMSK0
            _SFR_MEM8(0x6E + counterTimerIndex) |= 4;
        }
        else
        {
            // TIMSK0
            _SFR_MEM8(0x6E + counterTimerIndex) &= ~4;
        }
    }
private:
    Interrupt(){}
};

} // ATL

#endif /* PINCHANGEINTERRUPT_H_ */