#ifndef __TIME_H__
#define __TIME_H__

#include<Arduino.h>

namespace ATL {

enum TimeResolution
{
	Milliseconds,
	Microseconds
};

template<TimeResolution resolution = Milliseconds>
class Time
{
public:
	Time() : _ticks(0)
	{
		Update();
	}

	// returns delta time in 'resolution'
	unsigned long Update()
	{
		unsigned long previous = _ticks;

		if (resolution == Milliseconds)
		{
			_ticks = millis();
		}
		else
		{
			_ticks = micros();
		}

		return _ticks - previous;
	}

	inline unsigned long getMilliseconds() const
	{
		return getMilliseconds(_ticks);
	}

	inline unsigned long getMicroseconds() const
	{
		return getMicroseconds(_ticks);
	}

	inline TimeResolution getResolution() const { return resolution; }

private:
	unsigned long _ticks;

protected:
	inline unsigned long getTicks() const { return _ticks; }

	inline unsigned long getMilliseconds(unsigned long ticks) const
	{
		if (resolution == Milliseconds)
		{
			return ticks;
		}

		return getMicroseconds(ticks) / 1000;
	}

	inline unsigned long getMicroseconds(unsigned long ticks) const
	{
		if (resolution == Milliseconds)
		{
			return ticks * 1000;
		}

		return ticks;
	}
};


template<TimeResolution resolution>
class TimeEx : Time<resolution>
{
public:
	TimeEx() : Time(), _previous(0)
	{
		_start = getTicks();
	}

	unsigned long Update()
	{
		_previous = getTicks();
		return Time::Update();
	}

	inline unsigned long getStartMilliseconds() const
	{
		return getMilliseconds(_start);
	}

	inline unsigned long getStartMicroseconds() const
	{
		return getMicroseconds(_start);
	}

	inline unsigned long getPreviousMilliseconds() const
	{
		return getMilliseconds(_previous);
	}

	inline unsigned long getPreviousMicroseconds() const
	{
		return getMicroseconds(_previous);
	}

private:
	unsigned long _start;
	unsigned long _previous;
};

} //ATL

#endif //__TIME_H__