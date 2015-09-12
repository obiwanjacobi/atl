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

#ifndef __COLLECTIONREF_H__
#define __COLLECTIONREF_H__

#include <stdint.h>
#include "Default.h"

namespace ATL {


// ArrayT is either Array or ArrayRef 
//   and implements T GetAt(uint8_t index), SetAt(uint8_t index, T item) and uint8_t getMaxCount()
// ArrayT::ItemT is the type of the item in ArrayT (typedef in ArrayT)
template<typename ArrayT>
class CollectionRef
{
public:
	CollectionRef(ArrayT& array)
		: _array(array), _count(0)
	{ }

	inline uint8_t getCount() const
	{
		return _count;
	}

	inline bool IsValidIndex(uint8_t index) const
	{
		return index >= 0 && index < _count;
	}

	inline typename ArrayT::ItemT GetAt(uint8_t index) const
	{
		if (!IsValidIndex(index)) return Default<typename ArrayT::ItemT>::DefaultOfT;

		return _array.GetAt(index);
	}

	inline typename ArrayT::ItemT operator[](uint8_t index) const
	{
		return GetAt(index);
	}

	inline char IndexOf(typename ArrayT::ItemT& item) const
	{
		for (int i = 0; i < _count; i++)
		{
			if (_array.GetAt(i) == item)
				return i;
		}

		return -1;
	}

	inline void Add(typename ArrayT::ItemT item)
	{
		if (_count < _array.getMaxCount())
		{
			_array.SetAt(_count, item);
			_count++;
		}
	}

	inline void Clear()
	{
		_count = 0;
	}

private:
	ArrayT& _array;
	uint8_t _count;
};



} // ATL

#endif //__COLLECTIONREF_H__