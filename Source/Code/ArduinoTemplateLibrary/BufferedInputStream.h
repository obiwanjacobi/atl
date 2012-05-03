#ifndef __BUFFEREDINPUTSTREAM_H__
#define __BUFFEREDINPUTSTREAM_H__

// The BufferedInputStream implements an abstract InputStream by using a circular buffer (RingBuffer).
/*
	BaseT is the class of a RingBuffer implementation: 
		unsigned int [IO.Stream]getLength(); 
		int [IO.InputStream.]Read(); 
*/
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