#ifndef __BUFFEREDINPUTSTREAM_H__
#define __BUFFEREDINPUTSTREAM_H__

// The BufferedInputStream implements an abstract InputStream by using a circular buffer (RingBuffer).
// BaseT is the class of a RingBuffer implementation: unsigned int getLength(); int Get(); void Clear();
template<class BaseT>
class BufferedInputStream : BaseT
{
public:
	int Read()
	{
		if(base.getLength() == 0)
		{
			return -1;
		}

		return base.Get();
	}

	unsigned int getLength()
	{
		return base.getLength();
	}

	void Clear()
	{
		base.Clear();
	}
};

#endif //__BUFFEREDINPUTSTREAM_H__