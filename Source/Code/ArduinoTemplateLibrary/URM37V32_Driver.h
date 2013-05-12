/*  
	Arduino Template Library http://atl.codeplex.com
	Written by Marc Jacobi
	Copyright 2012-2013 All Rights Reserved

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

namespace ATL {
namespace Hardware {
namespace Sensor {

/*
	The InputStreamT class implements a stream for retrieving the output of the Sensor (our input).
		int getLength() (available)
		int Read() (read)
	The OutputStreamT class implements a stream for sending commands to the Sensor (our output).
		void Write (byte data) (write)

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

	void SendCommand(unsigned char command, unsigned char data1, unsigned char data2)
	{
		OutputStreamT::Write(command);
		OutputStreamT::Write(data1);
		OutputStreamT::Write(data2);
		OutputStreamT::Write(CalculateChecksum(command, data1, data2));
	}

	int ReceiveResponse(unsigned char& outCommand, unsigned char& outData1, unsigned char& outData2)
	{
		if(InputStreamT::getLength() > 3)
		{
			outCommand = InputStreamT::Read();
			outData1 = InputStreamT::Read();
			outData2 = InputStreamT::Read();
			unsigned char sum = InputStreamT::Read();

			return ValidateChecksum(outCommand, outData1, outData2, sum) ? Success : ChecksumError;
		}

		return InputStreamT::getLength() > 0 ? Pending : None;
	}
	
private:
	inline bool ValidateChecksum(unsigned char command, unsigned char data1, unsigned char data2, unsigned char checksum)
	{
		return CalculateChecksum(command, data1, data2) == checksum;
	}

	inline unsigned char CalculateChecksum(unsigned char command, unsigned char data1, unsigned char data2)
	{
		int value = command;
		value += data1;
		value += data2;

		return (unsigned char)value;
	}
};

}}} // ATL.Hardware.Sensor

#endif //__URM37V32_DRIVER_H__