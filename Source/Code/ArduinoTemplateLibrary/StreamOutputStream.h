#ifndef __STREAMOUTPUTSTREAM_H__
#define __STREAMOUTPUTSTREAM_H__

#include <Arduino.h>

namespace ATL {
namespace IO {

// This class is an adapter class to treat an Arduino Stream as an ATL OutputStream.
// StreamT is a class with 'void write()', 'void flush()' and 'int available()' (typical Arduino Stream).
template<class StreamT>
class StreamOutputStream
{
public:
	StreamOutputStream()
	{
		_stream = NULL;
	}

	StreamOutputStream(StreamT* serialStream)
	{
		AttachOutputStream(serialStream);
	}

	void AttachOutputStream(StreamT* serialStream)
	{
		_stream = serialStream;
	}

	// returns the number of bytes that are available in the stream.
	unsigned int getLength() const
	{
		if (_stream == NULL) return 0;

		return _stream->available();
	}

	// removes all content from the stream.
	void Flush()
	{
		if (_stream == NULL) return;

		_stream->flush();
	}

	// Writes one byte to the stream.
	void Write(byte data)
	{
		if (_stream == NULL) return;

		_stream->write(data);
	}

private:
	StreamT* _stream;
};

}} // ATL.IO

#endif //__STREAMOUTPUTSTREAM_H__