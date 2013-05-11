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

#ifndef __DIGITALOUTPUT_H__
#define __DIGITALOUTPUT_H__

namespace ATL {
namespace IO {

/*
	BaseT is used as base class and implements:

	void [IO.Hardware.]Write(bool value);
*/
template<class BaseT>
class DigitalOutput : public BaseT
{
public:
	DigitalOutput() 
		: _value(false)
	{
	}

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

	bool Set()
	{
		return Write(true);
	}

	bool Reset()
	{
		return Write(false);
	}

	bool getValue() const
	{
		return _value;
	}

private:
	bool _value;
};

}} // ATL.IO

#endif //__DIGITALOUTPUT_H__