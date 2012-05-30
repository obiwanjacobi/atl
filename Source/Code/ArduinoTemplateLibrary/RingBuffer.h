#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

namespace ATL {

// A RingBuffer uses a fixed amount of memory to simulate an 'endless' buffer.
// Capacity is always one less than the specified Size.
// There is NO underrun detection!
// T is the data type of the buffer items.
// Size is the number of 'T' items in the buffer.
template <typename T, unsigned int Size>
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

	bool Write(T value)
	{
		// check for overrun
		if ((_writePtr + 1) >= (_buffer + Size))
		{
			if ((_buffer) == _readPtr) return false;
		}
		else if ((_writePtr + 1) == _readPtr) return false;

		*_writePtr = value;
		_writePtr++;

		if (_writePtr >= (_buffer + Size))
		{
			_writePtr = _buffer;
		}

		return true;
	}

	T Read()
	{
		T result = *_readPtr;
		_readPtr++;

		if (_readPtr >= (_buffer + Size))
		{
			_readPtr = _buffer;
		}

		return result;
	}

	inline unsigned int getLength() const
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

} //ATL

#endif //__RINGBUFFER_H__
