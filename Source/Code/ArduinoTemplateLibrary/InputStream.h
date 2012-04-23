#ifndef __INPUTSTREAM_H__
#define __INPUTSTREAM_H__

// An abstract input stream base class that reads data from a stream source (a device).
// BaseT is a type of Stream used as its base class.
template <class BaseT>
class InputStream : public BaseT
{
	// Reads one byte from the stream.
	// Returns the byte read in the lsb (up to 9 bits). If -1 is returned, no data was available or an error occurred.
	virtual int Read() = 0;
};

#endif //__INPUTSTREAM_H__
