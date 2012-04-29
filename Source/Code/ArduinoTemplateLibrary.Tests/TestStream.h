#ifndef __TESTSTREAM_H__
#define __TESTSTREAM_H__

class TestStream
{
public:
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

#endif //__TESTSTREAM_H__