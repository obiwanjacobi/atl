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

#ifndef __DIGITALOUTPUT_H__
#define __DIGITALOUTPUT_H__

namespace ATL {
namespace IO {

/*
	BaseT is used as base class and implements:
		void [DigitalOutputPin]Write(bool value);
*/
template<class BaseT>
class DigitalOutput : public BaseT
{
public:
	DigitalOutput() 
		: _value(false)
	{}

	/*
		Write to the output pin if the value is different than the last write.
		Returns true if the value was written. If false is returned the value did not differ.
	 */
	bool Write(bool value)
	{
		if (_value != value)
		{
			BaseT::Write(value);
			_value = value;

			return true;
		}

		return false;
	}

	/*
		Writes HIGH (true) to the output.
	 */
	bool Set()
	{
		return Write(true);
	}

	/*
		Writes LOW (false) to the output.
	 */
	bool Reset()
	{
		return Write(false);
	}

	/*
		Returns the value that was last written.
	 */
	bool getValue() const
	{
		return _value;
	}

private:
	bool _value;
};

}} // ATL.IO

#endif //__DIGITALOUTPUT_H__