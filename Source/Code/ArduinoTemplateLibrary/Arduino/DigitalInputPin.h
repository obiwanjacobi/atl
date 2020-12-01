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

#ifndef __DIGITALINPUTPIN_H__
#define __DIGITALINPUTPIN_H__

#include <stdint.h>

namespace ATL {

    /** Represents a digital input pin.
     *  Initializes a BoardPinNumber to input.
     *  \tparam BoardPinNumber indicates the Arduino Board pin number.
     */
    template <const uint8_t BoardPinNumber>
    class DigitalInputPin
    {
    public:
        /** The ctor sets the pinMode to INPUT.
         */
        DigitalInputPin()
        {
            pinMode(BoardPinNumber, INPUT);
        }

        /** Reads the value from the BoardPinNumder.
         *  \return Returns the digital value read from the pin.
         */
        inline bool Read()
        {
            return digitalRead(BoardPinNumber);
        }

        /** Enables (true) or disables (false) the internal pull-up resistor the Arduino (MCU) has on digital input pins.
         *  \param enable is true by default.
         */
        inline void EnableInternalPullup(bool enable = true)
        {
            digitalWrite(BoardPinNumber, enable);
        }

        /** Gets the BoardPinNumber template parameter.
         *  \return Returns the BoardPinNumber template parameter.
         */
        inline uint8_t getPinNumber() const
        {
            return BoardPinNumber;
        }
    };

} // ATL

#endif //__DIGITALINPUTPIN_H__