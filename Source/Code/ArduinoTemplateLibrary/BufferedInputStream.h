#ifndef __BUFFEREDINPUTSTREAM_H__
#define __BUFFEREDINPUTSTREAM_H__

// The BufferedInputStream implements an abstract InputStream by using a circular buffer (RingBuffer).
// BaseT is the class of a RingBuffer implementation: unsigned int getLength(); int Get(); void Clear();
template<class BaseT>
class BufferedInputStream : public BaseT
{
public:
	// adapts the Read method to always check for length.
	int Read()
	{
		if(getLength() == 0)
		{
			return -1;
		}

		return (int)BaseT::Read();
	}
};

#endif //__BUFFEREDINPUTSTREAM_H__