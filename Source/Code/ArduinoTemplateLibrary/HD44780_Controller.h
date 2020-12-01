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

#ifndef __HD44780_CONTROLLER_H__
#define __HD44780_CONTROLLER_H__

#include "HD44780_Profile.h"
#include "BitArray.h"

namespace ATL {


    /** Implements the communication protocol for a HD44780 compatible LCD character display.
     *  \tparam BaseT represents a HD44780_Driver that interfaces with the actual device. 
     *  It implements: `void Write4(uint8_t)`, `void WriteCommand(uint8_t)` and void Initialize()`.
     *  \tparam TimingProfileT is used to perform synchronous delays. 
     *  It can be used to fine-tune the synchronous delays. See also HD44780_Profile.
     */
    template<class BaseT, typename TimingProfileT = HD44780_Profile>
    class HD44780_Controller : public BaseT
    {
    public:

        /** Enumerates the horizontal direction.
         */
        enum Direction
        {
            /** To the Left. */
            Left,
            /** To the Right. */
            Right
        };

        /**
         *  Constructs the instance.
         */
        HD44780_Controller()
            : _registers(0)
        { }

        /** Performs the LCD initialization sequence - only when full is true.
         *  Clears the display and resets cursor position.
         *  \param full indicates a full initialization sequence.
         */
        inline void Initialize(bool full = true)
        {
            if (full)
            {
                TimingProfileT::WaitPowerUp();
                // Follow the initialization sequence on page 46 (figure 24) - HD44780 data sheet
                BaseT::Write4(0x03);
                TimingProfileT::WaitInitializeLong();
                BaseT::Write4(0x03);
                TimingProfileT::WaitInitialize();
                BaseT::Write4(0x03);
                TimingProfileT::WaitInitializeShort();
                BaseT::Initialize();
            }

            ClearDisplay();
            ReturnHome();
        }

        /** Sends a command that clears the display.
         */
        inline void ClearDisplay()
        {
            BaseT::WriteCommand(ClearDisplayCommand);
            TimingProfileT::WaitForCommandLong();
        }

        /** Sends a command that resets the cursor position.
         */
        inline void ReturnHome()
        {
            BaseT::WriteCommand(ReturnHomeCommand);
            TimingProfileT::WaitForCommandLong();
        }

        /** Returns the value for blinking the cursor.
         *  \return Returns true if the cursor is blinking.
         */
        inline bool getEnableBlink() const
        {
            return _registers.IsTrue(Blink);
        }

        /** Sets the value for blinking the cursor.
         *  \param value indicates if the cursor blinks.
         */
        inline void setEnableBlink(bool value = true)
        {
            _registers.Set(Blink, value);
            WriteDisplayControl();
        }

        /** Returns the value for displaying the cursor.
         *  \return Returns an indication if the cursor is displayed.
         */
        inline bool getEnableCursor() const
        {
            return _registers.IsTrue(Cursor);
        }

        /** Sets the value for displaying the cursor.
         *  \param value indicates if the cursor is displayed.
         */
        inline void setEnableCursor(bool value = true)
        {
            _registers.Set(Cursor, value);
            WriteDisplayControl();
        }

        /** Returns the value for enabling the display.
         *  \return Returns an indication if the display is on.
         */
        inline bool getEnableDisplay() const
        {
            return _registers.IsTrue(Display);
        }

        /** Sets the value for enabling the display.
         *  \param value indicates if the display is on.
         */
        inline void setEnableDisplay(bool value = true)
        {
            _registers.Set(Display, value);
            WriteDisplayControl();
        }

        /** Optimal way to set values for enable display, enable cursor and blink cursor in one call to LCD.
         *  \param enableDisplay indicates if the display is on.
         *  \param enableCursor indicates if the cursor is displayed.
         *  \param enableBlink indicates if the cursor blinks.
         */
        inline void SetDisplayControl(bool enableDisplay, bool enableCursor, bool enableBlink)
        {
            _registers.Set(Blink, enableBlink);
            _registers.Set(Cursor, enableCursor);
            _registers.Set(Display, enableDisplay);
            WriteDisplayControl();
        }

        /** Retrieves the direction of text entry.
         *  \return Returns the horizontal direction of text entry.
         */
        inline Direction getEntryCursorDirection() const
        {
            return _registers.IsFalse(EntryCursorDirection);
        }

