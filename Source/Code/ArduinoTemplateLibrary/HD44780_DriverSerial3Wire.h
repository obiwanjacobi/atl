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

#ifndef __HD44780_DRIVERSERIAL3WIRE_H__
#define __HD44780_DRIVERSERIAL3WIRE_H__

#include <stddef.h>
#include "HD44780_Profile.h"

namespace ATL {

    /** This class implements driver logic for the HD44780 LCD display controlled over a 3-wire serial connection.
     *  It assumes a write-only (5-R/W connected to GND) 4-bit mode (soft-mode).
     *  Note that in 4-bit mode only the high data lines (4-7) of the display are used.
     *  See also: http://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller
     *  The 3-wire serial connection can drive 74HC595 serial-in/parallel-out shift registers.
     *  It uses a BitArray to store all the bits that are clocked out to the shift registers. 
     *  This BitArray is shared amongst all 'devices' that share the shift-registers (which can be chained to 'any' length).
     *  So it is important to call the setDataRegister method BEFORE calling Initialize on the controller.
     *  See also Serial3WireOutput.
     *  \tparam BaseT is a Serial3WireOutput type that implements `void Write(BitArray<T>)`.
     *  \tparam RegSetIndex is the index in BitArrayT of the RS line to the display.
     *  \tparam EnableIndex is the index in BitArrayT of the enable line to the display.
     *  \tparam Data04Index is the index in BitArrayT of the D4 line to the display.
     *  \tparam Data15Index is the index in BitArrayT of the D5 line to the display.
     *  \tparam Data26Index is the index in BitArrayT of the D6 line to the display.
     *  \tparam Data37Index is the index in BitArrayT of the D7 line to the display.
     *  \tparam BitArrayT is the type that holds the serial bits.
     *  \tparam TimingProfileT is used to perform synchronous delays.
     *  It can be used to fine-tune the synchronous delays. See also HD44780_Profile.
     */
    template<class BaseT, const uint8_t RegSetIndex, const uint8_t EnableIndex,
        const uint8_t Data04Index, const uint8_t Data15Index, const uint8_t Data26Index, const uint8_t Data37Index,
        typename BitArrayT, typename TimingProfileT = HD44780_Profile>
    class HD44780_DriverSerial3Wire : public BaseT
    {
    public:
        /** Constructs a new instance.
         */
        HD44780_DriverSerial3Wire()
            : _dataReg(NULL)
        { }

        /** Stores the pointer to the dataReg and initializes the lines to the display (all low except enable).
         *  \param dataReg is a pointer to the shared BitArray. Must not be NULL.
         */
        inline void setDataRegister(BitArrayT* dataReg)
        {
            if (dataReg == NULL) return;

            _dataReg = dataReg;

            _dataReg->Set(RegSetIndex, false);
            _dataReg->Set(EnableIndex, true);
            _dataReg->Set(Data04Index, false);
            _dataReg->Set(Data15Index, false);
            _dataReg->Set(Data26Index, false);
            _dataReg->Set(Data37Index, false);

            WriteDataRegister();
        }

        /** Retrieves the data register BitArray this class uses.
         *  \return Returns NULL if `setDataRegister` was not called, or was called with NULL.
         */
        inline BitArrayT getDataRegister() const
        {
            return _dataReg;
        }

        /** Initializes the function set.
         *  Does nothing when `setDataRegister` was not called, or was called with NULL.
         */
        inline void Initialize()
        {
            if (_dataReg == NULL) return;

            Write4(0x02);
            WriteFunctionSet();
        }

        /** Writes a command to the LCD.
         *  pulls the RS LOW to indicate a command.
         *  Does nothing when `setDataRegister` was not called, or was called with NULL.
         *  \param cmd is the command to write.
         */
        inline void WriteCommand(uint8_t cmd)
        {
            if (_dataReg == NULL) return;

            _dataReg->Set(RegSetIndex, false);
            Write8(cmd);
        }

        /** Writes data to the LCD.
         *  Pulls the RS HIGH to indicate data.
         *  Does nothing when `setDataRegister` was not called, or was called with NULL.
         *  \param data is the data to write.
         */
        inline void WriteData(uint8_t data)
        {
            if (_dataReg == NULL) return;

            _dataReg->Set(RegSetIndex, true);
            Write8(data);
        }

    protected:
        /** \todo refactor to avoid code duplication with other HD44780 driver classes. */

        /** Writes 8-bits to the display.
         *  Does nothing when `setDataRegister` was not called, or was called with NULL.
         *  \param data is all 8 bits.
         */
        inline void Write8(uint8_t data)
        {
            Write4(data >> 4);
            Write4(data);
        }

        /** Writes 4-bits to the display.
         *  Pulses Enable to let the display read the data.
         *  Does nothing when `setDataRegister` was not called, or was called with NULL.
         *  \param data is all 4 bits in the lower nibble.
         */
        inline void Write4(uint8_t data)
        {
            if (_dataReg == NULL) return;

            _dataReg->Set(Data04Index, data & 0x01);
            _dataReg->Set(Data15Index, data & 0x02);
            _dataReg->Set(Data26Index, data & 0x04);
            _dataReg->Set(Data37Index, data & 0x08);
            WriteDataRegister();

            PulseEnable();
        }

    private:
        BitArrayT* _dataReg;

        inline void WriteDataRegister()
        {
            BaseT::Write(_dataReg);
        }

        inline void WriteFunctionSet()
        {
            // D7 D6 D5 D4 D3 D2 D1 D0
            //  0  0  1  0  1  0  0  0   => 0x28
            //      cmd 4b 2l  F  *  *
            // cmd = FunctionSet command bit
            // 4b = 4-bit data transfer (DL)
            // 2l = 2 line display (not single line) (N)
            // F = Font not available for multi-line.
            // * = don't care
            WriteCommand(0x28);
        }

        inline void PulseEnable()
        {
            _dataReg->Set(EnableIndex, false);
            WriteDataRegister();

            TimingProfileT::WaitPulseEnable();

            _dataReg->Set(EnableIndex, true);
            WriteDataRegister();
        }
    };

} // ATL

#endif //__HD44780_DRIVERSERIAL3WIRE_H__