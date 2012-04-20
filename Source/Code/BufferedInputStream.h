#ifndef __BUFFEREDINPUTSTREAM_H__
#define __BUFFEREDINPUTSTREAM_H__

#include <inttypes.h>

// The BufferedInputStream implements an abstract InputStream by using a circular buffer (RingBuffer).
// BaseT is a InputStream class type (or derived).
// BufferT is the class of the RingBuffer implementation.
template<class BaseT, class BufferT>
class BufferedInputStream : BaseT
{
public:
	virtual int Read()
	{
		if(Buffer.getLength() == 0)
		{
			return -1;
		}

		return Buffer.Get();
	}

	virtual uint16_t getLength()
	{
		return Buffer.getLength();
	}

	virtual void Clear()
	{
		Buffer.Clear();
	}

protected:
	BufferT Buffer;
};

#endif //__BUFFEREDINPUTSTREAM_H__