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

namespace ATL {

// The BitArray class stores its bits in one or more unsigned char. 
// This class can be used for maintaining boolean flags in a memory efficient way.
// A normal boolean takes up a whole unsigned char.
// T is an (unsigned) integer data-type.
template<typename T>
class BitArray
{
public:
	BitArray(T initialValues)
	{
		_bits = initialValues;
	}

	inline void SetAll(T bitValues)
	{
		_bits = bitValues;
	}

	bool Set(unsigned char bitIndex, bool value)
	{
		if (bitIndex > getMaxBits()) return false;

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

	bool Set(unsigned char bitIndex)
	{
		if (bitIndex > getMaxBits()) return false;

		// set bit
		_bits |= (1 << bitIndex);

		return true;
	}

	bool Reset(unsigned char bitIndex)
	{
		if (bitIndex > getMaxBits()) return false;

		// clear bit
		_bits &= ~(1 << bitIndex);

		return true;
	}

	inline void ResetAll()
	{
		_bits = 0;
	}

	bool IsTrue(unsigned char bitIndex) const
	{
		if (bitIndex > getMaxBits()) return false;

		return ((_bits & (1 << bitIndex)) > 0);
	}

	bool IsFalse(unsigned char bitIndex) const
	{
		if (bitIndex > getMaxBits()) return false;

		return ((_bits & (1 << bitIndex)) == 0);
	}

	void Reverse()
	{
		T rv = 0;
		for (byte i = 0; i < getMaxBits(); ++i, _bits >>= 1)
		{
			rv = (rv << 1) | (_bits & 0x01);
		}

		_bits = rv;
	}

	unsigned char getMaxBits() const
	{
		return (sizeof(T) * CHAR_BITS);
	}

	inline bool operator[] (unsigned char bitIndex) const
	{
		return IsTrue(bitIndex);
	}

	inline operator T() const
	{
		return _bits;
	}

	inline void ShiftUp(byte shift)
	{
		_bits <<= shift;
	}

	inline void ShiftDown(byte shift)
	{
		_bits >>= shift;
	}

private:
	T _bits;
};

// specializations

template<>
void BitArray<byte>::Reverse()
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
