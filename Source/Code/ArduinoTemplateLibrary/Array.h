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

#ifndef __ARRAY_H__
#define __ARRAY_H__

namespace ATL {

/*
 *	Bounds-checked array.
 *
 */
template<typename T, const unsigned char MaxItems>
class Array
{
public:
	typedef T ItemT;

	inline unsigned char getMaxCount() const
	{
		return MaxItems;
	}

	inline T GetAt(unsigned char index) const
	{
		if (!IsValidIndex(index)) return DefaultOfT;

		return _arr[index];
	}

	inline void SetAt(unsigned char index, T value)
	{
		if (!IsValidIndex(index)) return;

		_arr[index] = value;
	}

	inline bool IsValidIndex(unsigned char index) const
	{
		return index >= 0 && index < MaxItems;
	}

	inline T operator[](unsigned char index) const
	{
		return GetAt(index);
	}

	static T DefaultOfT;

private:
	T _arr[MaxItems];
};

template<typename T, const unsigned char MaxItems>
T Array<T, MaxItems>::DefaultOfT;



} // ATL

#endif //__ARRAY_H__