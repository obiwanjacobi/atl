#ifndef __INPUTSTREAM_H__
#define __INPUTSTREAM_H__

// An abstract prototype base class for input streams. Reads data from a stream source (a device).
template <class BaseT>
class _InputStream : public _Stream
{
	// Reads one byte from the stream.
	// Returns the byte read in the lsb (up to 9 bits). If -1 is returned, no data was available or an error occurred.
	virtual int Read() = 0;
};

#endif //__INPUTSTREAM_H__
