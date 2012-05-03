#ifndef __TESTSTREAM_H__
#define __TESTSTREAM_H__

#include "Arduino.h"

class TestStream
{
public:
	TestStream()
	{
		_buffer = NULL;
		_length = 0;
		_index = -1;
	}

	void InitStream(unsigned char* buffer, unsigned int length)
	{
		_buffer = buffer;
		_length = length;
		_index = 0;
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

	void Clear()
	{
		_length = 0;
	}

private:
	int _index;
	unsigned int _length;
	unsigned char* _buffer;
};

#endif //__TESTSTREAM_H__