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
