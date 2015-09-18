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

#ifndef __BITARRAY_H__
#define __BITARRAY_H__

#ifndef CHAR_BITS
#define CHAR_BITS 8
#endif

#include <stdint.h>

namespace ATL {

/*
	The BitArray class stores its bits in one or more bytes.
	This class can be used for maintaining boolean flags in a memory efficient way.
	A normal boolean takes up a whole byte.
	T is an (unsigned) integer data-type.
 */
template<typename T>
class BitArray
{
public:
	BitArray(T initialValues = 0)
		: _bits(initialValues)
	{ }

	/*
		Sets all bits in one call.
	 */
	inline void SetAll(T bitValues)
	{
		_bits = bitValues;
	}

	/*
		Sets the bits from value for bitCount bits starting at bit0
		in the BitArray starting at the bitIndex position.
	 */
	bool Set(uint8_t bitIndex, T value, uint8_t bitCount)
	{
		if (!isValidIndex(bitIndex, bitCount)) return false;

		T mask = CreateMask(bitCount);

		// make sure only valid bits are set
		value &= mask;

		// shift up to bit position
		mask <<= bitIndex;
		value <<= bitIndex;

		// clear bits then set bits with new value
		_bits &= ~mask;
		_bits |= value;

		return true;
	}

	/*
		Retrieves the bits for a bitCount number of bits from
		the BitArray starting at the bitIndex. The value is
		shifted down to bit0 in the return value.
	 */
	T Get(uint8_t bitIndex, uint8_t bitCount) const
	{
		if (!isValidIndex(bitIndex, bitCount)) return (T)0;

		T mask = CreateMask(bitCount);

		// mask the bits and extract value
		mask <<= bitIndex;
		T value = (T)(_bits & mask);

		// shift value down to lowest position
		value >>= bitIndex;

		return value;
	}

	/*
		Sets the bit at bitIndex position to the specified value.
	 */
	bool Set(uint8_t bitIndex, bool value)
	{
		if (!isValidIndex(bitIndex)) return false;

		T mask = 1 << bitIndex;
		// clear bit
		_bits &= ~mask;

		if (value)
		{
			// set bit
			_bits |= mask;
		}

		return true;
	}

	/*
		Sets the bit at bitIndex position to true.
	 */
	bool Set(uint8_t bitIndex)
	{
		if (!isValidIndex(bitIndex)) return false;

		// set bit
		_bits |= (1 << bitIndex);

		return true;
	}

	/*
		Gets the bit at bitIndex position.
	 */
	inline bool Get(uint8_t bitIndex) const
	{
		return IsTrue(bitIndex);
	}

	/*
		Sets the bit at bitIndex position to false.
	 */
	bool Reset(uint8_t bitIndex)
	{
		if (!isValidIndex(bitIndex)) return false;

		// clear bit
		_bits &= ~(1 << bitIndex);

		return true;
	}

	/*
		Resets all bits to false;
	 */
	inline void ResetAll()
	{
		_bits = 0;
	}

	/*
		Returns true if the bit at bitIndex position is true.
	 */
	bool IsTrue(uint8_t bitIndex) const
	{
		if (!isValidIndex(bitIndex)) return false;

		return ((_bits & (1 << bitIndex)) > 0);
	}

	/*
		Returns true if the bit at bitIndex position is false.
	 */
	bool IsFalse(uint8_t bitIndex) const
	{
		if (!isValidIndex(bitIndex)) return false;

		return ((_bits & (1 << bitIndex)) == 0);
	}

	/*
		Reverses all bits in the BitArray.
		Bit0 -> BitX / BitX -> Bit0.
	 */
	void Reverse()
	{
		T rv = 0;
		for (uint8_t i = 0; i < getMaxBits(); ++i, _bits >>= 1)
		{
			rv = (rv << 1) | (_bits & 0x01);
		}

		_bits = rv;
	}

	/*
		Returns the maximum number of bits that can be stored.
	 */
	inline uint8_t getMaxBits() const
	{
		return (sizeof(T) * CHAR_BITS);
	}

	inline bool operator[] (uint8_t bitIndex) const
	{
		return IsTrue(bitIndex);
	}

	inline operator T() const
	{
		return _bits;
	}

	/*
		Shifts all bits up specified number of times, 
		losing the most significant bits and 
		setting false for the least significant bits.
	 */
	inline void ShiftUp(uint8_t shift)
	{
		_bits <<= shift;
	}

	/*
		Shifts all bits down specified number of times, 
		losing the least significant bits and 
		setting false for the most significant bits.
	 */
	inline void ShiftDown(uint8_t shift)
	{
		_bits >>= shift;
	}

private:
	T _bits;

	T CreateMask(uint8_t count) const
	{
		T mask = 0;

		for (int i = 0; i < count; i++)
		{
			mask <<= 1;
			mask |= 1;
		}

		return mask;
	}

	inline bool isValidIndex(uint8_t index, uint8_t count = 1) const
	{
		return (index + count) <= getMaxBits();
	}
};

// BitArray template specializations

template<>
void BitArray<uint8_t >::Reverse()
{
	_bits = (_bits & 0xF0) >> 4 | (_bits & 0x0F) << 4;
	_bits = (_bits & 0xCC) >> 2 | (_bits & 0x33) << 2;
	_bits = (_bits & 0xAA) >> 1 | (_bits & 0x55) << 1;
}

template<>
void BitArray<uint16_t>::Reverse()
{
	_bits = (_bits & 0xFF00) >> 8 | (_bits & 0x00FF) << 8;
	_bits = (_bits & 0xF0F0) >> 4 | (_bits & 0x0F0F) << 4;
	_bits = (_bits & 0xCCCC) >> 2 | (_bits & 0x3333) << 2;
	_bits = (_bits & 0xAAAA) >> 1 | (_bits & 0x5555) << 1;
}


} //ATL


#endif //__BITARRAY_H__
