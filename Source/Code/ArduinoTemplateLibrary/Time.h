/*  
	Arduino Template Library http://atl.codeplex.com
	Written by Marc Jacobi
	Copyright 2012-2013 All Rights Reserved

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
	TimeEx() : _previous(0)
	{
		_start = Time<resolution>::getTicks();
	}

	unsigned long Update()
	{
		_previous = Time<resolution>::getTicks();
		return Time<resolution>::Update();
	}

	inline unsigned long getStartMilliseconds() const
	{
		return Time<resolution>::getMilliseconds(_start);
	}

	inline unsigned long getStartMicroseconds() const
	{
		return Time<resolution>::getMicroseconds(_start);
	}

	inline unsigned long getPreviousMilliseconds() const
	{
		return Time<resolution>::getMilliseconds(_previous);
	}

	inline unsigned long getPreviousMicroseconds() const
	{
		return Time<resolution>::getMicroseconds(_previous);
	}

private:
	unsigned long _start;
	unsigned long _previous;
};

} //ATL

#endif //__TIME_H__