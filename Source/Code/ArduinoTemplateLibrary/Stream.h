#ifndef __STREAM_H__
#define __STREAM_H__

#include <inttypes.h>

// abstract base class for streams.
// TEMP NAME DUE TO CONFLICT WITH ARDUINO STREAM.H
class StreamBase
{
	// returns the number of bytes that are available in the stream.
	virtual uint16_t getLength() = 0;
	// removes all content from the stream.
	virtual void Clear() = 0;
};

#endif /__STREAM_H__
