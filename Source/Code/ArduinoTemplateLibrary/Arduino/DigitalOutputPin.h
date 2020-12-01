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

#ifndef __DIGITALOUTPUTPIN_H__
#define __DIGITALOUTPUTPIN_H__

#include <stdint.h>

namespace ATL {

    /** Represents a digital output pin.
     *  Initializes a BoardPinNumber to output.
     *  \tparam BoardPinNumber indicates the Arduino Board pin number.
     */
    template<const uint8_t BoardPinNumber>
    class DigitalOutputPin
    {
    public:
        /** The ctor sets the pinMode to OUTPUT.
         */
        DigitalOutputPin()
        {
            pinMode(BoardPinNumber, OUTPUT);
        }

        /** The ctor sets the pinMode to OUTPUT and writes the initialValue.
         *  \param initialValue the state of the pin to be writen.
         */
        DigitalOutputPin(bool initialValue)
        {
            pinMode(BoardPinNumber, OUTPUT);
            Write(initialValue);
        }

        /** Writes the value to the BoardPinNumder.
         *  \param value is the digital value to be written.
         */
        inline void Write(bool value) const
        {
            digitalWrite(BoardPinNumber, value);
        }

        /** Returns the value that was last written.
         *  Reads the value back from the output pin.
         *  \return The value the output pin currently has.
         */
        bool getValue() const
        {
            return digitalRead(BoardPinNumber);
        }

        /** Toggles (or inverts) the state of the output pin.
         */
        inline void Toggle()
        {
            Write(!getValue());
        }

        /** Returns the BoardPinNumber template parameter.
         */
        inline uint8_t getPinNumber() const
        {
            return BoardPinNumber;
        }
    };

} // ATL

#endif //__DIGITALOUTPUTPIN_H__