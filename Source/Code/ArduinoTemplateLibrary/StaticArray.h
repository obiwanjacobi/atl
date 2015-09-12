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

#ifndef __STATICARRAY_H__
#define __STATICARRAY_H__

namespace ATL {

namespace Implementation {

template<typename T, const uint8_t TypeSize = sizeof(T)>
class ProgMemAccessor
{
public:
	inline static T Read(uint16_t address);
};

// Specializations based on type size

template<typename T>
class ProgMemAccessor<T, 1>
{
public:
	inline static T Read(uint16_t address)
	{
		return (T)pgm_read_byte_near(address);
	}
};

template<typename T>
class ProgMemAccessor<T, 2>
{
public:
	inline static T Read(uint16_t address)
	{
		return (T)pgm_read_word_near(address);
	}
};

template<typename T>
class ProgMemAccessor<T, 4>
{
public:
	inline static T Read(uint16_t address)
	{
		return (T)pgm_read_dword_near(address);
	}
};

template<>
class ProgMemAccessor<float, 4>
{
public:
	inline static float Read(uint16_t address)
	{
		return (float)pgm_read_float_near(address);
	}
};

} // Implementation

template<typename T, const uint8_t MaxItems>
class StaticArray
{
public:
	typedef T ItemT;

	// declare a PROGMEM array and pass in the var
	StaticArray(const T array[MaxItems])
		: _array(array)
	{ }

	inline uint8_t getMaxCount() const
	{
		return MaxItems;
	}

	inline T GetAt(uint8_t index) const
	{
		if (!IsValidIndex(index)) return Default<T>::DefaultOfT;

		return Implementation::ProgMemAccessor<T>::Resolve((uint16_t)&_array[index]);
	}

	inline bool IsValidIndex(uint8_t index) const
	{
		return index >= 0 && index < MaxItems;
	}

	inline T operator[](uint8_t index) const
	{
		return GetAt(index);
	}

protected:
	inline const T* getArray() const
	{
		return _array;
	}

private:
	const T* _array;

};



} // ATL

#endif //__STATICARRAY_H__