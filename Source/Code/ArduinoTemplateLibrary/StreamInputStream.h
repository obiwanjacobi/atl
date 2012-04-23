#ifndef __STREAMINPUTSTREAM_H__
#define __STREAMINPUTSTREAM_H__

// BaseT is an InputStream
// StreamT is a class with 'int read()' and 'int available()'.
template<class BaseT, class StreamT>
class StreamInputStream : public BaseT
{
public:
	StreamInputStream(StreamT* serialStream)
	{
		_stream = serialStream;
	}

	// returns the number of bytes that are available in the stream.
	virtual uint16_t getLength()
	{
		return _stream->available();
	}

	// removes all content from the stream.
	virtual void Clear()
	{
		while(_stream->read() != -1);
	}

	// Reads one byte from the stream.
	// Returns the byte read in the lsb (up to 9 bits). If -1 is returned, no data was available or an error occurred.
	virtual int Read()
	{
		return _stream->read();
	}

private:
	StreamT _stream;
};

#endif //__STREAMINPUTSTREAM_H__