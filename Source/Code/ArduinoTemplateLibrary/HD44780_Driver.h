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

#ifndef __HD44780_DRIVER_H__
#define __HD44780_DRIVER_H__

#include "HD44780_Profile.h"

namespace ATL {

/*
   See also: http://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller

   This class implements driver logic for the HD44780 LCD display. It assumes a
   write-only (5-R/W connected to GND) 4-bit mode (soft-mode).

   All template parameters represent a DigitalOutputPin template class specification
   that each correspond to the connected pins on the Arduino.

   Note that in 4-bit mode only the high data lines (4-7) of the display are used.
 */
template<typename RegSelPinT, typename EnablePinT, 
		 typename Data04PinT, typename Data15PinT, typename Data26PinT, typename Data37PinT,
		 typename TimingProfileT = HD44780_Profile>
class HD44780_Driver
{
public:

	/*
		Constructs a new instance and sets the Enable pin HIGH.
	 */
	HD44780_Driver()
		: _enable(true)
	{}

	/*
		Initializes the function set.
	 */
	inline void Initialize()
	{
		Write4(0x02);
		WriteFunctionSet();
	}

	/*
		Writes a command to the LCD.
	 */
	inline void WriteCommand(uint8_t cmd)
	{
		_rs.Write(false);
		Write8(cmd);
	}

	/*
		Writes data to the LCD.
	 */
	inline void WriteData(uint8_t data)
	{
		_rs.Write(true);
		Write8(data);
	}

protected:

	inline void Write8(uint8_t data)
	{
		Write4(data >> 4);
		Write4(data);
	}

	inline void Write4(uint8_t data)
	{
		_data04.Write(data & 0x01);
		_data15.Write(data & 0x02);
		_data26.Write(data & 0x04);
		_data37.Write(data & 0x08);

		PulseEnable();
	}

private:
	RegSelPinT _rs;
	EnablePinT _enable;
	Data04PinT _data04;
	Data15PinT _data15;
	Data26PinT _data26;
	Data37PinT _data37;

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
		_enable.Write(false);
		TimingProfileT::WaitPulseEnable();
		_enable.Write(true);
	}
};

} // ATL

#endif //__HD44780_DRIVER_H__
