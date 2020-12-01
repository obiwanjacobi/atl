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

#ifndef __TB6612FNG_DRIVER_H__
#define __TB6612FNG_DRIVER_H__

#include "DigitalOutputPin.h"
#include "AnalogOutputPin.h"

namespace ATL {

    /** This driver class writes to one port of a Toshiba TB6612FNG - a dual 1A motor driver/controller.
     *  Use two instances of this class to drive both channels of the chip.
     *  The class implements the IO routines for direct connection onto an Arduino. 
     *  \tparam In1_BoardPinNumber is the BoardPinNumber of an output that is connected to input 1 of the chip.
     *  \tparam In2_BoardPinNumber is the BoardPinNumber of an output that is connected to input 2 of the chip.
     *  \tparam Pwm_BoardPinNumber is the BoardPinNumber of an output for the PWM input that controls speed. 
     *  The Pwm_BoardPinNumber must be a PWM (~) pin.
     */
    template<const uint8_t In1_BoardPinNumber, const uint8_t In2_BoardPinNumber, const uint8_t Pwm_BoardPinNumber>
    class TB6612FNG_Driver
    {
    public:
        /** Sends the signals no the defined outputs.
         *  \param in1 is the state for in1.
         *  \param in2 is the state for in2.
         *  \param pwm is the value for the PWM.
         */
        void Send(bool in1, bool in2, uint8_t pwm)
        {
            _in1.Write(in1);
            _in2.Write(in2);

            if (pwm > 0)
            {
                _pwm.Write(pwm);
            }
            else
            {
                _pwm.Write(true);
            }
        }

    private:
        DigitalOutputPin<In1_BoardPinNumber> _in1;
        DigitalOutputPin<In2_BoardPinNumber> _in2;
        AnalogOutputPin<Pwm_BoardPinNumber> _pwm;
    };

} // ATL

#endif //__TB6612FNG_DRIVER_H__