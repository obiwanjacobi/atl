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

#ifndef __URM37V32_DRIVER_H__
#define __URM37V32_DRIVER_H__

#include <stdint.h>

namespace ATL {

/*
	The InputStreamT class implements a stream for retrieving the output of the Sensor (our input).
		int getLength() (available)
		int Read() (read)
	The OutputStreamT class implements a stream for sending commands to the Sensor (our output).
		void Write (uint8_t data) (write)

	Note: Serial communication is done over 9600 baud, no parity, 1 stop bit.
*/
template<class InputStreamT, class OutputStreamT>
class URM37V32_Driver : public InputStreamT, public OutputStreamT
{
public:
	enum ReceiveResult
	{
		None,
		Pending,
		ChecksumError,
		Success
	};

	void SendCommand(uint8_t command, uint8_t data1, uint8_t data2)
	{
		OutputStreamT::Write(command);
		OutputStreamT::Write(data1);
		OutputStreamT::Write(data2);
		OutputStreamT::Write(CalculateChecksum(command, data1, data2));
	}

	int ReceiveResponse(uint8_t & outCommand, uint8_t & outData1, uint8_t & outData2)
	{
		if(InputStreamT::getLength() > 3)
		{
			outCommand = InputStreamT::Read();
			outData1 = InputStreamT::Read();
			outData2 = InputStreamT::Read();
			uint8_t sum = InputStreamT::Read();

			return ValidateChecksum(outCommand, outData1, outData2, sum) ? Success : ChecksumError;
		}

		return InputStreamT::getLength() > 0 ? Pending : None;
	}
	
private:
	inline bool ValidateChecksum(uint8_t command, uint8_t data1, uint8_t data2, uint8_t checksum)
	{
		return CalculateChecksum(command, data1, data2) == checksum;
	}

	inline uint8_t CalculateChecksum(uint8_t command, uint8_t data1, uint8_t data2)
	{
		uint16_t value = command;
		value += data1;
		value += data2;

		return (uint8_t)value;
	}
};

} // ATL

#endif //__URM37V32_DRIVER_H__