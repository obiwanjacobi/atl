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

#ifndef __BITFLAG_H__
#define __BITFLAG_H__

#include <stdint.h>

#ifndef CHAR_BITS
#define CHAR_BITS 8
#endif

namespace ATL {

/*
*
*
*/
class BitFlag
{
public:
	template<typename T>
	inline static void Set(T& target, const uint8_t bitIndex)
	{
		if (bitIndex > getMaxBits<T>()) return;

		target |= BitToMask<T>(bitIndex);
	}

	template<typename T>
	inline static void Set(T& target, const uint8_t bitIndex, bool value)
	{
		if (bitIndex > getMaxBits<T>()) return;

		T mask = BitToMask<T>(bitIndex);

		// clear bit
		target &= ~mask;

		if (value)
		{
			// set bit
			target |= mask;
		}
	}

	template<typename T>
	inline static void Reset(T& target, const uint8_t bitIndex)
	{
		if (bitIndex > getMaxBits<T>()) return;

		// clear bit
		target &= ~BitToMask<T>(bitIndex);
	}

	template<typename T>
	inline static void Toggle(T& target, const uint8_t bitIndex)
	{
		if (bitIndex > getMaxBits<T>()) return;

		target ^= BitToMask<T>(bitIndex);
	}

	template<typename T>
	inline static bool IsTrue(T target, const uint8_t bitIndex)
	{
		if (bitIndex > getMaxBits<T>()) return false;

		return (target & BitToMask<T>(bitIndex)) > 0;
	}

	template<typename T>
	inline static bool IsFalse(T target, const uint8_t bitIndex)
	{
		if (bitIndex > getMaxBits<T>()) return false;

		return (target & BitToMask<T>(bitIndex)) == 0;
	}

	template<typename T>
	inline static uint8_t getMaxBits()
	{
		return (sizeof(T) * CHAR_BITS);
	}

protected:
	template<typename T>
	inline static T BitToMask(const uint8_t bitIndex)
	{
		return 1 << bitIndex;
	}

private:
	BitFlag(){}
};


} // ATL

#endif //__BITFLAG_H__