#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#include <inttypes.h>

// A RingBuffer uses a fixed amount of memory to simulate an 'endless' buffer.
// There is NO overrun or underrun detection!
// T is the data type of the buffer items.
// Size is the number of 'T' items in the buffer.
template <typename T, uint16_t Size>
class RingBuffer
{
public:
	RingBuffer()
	{
		Clear();
	}

	inline void Clear()
	{
		_writePtr = _buffer;
		_readPtr = _buffer;
	}

	bool Put(T value)
	{
		*_writePtr = value;
		_writePtr++;

		if (_writePtr >= (_buffer + Size))
		{
			_writePtr = _buffer;
		}

		return true;
	}

	T Get()
	{
		T result = *_readPtr;
		_readPtr++;

		if (_readPtr >= (_buffer + Size))
		{
			_readPtr = _buffer;
		}

		return result;
	}

	inline uint16_t getLength() const
	{
		if (_writePtr >= _readPtr)
		{
			return _writePtr - _readPtr;
		}

		return Size - (_readPtr - _writePtr);
	}

private:
	T _buffer[Size];
	T* _writePtr;
	T* _readPtr;
};

#endif //__RINGBUFFER_H__
