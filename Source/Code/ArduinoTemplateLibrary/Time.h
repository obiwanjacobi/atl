#ifndef __TIME_H__
#define __TIME_H__

#include<Arduino.h>

namespace ATL {

struct Time
{
public:
	enum Resolution
	{
		Milliseconds,
		Microseconds
	};

	Time(Resolution resolution)
	{
		_resolution = resolution;
		Update();
	}

	void Update()
	{
		if (_resolution == Milliseconds)
		{
			_ticks = millis();
		}
		else
		{
			_ticks = micros();
		}
	}

	unsigned long getMinutes() const
	{
		return getSeconds() / 60;
	}

	unsigned long getSeconds() const
	{
		return getMilliseconds() / 1000;
	}

	unsigned long getMilliseconds() const
	{
		if (_resolution == Milliseconds)
		{
			return _ticks;
		}

		return getMicroseconds() / 1000;
	}

	unsigned long getMicroseconds() const
	{
		if (_resolution == Milliseconds)
		{
			return _ticks * 1000;
		}

		return _ticks;
	}

	inline Resolution getResolution() const { return _resolution; }

private:
	Resolution _resolution;
	unsigned long _ticks;
};

} //ATL

#endif //__TIME_H__