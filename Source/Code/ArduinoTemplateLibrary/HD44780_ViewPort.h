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

#ifndef __HD44780_VIEWPORT_H__
#define __HD44780_VIEWPORT_H__

namespace ATL {
namespace Hardware {
namespace Display {

/*
	BaseT is used as a base class and implements:
		[HD44780_View]
*/
template<class BaseT>
class HD44780_ViewPort : public BaseT
{
public:

	HD44780_ViewPort()
		: _offset(0)
	{}

	inline bool ScrollRight()
	{
		if (_offset > 0)
		{
			_offset--;
			BaseT::WriteCursorShift(true, BaseT::Right);
			return true;
		}
		return false;
	}

	inline bool ScrollLeft()
	{
		if (_offset > BaseT::getTotalColumns())
		{
			_offset++;
			BaseT::WriteCursorShift(true, BaseT::Left);
			return true;
		}
		return false;
	}

	inline byte getDislayOffset() const
	{
		return _offset;
	}

private:
	byte _offset;
	
};

}}} // ATL::Hardware::Display

#endif //__HD44780_VIEWPORT_H__