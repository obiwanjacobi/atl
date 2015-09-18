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
template<typename T, const uint16_t MaxItems>
class ArrayRef
{
public:
	typedef T ItemT;

	ArrayRef(T* array)
		: _arr(array)
	{ }

	inline uint16_t getMaxCount() const
	{
		return MaxItems;
	}
    
    inline uint16_t getCount() const
    {
        return MaxItems;
    }

	inline T GetAt(int16_t index) const
	{
		if (!IsValidIndex(index)) return Default<T>::DefaultOfT;

		return _arr[index];
	}

	inline void SetAt(int16_t index, T value)
	{
		if (!IsValidIndex(index)) return;

		_arr[index] = value;
	}

	inline bool IsValidIndex(int16_t index) const
	{
		return index >= 0 && index < MaxItems;
	}

	inline int8_t IndexOf(T item) const
	{
		for (uint8_t i = 0; i < MaxItems; i++)
		{
			if (_arr[i] == item)
				return i;
		}

		return -1;
	}

	inline T operator[](int16_t index) const
	{
		return GetAt(index);
	}

	inline void Clear()
	{
		memset(_arr, 0, MaxItems);
	}

protected:
	inline void setBuffer(T* array)
	{
		_arr = array;
	}

	inline T* getBuffer() const
	{
		return _arr;
	}

private:
	T* _arr;
};


} // ATL

#endif //__ARRAYREF_H__