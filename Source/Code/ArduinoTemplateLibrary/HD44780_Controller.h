/*  
	Arduino Template Library http://atl.codeplex.com
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

/*
	BaseT is used as a base class and implements:
		void [HD44780_Driver]Write4(unsigned char);
		void [HD44780_Driver]WriteCommand(unsigned char);
		void [HD44780_Driver]Initialize();
	TimingProfileT is used to perform synchronous delays. See also HD44780_Profile.

	The Controller class implements the protocol of communicating with the LCD display.
*/
template<class BaseT, typename TimingProfileT = HD44780_Profile>
class HD44780_Controller : public BaseT
{
public:

	/*
		Direction (horizontal).
	 */
	enum Direction
	{
		Left,
		Right
	};

	/*
		Constructs the instance.
	 */
	HD44780_Controller() 
		: _registers(0)
	{}

	/*
		Performs the LCD initialization sequence - only when full is true.
		Clears the display and resets cursor position.
	 */
	void Initialize(bool full)
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

	/*
		Clears the display.
	 */
	inline void ClearDisplay()
	{
		BaseT::WriteCommand(ClearDisplayCommand);
		TimingProfileT::WaitForCommandLong();
	}

	/*
		Resets the cursor position.
	 */
	inline void ReturnHome()
	{
		BaseT::WriteCommand(ReturnHomeCommand);
		TimingProfileT::WaitForCommandLong();
	}

	/*
		Returns the value for blinking the cursor.
	 */
	inline bool getEnableBlink() const
	{
		return _registers.IsTrue(Blink);
	}

	/*
		Sets the value for blinking the cursor.
	 */
	inline void setEnableBlink(bool value = true)
	{
		_registers.Set(Blink, value);
		WriteDisplayControl();
	}

	/*
		Returns the value for displaying the cursor.
	 */
	inline bool getEnableCursor() const
	{
		return _registers.IsTrue(Cursor);
	}

	/*
		Sets the value for displaying the cursor.
	 */
	inline void setEnableCursor(bool value = true)
	{
		_registers.Set(Cursor, value);
		WriteDisplayControl();
	}

	/*
		Returns the value for enabling the display.
	 */
	inline bool getEnableDisplay() const
	{
		return _registers.IsTrue(Display);
	}

	/*
		Sets the value for enabling the display.
	 */
	inline void setEnableDisplay(bool value = true)
	{
		_registers.Set(Display, value);
		WriteDisplayControl();
	}

	/*
		Optimal way to set values for enable display, enable cursor and blink cursor in one call to LCD.
	 */
	inline void SetDisplayControl(bool enableDisplay, bool enableCursor, bool enableBlink)
	{
		_registers.Set(Blink, enableBlink);
		_registers.Set(Cursor, enableCursor);
		_registers.Set(Display, enableDisplay);
		WriteDisplayControl();
	}

	/*
		
	 */
	inline Direction getEntryCursorDirection() const
	{
		return _registers.IsFalse(EntryCursorDirection);
	}

	/*
		
	 */
	inline void setEntryCursorDirection(Direction dir = Left)
	{
		_registers.Set(EntryCursorDirection, dir == Left);
		WriteEntryMode();
	}

	/*
		
	 */
	inline bool getEnableDisplayShift() const
	{
		return _registers.IsTrue(EntryDisplayShift);
	}

	/*
		
	 */
	inline void setEnableDisplayShift(bool value = true)
	{
		_registers.Set(EntryDisplayShift, value);
		WriteEntryMode();
	}

	/*
		
	 */
	inline void SetEntryMode(Direction entryCursorDirection, bool enableDisplayShift)
	{
		_registers.Set(EntryCursorDirection, entryCursorDirection == Left);
		_registers.Set(EntryDisplayShift, enableDisplayShift);
		WriteEntryMode();
	}

protected:

	inline void WriteDisplayAddress(byte address)
	{
		BaseT::WriteCommand(address | SetDdRamAddressCommand);
		TimingProfileT::WaitForCommand();
	}

	inline void WriteCharacterAddress(byte address)
	{
		BaseT::WriteCommand((address & 0x3F) | SetCgRamAddressCommand);
		TimingProfileT::WaitForCommand();
	}

	inline void WriteCursorShift(bool shiftDisplay, Direction shiftDir)
	{
		byte cmd = ShiftCursorCommand;
		cmd |= shiftDisplay ? 0x08 : 0;
		cmd |= shiftDir == Right ? 0x04 : 0;
		
		BaseT::WriteCommand(cmd);
		TimingProfileT::WaitForCommand();
	}

	enum Registers
	{
		// display control
		Blink,
		Cursor,
		Display,
		// entry mode
		EntryDisplayShift,
		EntryCursorDirection,
	};

	inline void setRegister(Registers reg, bool value)
	{
		_registers.Set(reg, value);
	}

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

	BitArray<byte> _registers;

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
