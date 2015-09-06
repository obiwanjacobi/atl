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

#ifndef __COLLECTION_H__
#define __COLLECTION_H__

namespace ATL {

	

// ArrayT is either Array or ArrayRef 
//   and implements T GetAt(unsigned char index), SetAt(unsigned char index, T item) and unsigned char getMaxCount()
// ArrayT::ItemT is the type of the item in ArrayT (typedef in ArrayT)
template<typename ArrayT>
class CollectionRef
{
public:
	CollectionRef(ArrayT& array)
		: _array(array), _count(0)
	{ }

	inline unsigned char getCount() const
	{
		return _count;
	}

	inline bool IsValidIndex(unsigned char index) const
	{
		return index >= 0 && index < _count;
	}

	inline typename ArrayT::ItemT GetAt(unsigned char index) const
	{
		if (!IsValidIndex(index)) return ArrayT::DefaultOfT;

		return _array.GetAt(index);
	}

	inline typename ArrayT::ItemT operator[](unsigned char index) const
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
	unsigned char _count;
};



} // ATL

#endif //__COLLECTION_H__