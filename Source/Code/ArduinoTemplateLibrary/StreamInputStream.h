#ifndef __STREAMINPUTSTREAM_H__
#define __STREAMINPUTSTREAM_H__

// This class is an adapter class to treat an Arduino Stream as an ATL InputStream.
// StreamT is a class with 'int read()' and 'int available()' (typical Arduino Stream).
template<class StreamT>
class StreamInputStream
{
public:
	StreamInputStream(StreamT* serialStream)
	{
		_stream = serialStream;
	}

	// returns the number of bytes that are available in the stream.
	uint16_t getLength()
	{
		return _stream->available();
	}

	// removes all content from the stream.
	void Clear()
	{
		while(_stream->read() != -1);
	}

	// Reads one byte from the stream.
	// Returns the byte read in the lsb (up to 9 bits). If -1 is returned, no data was available or an error occurred.
	int Read()
	{
		return _stream->read();
	}

private:
	StreamT _stream;
};

#endif //__STREAMINPUTSTREAM_H__