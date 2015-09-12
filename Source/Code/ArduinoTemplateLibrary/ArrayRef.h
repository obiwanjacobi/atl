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

#ifndef __ARRAYREF_H__
#define __ARRAYREF_H__

#include <stdint.h>
#include "Default.h"

namespace ATL {


/*
* Bounds-checked wrapper for an array reference
*
*/
template<typename T, const uint8_t MaxItems>
class ArrayRef
{
public:
	typedef T ItemT;

	ArrayRef(T(&array)[MaxItems])
		: _arr(array)
	{ }

	inline uint8_t getMaxCount() const
	{
		return MaxItems;
	}

	inline T GetAt(uint8_t index) const
	{
		if (!IsValidIndex(index)) return Default<T>::DefaultOfT;

		return _arr[index];
	}

	inline void SetAt(uint8_t index, T value)
	{
		if (!IsValidIndex(index)) return;

		_arr[index] = value;
	}

	inline bool IsValidIndex(uint8_t index) const
	{
		return index >= 0 && index < MaxItems;
	}

	inline T operator[](uint8_t index) const
	{
		return GetAt(index);
	}

private:
	T(&_arr)[MaxItems];
};


} // ATL

#endif //__ARRAYREF_H__