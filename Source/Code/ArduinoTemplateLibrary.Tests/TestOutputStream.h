#ifndef __TESTOUTPUTSTREAM_H__
#define __TESTOUTPUTSTREAM_H__

#include "Arduino.h"

class TestOutputStream
{
public:
	TestOutputStream()
	{
		_buffer = NULL;
		_length = 0;
		_index = -1;
	}

	void InitOutputStream(unsigned char* buffer, unsigned int length)
	{
		_buffer = buffer;
		_length = length;
		_index = 0;
	}

	// Arduino Stream compatible methods
	unsigned int available()
	{
		return getLength();
	}
	void write(byte data)
	{
		Write(data);
	}
	void flush()
	{
		_index = 0;
	}

	unsigned int getLength()
	{
		return _index;
	}

	bool Write(unsigned char data)
	{
		if (_buffer == NULL) return false;

		if ((unsigned int)_index < _length)
		{
			_buffer[_index] = data;
			_index++;

			return true;
		}

		return false;
	}

private:
	int _index;
	unsigned int _length;
	unsigned char* _buffer;
};

#endif //__TESTOUTPUTSTREAM_H__