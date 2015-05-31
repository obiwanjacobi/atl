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

#ifndef __BIT_H__
#define __BIT_H__

namespace ATL {

/*
 *
 *
 */
template<typename T, const unsigned char BitIndex = -1>
class Bit
{
	static_assert(BitIndex < (sizeof(T) * CHAR_BITS), "Invalid BitIndex value.");

public:
	inline static void Set(T& target)
	{
		target |= Mask;
	}

	inline static void Set(T& target, bool value)
	{
		// clear bit
		target &= ~Mask;

		if (value)
		{
			// set bit
			target |= Mask;
		}
	}

	inline static void Reset(T& target)
	{
		// clear bit
		target &= ~Mask;
	}

	inline static void Toggle(T& target)
	{
		target ^= Mask;
	}

	inline static bool IsTrue(T target)
	{
		return (target & Mask) > 0;
	}

	inline static bool IsFalse(T target)
	{
		return (target & Mask) == 0;
	}

protected:
	static const T Mask = 1 << BitIndex;

private:
	Bit(){}
};



template<typename T>
class Bit<typename T, -1>
{
public:
	inline static void Set(T& target, const unsigned char bitIndex)
	{
		if (bitIndex > getMaxBits()) return;

		target |= BitToMask(bitIndex);
	}

	inline static void Set(T& target, const unsigned char bitIndex, bool value)
	{
		if (bitIndex > getMaxBits()) return;

		T mask = BitToMask(bitIndex);
		
		// clear bit
		target &= ~mask;

		if (value)
		{
			// set bit
			target |= mask;
		}
	}

	inline static void Reset(T& target, const unsigned char bitIndex)
	{
		if (bitIndex > getMaxBits()) return;

		// clear bit
		target &= ~BitToMask(bitIndex);
	}

	inline static void Toggle(T& target, const unsigned char bitIndex)
	{
		if (bitIndex > getMaxBits()) return;

		target ^= BitToMask(bitIndex);
	}

	inline static bool IsTrue(T target, const unsigned char bitIndex)
	{
		if (bitIndex > getMaxBits()) return false;

		return (target & BitToMask(bitIndex)) > 0;
	}

	inline static bool IsFalse(T target, const unsigned char bitIndex)
	{
		if (bitIndex > getMaxBits()) return false;

		return (target & BitToMask(bitIndex)) == 0;
	}

	inline unsigned static char getMaxBits()
	{
		return (sizeof(T) * CHAR_BITS);
	}

protected:
	inline static T BitToMask(const unsigned char bitIndex)
	{
		return 1 << bitIndex;
	}

private:
	Bit(){}
};

} // ATL

#endif //__BIT_H__