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

#ifndef __TB6612FNG_DRIVERSERIAL3WIRE_H__
#define __TB6612FNG_DRIVERSERIAL3WIRE_H__

#include "DigitalOutputPin.h"
#include "AnalogOutputPin.h"

namespace ATL {

    /** This driver class writes to one port of a Toshiba TB6612FNG - a dual 1A motor driver/controller.
     *  Use two instances of this class to drive both channels of the chip.
     *  The class implements the IO routines for partially using the serial-3-wire shift registers. 
     *  The PWM is still connected directly to the Arduino (no support for PWM on Serial3Wire yet).
     *  \tparam BaseT is a Serial3WireOutput type and implements:
     *  `void Write(BitArrayT*)`
     *  \tparam In1Index is the bit index into BitArrayT of the In1 pin.
     *  \tparam In2Index is the bit index into BitArrayT of the In2 pin.
     *  \tparam Pwm_BoardPinNumber is the BoardPinNumber of an output for the PWM input that controls speed.
     *  The Pwm_BoardPinNumber must be a PWM (~) pin.
     *  \tparam BitArrayT is the bit array that stores all bits for the shift registers and is shared among all driver classes.
     */
    template<class BaseT,
        const uint8_t In1Index, const uint8_t In2Index, const uint8_t Pwm_BoardPinNumber,
        typename BitArrayT>
    class TB6612FNG_DriverSerial3Wire : public BaseT
    {
    public:
        /** Constructs the instance.
         */
        TB6612FNG_DriverSerial3Wire()
            : _dataReg(NULL)
        { }

        /** Stores the pointer to the dataReg and initializes the bit values this driver uses.
         *  \param dataReg is a pointer to the shared BitArray. Must not be NULL.
         */
        inline void setDataRegister(BitArrayT* dataReg)
        {
            if (dataReg == NULL) return;

            _dataReg = dataReg;

            _dataReg->Set(In1Index, false);
            _dataReg->Set(In2Index, false);

            WriteDataRegister();
        }

        /** Retrieves the data register BitArray this class uses.
         *  \return Returns NULL if `setDataRegister` was not called, or was called with NULL.
         */
        inline BitArrayT getDataRegister()
        {
            return _dataReg;
        }

        /** Sends the signals no the defined outputs.
         *  \param in1 is the state for in1.
         *  \param in2 is the state for in2.
         *  \param pwm is the value for the PWM.
         */
        void Send(bool in1, bool in2, uint8_t pwm)
        {
            _dataReg->Set(In1Index, in1);
            _dataReg->Set(In2Index, in2);
            WriteDataRegister();

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
        AnalogOutputPin<Pwm_BoardPinNumber> _pwm;
        BitArrayT* _dataReg;

        inline void WriteDataRegister()
        {
            BaseT::Write(_dataReg);
        }
    };

} // ATL

#endif //__TB6612FNG_DRIVERSERIAL3WIRE_H__