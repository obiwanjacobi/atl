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

#ifndef __DIGITALINPUT_H__
#define __DIGITALINPUT_H__

namespace ATL {
namespace IO {

/*
	BaseT is used as base class and implements:
		bool [DigitalInputPin]Read();
*/
template<class BaseT>
class DigitalInput : public BaseT
{
public:
	DigitalInput() 
		: _value(false)
	{
	}

	/*
		Returns true when a new value was read.
		This method can be called repeatedly.
	 */
	bool Read()
	{
		bool value = BaseT::Read();

		if (_value != value)
		{
			_value = value;
			return true;
		}

		return false;
	}

	/*
		Returns the value that was last read by Read().
	 */
	bool getValue() const
	{
		return _value;
	}

private:
	bool _value;
};

}} // ATL.IO

#endif //__DIGITALINPUT_H__