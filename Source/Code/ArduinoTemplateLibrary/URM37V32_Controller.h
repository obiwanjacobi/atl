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

#ifndef __URM37V32_CONTROLLER_H__
#define __URM37V32_CONTROLLER_H__

namespace ATL {

/*
	BaseT is used as a base class and implements:
		void [URM37V32_Driver]SendCommand(unsigned char command, unsigned char data1, unsigned char data2);
		int [URM37V32_Driver]ReceiveResponse(unsigned char& outCommand, unsigned char& outData1, unsigned char& out_Data2);
			returns 0- no data available, 1- some data available waiting on more, 2- error in checksum, 3- success.
		See also the URM37V32_Driver class.

*/
template<class BaseT>
class URM37V32_Controller : public BaseT
{
public:
	#define CMD_TEMPERATURE 0x11
	#define CMD_DISTANCE 0x22
	#define CMD_READ_EEPROM 0x33
	#define CMD_WRITE_EEPROM 0x44

	enum ReceiveResult
	{
		None,
		Pending,
		ChecksumError,
		Success
	};

	// Mode 2: Autonomous trigger mode
	bool SetAutonomousTriggerMode(unsigned int threshold)
	{
		if (!WriteEEPROM(0x02, 0xaa)) return false;
		if (!WriteEEPROM(0x00, (unsigned char)threshold)) return false;

		return WriteEEPROM(0x01, (unsigned char)(threshold >> 8));
	}

	// Mode 3: PWM passive control mode
	bool SetPassiveControlMode()
	{
		return WriteEEPROM(0x02, 0xbb);
	}

	void BeginDistance()
	{
		BaseT::SendCommand(CMD_DISTANCE, 0x00, 0x00);
	}

	// degrees: 0-270
	void BeginDistance(unsigned int degrees)
	{
		BaseT::SendCommand(CMD_DISTANCE, map(degrees, 0, 270, 0, 46), 0x00);
	}

	ReceiveResult EndDistance(unsigned int& outDistance)
	{
		unsigned char command;
		unsigned char data1;
		unsigned char data2;

		ReceiveResult retVal = (ReceiveResult)BaseT::ReceiveResponse(command, data1, data2);

		if (retVal == Success)
		{
			if (command == CMD_DISTANCE && data1 != 0xFF && data2 != 0xFF)
			{
				outDistance = (data1 << 8) | data2;
			}
			else
			{
				// invalid reading
				retVal = None;
			}
		}

		return retVal;
	}

	void BeginTemperature()
	{
		BaseT::SendCommand(CMD_TEMPERATURE, 0x00, 0x00);
	}

	ReceiveResult EndTemperature(int& outTemperature)
	{
		unsigned char command;
		unsigned char data1;
		unsigned char data2;

		ReceiveResult retVal = BaseT::ReceiveRespone(command, data1, data2);

		if (retVal == Success)
		{
			if (command == CMD_TEMPERATURE)
			{
				outTemperature = ((data1 & 0x0F) << 8) | data2;

				// below 0
				if ((data1 & 0xF0) != 0)
				{
					outTemperature = -outTemperature;
				}
			}
			else
			{
				// invalid reading
				retVal = None;
			}
		}

		return retVal;
	}

private:
	bool WriteEEPROM(unsigned char data1, unsigned char data2)
	{
		BaseT::SendCommand(CMD_WRITE_EEPROM, data1, data2);

		unsigned char outCommand;
		unsigned char outData1;
		unsigned char outData2;

		// TODO: timeout?
		while(BaseT::ReceiveResponse(outCommand, outData1, outData2) != Success);

		// check echo response
		return (outCommand == 0x44 && outData1 == data1 && outData2 == data2);
	}

#ifndef Arduino_h
	// copied from arduino: WMath.cpp
	inline long map(long x, long in_min, long in_max, long out_min, long out_max)
	{
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
#endif

};

} // ATL

#endif //__URM37V32_CONTROLLER_H__