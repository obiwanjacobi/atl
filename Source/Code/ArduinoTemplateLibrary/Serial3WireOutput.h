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

#ifndef __SERIAL3WIREOUTPUT_H__
#define __SERIAL3WIREOUTPUT_H__

#include "BitArray.h"

namespace ATL {
namespace IO {

/*
	This class implements the driver logic for a typical serial to parallel Output conversion
	usually made with 74HC595's or similar. Serial data (bits) is clocked into the shift registers.
	When all data is in place the latch clock is pulsed to latch the bits to the output's.

	SerialDataPinT is a DigitalOutputPin for the serial data pin.
	SerialClockPinT is a DigitalOutputPin for the serial clock pulse.
	LatchClockPinT is a DigitalOutputPin for latching clocked-in serial data to the outputs.

	All DigitalOutputPinT template arguments call the void Write(bool) method.
 */
template<typename SerialDataPinT, typename SerialClockPinT, typename LatchClockPinT>
class Serial3WireOutput
{
public:
	// writes out lo bits first
	template<typename T>
	void WriteReverse(BitArray<T>* dataBits)
	{
		for (byte i = 0; i < dataBits->getMaxBits(); i++)
		{
			_serialData.Write(dataBits->IsTrue(i));

			PulseSerialClock();
		}

		PulseLatchClock();
	}

	// writes out hi bits first
	template<typename T>
	void Write(BitArray<T>* dataBits)
	{
		for (byte i = dataBits->getMaxBits(); i > 0; i--)
		{
			_serialData.Write(dataBits->IsTrue(i - 1));

			PulseSerialClock();
		}

		PulseLatchClock();
	}

protected:

	void PulseSerialClock()
	{
		_serialClock.Write(true);
		_serialClock.Write(false);
	}

	void PulseLatchClock()
	{
		_latchClock.Write(true);
		_latchClock.Write(false);
	}

private:
	SerialDataPinT _serialData;
	SerialClockPinT _serialClock;
	LatchClockPinT _latchClock;
};

}} // ATL.IO

#endif // __SERIAL3WIREOUTPUT_H__