        /** Sends a command to set the direction of text entry.
         *  \param dir is the horizontal direction of text entry.
         */
        inline void setEntryCursorDirection(Direction dir = Left)
        {
            _registers.Set(EntryCursorDirection, dir == Left);
            WriteEntryMode();
        }

        /** Retrieves an indication if the display shifts.
         *  \return Returns an indication if the display shifts.
         */
        inline bool getEnableDisplayShift() const
        {
            return _registers.IsTrue(EntryDisplayShift);
        }

        /** Sends a command to set an indication if the display shifts.
         *  \param value is an indication if the display shifts.
         */
        inline void setEnableDisplayShift(bool value = true)
        {
            _registers.Set(EntryDisplayShift, value);
            WriteEntryMode();
        }

        /** Sends one command that sets both the text entry direction as well as the enable shift value.
         *  \param entryCursorDirection is the horizontal direction of text entry.
         *  \param enableDisplayShift is an indication if the display shifts.
         */
        inline void SetEntryMode(Direction entryCursorDirection, bool enableDisplayShift)
        {
            _registers.Set(EntryCursorDirection, entryCursorDirection == Left);
            _registers.Set(EntryDisplayShift, enableDisplayShift);
            WriteEntryMode();
        }

    protected:
        /** Send a command that sets the cursor position.
         *  \param address is the memory address in the display.
         */
        inline void WriteDisplayAddress(uint8_t address)
        {
            BaseT::WriteCommand(address | SetDdRamAddressCommand);
            TimingProfileT::WaitForCommand();
        }

        /** Send a command that sets the character address (custom chars).
         *  \param address is the memory address in the display.
         */
        inline void WriteCharacterAddress(uint8_t address)
        {
            BaseT::WriteCommand((address & 0x3F) | SetCgRamAddressCommand);
            TimingProfileT::WaitForCommand();
        }

        /** Sends a command to shift the display in a horizontal direction.
         *  \param shiftDisplay an indication to shift the display.
         *  \param shiftDir indicates the horizontal direction.
         */
        inline void WriteCursorShift(bool shiftDisplay, Direction shiftDir)
        {
            uint8_t cmd = ShiftCursorCommand;
            cmd |= shiftDisplay ? 0x08 : 0;
            cmd |= shiftDir == Right ? 0x04 : 0;

            BaseT::WriteCommand(cmd);
            TimingProfileT::WaitForCommand();
        }

        /** Enumerates the registers used by this class.
         *  These are available to derived classes.
         */
        enum Registers
        {
            /** Display Control: blink on/off. */
            Blink,
            /** Display Control: cursor on/off. */
            Cursor,
            /** Display Control: display on/off. */
            Display,
            /** Entry Mode: entry shift on/off. */
            EntryDisplayShift,
            /** Entry Mode: entry direction left/right. */
            EntryCursorDirection,
        };

        /** Sets the value for the specified reg.
         *  Only sets the value in memory - not in the display!
         *  \param reg one of the registers.
         *  \param value is the value to write.
         */
        inline void setRegister(Registers reg, bool value)
        {
            _registers.Set(reg, value);
        }

        /** Retrieves the value for a reg from memory (not the display).
         *  \param reg one of the registers.
         *  \return Returns value of the specified register.
         */
        inline bool getRegister(Registers reg)
        {
            return _registers.IsTrue(reg);
        }

    private:
        enum RegistersMasks
        {
            // bit0-2
            DisplayControlMask = 0x07,
            // bit3-4
            EntryModeMask = 0x18,
        };

        BitArray<uint8_t> _registers;

        enum Commands
        {
            ClearDisplayCommand = 1 << 0,
            ReturnHomeCommand = 1 << 1,
            SetEntryModeCommand = 1 << 2,
            DisplayControlCommand = 1 << 3,
            ShiftCursorCommand = 1 << 4,
            //FunctionSetCommand = 1 << 5,
            SetCgRamAddressCommand = 1 << 6,
            SetDdRamAddressCommand = 1 << 7
        };

        inline void WriteDisplayControl()
        {
            BaseT::WriteCommand((_registers & DisplayControlMask) | DisplayControlCommand);
            TimingProfileT::WaitForCommand();
        }

        inline void WriteEntryMode()
        {
            // shift down the 3 display-control bits
            BaseT::WriteCommand((_registers & EntryModeMask) >> 3 | SetEntryModeCommand);
            TimingProfileT::WaitForCommand();
        }
    };

} // ATL

#endif //__HD44780_CONTROLLER_H__
