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

#ifndef __HD44780_DRIVERSERIAL3WIRE_H__
#define __HD44780_DRIVERSERIAL3WIRE_H__

#include "HD44780_Profile.h"

namespace ATL {
namespace Hardware {
namespace Display {

/*
	BaseT is used as a base class and implements:
		[Serial3WireOutput]
*/
template<class BaseT, const byte RegSetIndex, const byte EnableIndex,
	const byte Data04Index, const byte Data15Index, const byte Data26Index, const byte Data37Index, 
	typename BitArrayT, typename TimingProfileT = HD44780_Profile>
class HD44780_DriverSerial3Wire : public BaseT
{
public:
	inline void setDataRegister(BitArrayT* dataReg)
	{
		_dataReg = dataReg;

		_dataReg->Set(RegSetIndex, false);
		_dataReg->Set(EnableIndex, true);
		_dataReg->Set(Data04Index, false);
		_dataReg->Set(Data15Index, false);
		_dataReg->Set(Data26Index, false);
		_dataReg->Set(Data37Index, false);

		WriteDataRegister();
	}

	inline BitArrayT getDataRegister()
	{
		return _dataReg;
	}

	inline void Initialize()
	{
		Write4(0x02);
		WriteFunctionSet();
	}

	inline void WriteCommand(byte cmd)
	{
		_dataReg->Set(RegSetIndex, false);
		Write8(cmd);
	}

	inline void WriteData(byte data)
	{
		_dataReg->Set(RegSetIndex, true);
		Write8(data);
	}

protected:

	inline void Write8(byte data)
	{
		Write4(data >> 4);
		Write4(data);
	}

	inline void Write4(byte data)
	{
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

}}} // ATL::Hardware::Display

#endif //__HD44780_DRIVERSERIAL3WIRE_H__