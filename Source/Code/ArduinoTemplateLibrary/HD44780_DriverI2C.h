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

#ifndef __HD44780_DRIVERI2C_H__
#define __HD44780_DRIVERI2C_H__

#include "BitArray.h"
#include "HD44780_Profile.h"

namespace ATL {

    
    template<typename BaseT, typename TimingProfileT = HD44780_Profile>
    class HD44780_DriverI2C : public BaseT
    {
        /// \todo THIS IS SPECIFIC TO THE I2C-LCD BOARD!!!
        static const uint8_t RegSel_Index = 0;
        static const uint8_t ReadWrite_Index = 1;
        static const uint8_t Enable_Index = 2;
        static const uint8_t LED_Index = 3;
        static const uint8_t Data_Index = 4;

    public:
        /** Constructs a new instance and sets the Enable pin HIGH.
        */
        HD44780_DriverI2C()
        {
            _dataReg.Set(Enable_Index);
            _dataReg.Set(LED_Index);
        }

        /** Initializes the function set.
        */
        inline void Initialize()
        {
            Write4(0x02);
            WriteFunctionSet();
        }

        /** Writes a command to the LCD.
        *  Pulls the RS LOW to indicate a command.
        *  \param cmd is the command to write.
        */
        inline void WriteCommand(uint8_t cmd)
        {
            _dataReg.Reset(RegSel_Index);
            ClearDataRegisters();
            WriteToI2C();

            Write8(cmd);
        }

        /** Writes data to the LCD.
        *  Pulls the RS HIGH to indicate data.
        *  \param data is the data to write.
        */
        inline void WriteData(uint8_t data)
        {
            _dataReg.Set(RegSel_Index);
            ClearDataRegisters();
            WriteToI2C();

            Write8(data);
        }

        inline bool getEnableBacklight() const
        {
            return _dataReg.IsTrue(LED_Index);
        }

        inline void setEnableBacklight(bool value = true)
        {
            _dataReg.Set(LED_Index, value);
            ClearDataRegisters();
            WriteToI2C();
        }

    protected:
        /** Writes 8-bits to the display - MSB first.
        *  \param data is all 8 bits.
        */
        inline void Write8(uint8_t data)
        {
            Write4(data >> 4);
            Write4(data);
        }

        /** Writes 4-bits to the display.
        *  Pulses Enable to let the display read the data.
        *  \param data is all 4 bits in the lower nibble.
        */
        inline void Write4(uint8_t data)
        {
            _dataReg.Set(Data_Index, data, 4);
            WriteToI2C();

            PulseEnable();
        }

    private:
        BitArray<uint8_t> _dataReg;

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

        inline bool WriteToI2C()
        {
            return BaseT::Write(_dataReg);
        }

        inline void ClearDataRegisters()
        {
            _dataReg.Set(Data_Index, 0, 4);
        }

        inline void PulseEnable()
        {
            _dataReg.Reset(Enable_Index);
            WriteToI2C();

            TimingProfileT::WaitPulseEnable();
            
            _dataReg.Set(Enable_Index);
            WriteToI2C();
        }
    };

} // ATL

#endif //__HD44780_DRIVERI2C_H__
