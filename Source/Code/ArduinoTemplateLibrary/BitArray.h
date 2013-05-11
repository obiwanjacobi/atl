/*  
	Arduino Template Library http://atl.codeplex.com
	Written by Marc Jacobi
	Copyright 2012-2013 All Rights Reserved

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

#include <Arduino.h>

namespace ATL {

// The BitArray class stores its bits in one or more byte. 
// This class can be used for maintaining boolean flags in a memory effecient way.
// A normal boolean takes up a whole byte.
// T is an (unsigned) integer datatype.
template<typename T>
class BitArray
{
public:
	BitArray(T initialValues)
	{
		_bits = initialValues;
	}

	bool Set(byte bitIndex, bool value)
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

	bool Set(byte bitIndex)
	{
		if (bitIndex > getMaxBits()) return false;

		T mask = 1 << bitIndex;
		// clear bit
		_bits &= ~mask;

		// set bit
		_bits |= mask;

		return true;
	}

	bool Reset(byte bitIndex)
	{
		if (bitIndex > getMaxBits()) return false;

		T mask = 1 << bitIndex;
		// clear bit
		_bits &= ~mask;

		return true;
	}

	bool IsTrue(byte bitIndex) const
	{
		if (bitIndex > getMaxBits()) return false;

		T mask = 1 << bitIndex;
		return ((_bits & mask) > 0);
	}

	bool IsFalse(byte bitIndex) const
	{
		if (bitIndex > getMaxBits()) return false;

		T mask = 1 << bitIndex;
		return ((_bits & mask) == 0);
	}

	byte getMaxBits() const
	{
		return (sizeof(T) * 8);
	}

	bool operator[] (byte bitIndex) const
	{
		return IsTrue(bitIndex);
	}

	operator T() const
	{
		return _bits;
	}

private:
	T _bits;
};

} //ATL

#endif //__BITARRAY_H__
