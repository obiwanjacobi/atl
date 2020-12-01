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


#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <stdint.h>
#include <avr\io.h>
#include <interrupt.h>
#include "Port.h"

namespace ATL {
namespace MCU {

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
        // specify pinFlags = 0 to turn off PinChange interrupts.
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
                /*else
                {
                PCMSK3 = pinFlags;
                }*/
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
        Interrupt()
        { }
    };

}} // ATL::MCU

#endif /* __INTERRUPT_H__ */