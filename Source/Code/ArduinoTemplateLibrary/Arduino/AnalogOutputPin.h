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

#ifndef __ANALOGOUTPUTPIN_H__
#define __ANALOGOUTPUTPIN_H__

#include <stdint.h>
#include "DigitalOutputPin.h"

namespace ATL {

    /** Represents an analog output pin that supports PWM.
     *  The pin indicated by BoardPinNumber must support PWM (~).
     *  \tparam BoardPinNumber indicates the Arduino Board pin number of a PWM (~) pin.
     */
    template<const uint8_t BoardPinNumber>
    class AnalogOutputPin : public DigitalOutputPin<BoardPinNumber>
    {
    public:
        /**
         *  Writes a PWM value to an output pin.
         *  \param value is written to the output pin.
         */
        inline void Write(uint8_t value)
        {
            analogWrite(BoardPinNumber, value);
        }
    };

} // ATL

#endif //__ANALOGOUTPUTPIN_H__