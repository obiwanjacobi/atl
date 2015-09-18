#ifndef __TESTINPUTSTREAM_H__
#define __TESTINPUTSTREAM_H__

#include <stddef.h>
#include "Arduino.h"

class TestInputStream
{
public:
	TestInputStream()
	{
		_buffer = NULL;
		_length = 0;
		_index = -1;
	}

	void InitInputStream(unsigned char* buffer, unsigned int length)
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
	int read()
	{
		return Read();
	}

	unsigned int getLength()
	{
		return _length - _index;
	}

	int Read()
	{
		if (_buffer == NULL) return -1;

		if ((unsigned int)_index < _length)
		{
			int value = _buffer[_index];
			_index++;

			return value;
		}

		return -1;
	}

	void Clear()
	{
		_length = 0;
	}

private:
	int _index;
	unsigned int _length;
	unsigned char* _buffer;
};

#endif //__TESTINPUTSTREAM_H__