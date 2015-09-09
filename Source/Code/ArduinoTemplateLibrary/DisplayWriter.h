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

#ifndef __DISPLAYWRITER_H__
#define __DISPLAYWRITER_H__

#include <stddef.h>
#include <stdint.h>

namespace ATL {


// abstract / interface
class DisplayWriter
{
public:
	static const uint8_t DontCare = 0xFF;

	virtual void Write(const char* /*text*/) {}
	virtual void GoTo(uint8_t /*lineIndex*/, uint8_t /*columnIndex*/) {}
	virtual void SetCursor(uint8_t /*lineIndex*/, uint8_t /*columnIndex*/, bool /*blink*/) {}
};



} // ATL

#endif //__DISPLAYWRITER_H__