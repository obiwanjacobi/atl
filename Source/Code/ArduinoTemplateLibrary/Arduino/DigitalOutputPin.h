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

#ifndef __DIGITALOUTPUTPIN_H__
#define __DIGITALOUTPUTPIN_H__

namespace ATL {
namespace IO {

/*
	Initializes a BoardPinNumber to output.
 */
template<const byte BoardPinNumber>
class DigitalOutputPin
{
public:
	/*
		The ctor sets the pinMode.
	 */
	DigitalOutputPin()
	{
		pinMode(BoardPinNumber, OUTPUT);
	}

	/*
		The ctor sets the pinMode and initialValue.
	 */
	DigitalOutputPin(bool initialValue)
	{
		pinMode(BoardPinNumber, OUTPUT);
		Write(initialValue);
	}

	/*
		Writes the value to the BoardPinNumder.
	 */
	inline void Write(bool value) const
	{
		digitalWrite(BoardPinNumber, value);
	}

	/*
		Returns the value that was last written.
	*/
	bool getValue() const
	{
		return digitalRead(BoardPinNumber);
	}

	/*
		Toggles the state of the output pin.
	 */
	inline void Toggle()
	{
		Write(!getValue());
	}

	/*
		Returns the BoardPinNumber template parameter.
	 */
	inline byte getPinNumber() const
	{
		return BoardPinNumber;
	}

protected:

	// Can be used as a BaseT for TimeoutTask.
	inline void OnTimeout()
	{
		Toggle();
	}
};

} // ATL::IO

#endif //__DIGITALOUTPUTPIN_H__