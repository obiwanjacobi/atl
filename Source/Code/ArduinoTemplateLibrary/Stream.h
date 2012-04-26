#ifndef __STREAM_H__
#define __STREAM_H__

// abstract prototype class for streams.
class _Stream
{
	// returns the number of bytes that are available in the stream.
	virtual unsigned int getLength() = 0;
	// removes all content from the stream.
	virtual void Clear() = 0;
};

#endif /__STREAM_H__
