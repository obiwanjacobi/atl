/*  
	Arduino Template Library http://atl.codeplex.com
	Written by Marc Jacobi
	Copyright 2012-2015 All Rights Reserved

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __TIME_H__
#define __TIME_H__

#include<Arduino.h>

namespace ATL {

/*
	Time resolution in either milli-seconds or micro-seconds.
 */
enum TimeResolution
{
	Milliseconds,
	Microseconds
};

/*
	Keeps track of time ticks (either milli- or micro-seconds).
 */
template<TimeResolution resolution = Milliseconds>
class Time
{
public:

	/*
		Constructs a new instance.
	 */
	Time() 
		: _ticks(0)
	{
		Update();
	}

	/*
		Captures the time ticks.
		Returns delta-time in 'resolution'
	 */
	inline unsigned long Update();
	/*{
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
	}*/

	/*
		Returns the time ticks in milli-seconds.
	 */
	inline unsigned long getMilliseconds() const
	{
		return getMilliseconds(_ticks);
	}

	/*
		Returns the time ticks in micro-seconds.
	 */
	inline unsigned long getMicroseconds() const
	{
		return getMicroseconds(_ticks);
	}

	/*
		Returns the resolution template parameter.
	 */
	inline TimeResolution getResolution() const 
	{
		return resolution;
	}

protected:

	/*
		Returns the raw time ticks.
	 */
	inline unsigned long getTicks() const 
	{
		return _ticks;
	}

	/*
		Returns the ticks in milli-seconds.
	 */
	inline static unsigned long getMilliseconds(unsigned long ticks);
	/*{
		if (resolution == Milliseconds)
		{
			return ticks;
		}

		return ticks / 1000;
	}*/

	/*
		Returns the ticks in micro-seconds.
	 */
	inline static unsigned long getMicroseconds(unsigned long ticks);
	/*{
		if (resolution == Milliseconds)
		{
			return ticks * 1000;
		}

		return ticks;
	}*/

private:
	unsigned long _ticks;
};

// Time template specializations

//template<>
//unsigned long Time<Milliseconds>::Update()
//{
//	unsigned long previous = _ticks;
//
//	_ticks = millis();
//
//	return _ticks - previous;
//}

template<>
inline static unsigned long Time<Milliseconds>::getMilliseconds(unsigned long ticks)
{
	return ticks;
}

template<>
inline static unsigned long Time<Milliseconds>::getMicroseconds(unsigned long ticks)
{
	return ticks * 1000;
}

//template<>
//unsigned long Time<Microseconds>::Update()
//{
//	unsigned long previous = _ticks;
//
//	_ticks = micros();
//
//	return _ticks - previous;
//}

template<>
inline static unsigned long Time<Microseconds>::getMilliseconds(unsigned long ticks)
{
	return ticks / 1000;
}

template<>
inline static unsigned long Time<Microseconds>::getMicroseconds(unsigned long ticks)
{
	return ticks;
}

/*
	The TimeEx class adds start-time and delta-time keeping.
 */
template<TimeResolution resolution = Milliseconds>
class TimeEx : public Time<resolution>
{
public:

	/*
		Initializes a new instance.
	 */
	TimeEx() 
	{
		Reset();
	}

	/*
		Resets the start time.
	 */
	void Reset()
	{
		_start = _previous = Time<resolution>::getTicks();
	}

	/*
		Updates the time ticks (Time<>) and delta time.
	 */
	unsigned long Update()
	{
		_previous = Time<resolution>::getTicks();

		return Time<resolution>::Update();
	}

	/*
		Returns the start time in milli-seconds.
	 */
	inline unsigned long getStartMilliseconds() const
	{
		return Time<resolution>::getMilliseconds(_start);
	}

	/*
		Returns the start time in micro-seconds.
	 */
	inline unsigned long getStartMicroseconds() const
	{
		return Time<resolution>::getMicroseconds(_start);
	}

	/*
		Returns the delta-time in ticks.
	 */
	inline unsigned int getDeltaTime() const
	{
		return (unsigned int)(Time<resolution>::getTicks() - _previous);
	}

private:
	unsigned long _start;
	unsigned long _previous;
};

} //ATL

#endif //__TIME_H__
