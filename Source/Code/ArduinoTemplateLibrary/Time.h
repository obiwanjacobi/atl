/*
Arduino Template Library https://github.com/obiwanjacobi/atl
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

#include <stdint.h>
#include "EnumScope.h"

namespace ATL {

    /** Time resolution in either milli-seconds or micro-seconds.
     */
    BeginEnum(TimeResolution)
    {
        /** Time units are milliseconds. */
        Milliseconds,
        /** Time units are microseconds. */
        Microseconds
    }
    EndEnum(TimeResolution)

    /** The Time class keeps track of time ticks (either milli- or micro-seconds).
     *  \tparam TimeResolution indicates the time units.
     */
    template<const TimeResolution::type resolution = TimeResolution::Milliseconds>
    class Time
    {
    public:

        /** Constructs a new instance.
         */
        Time() 
            : _ticks(0)
        {
            Update();
        }

        /** Captures the time ticks.
         *  \return Returns delta-time in 'resolution'
         */
        inline uint32_t Update();

        /** Returns the time ticks in milli-seconds.
         */
        inline uint32_t getMilliseconds() const
        {
            return getMilliseconds(_ticks);
        }

        /** Returns the time ticks in micro-seconds.
         */
        inline uint32_t getMicroseconds() const
        {
            return getMicroseconds(_ticks);
        }

        /** Returns the TimeResolution template parameter.
         */
        inline TimeResolution getResolution() const 
        {
            return resolution;
        }

    protected:

        /** Returns the raw time ticks.
         */
        inline uint32_t getTicks() const 
        {
            return _ticks;
        }

        /** Returns the ticks in milli-seconds.
         */
        inline static uint32_t getMilliseconds(uint32_t ticks);

        /** Returns the ticks in micro-seconds.
         */
        inline static uint32_t getMicroseconds(uint32_t ticks);

    private:
        uint32_t _ticks;
    };

    // Time template specializations

    /** Specialization for Time in Milliseconds.
     */
    template<>
    inline uint32_t Time<TimeResolution::Milliseconds>::getMilliseconds(uint32_t ticks)
    {
        return ticks;
    }

    /** Specialization for Time in Milliseconds.
     */
    template<>
    inline uint32_t Time<TimeResolution::Milliseconds>::getMicroseconds(uint32_t ticks)
    {
        return ticks * 1000;
    }

    /** Specialization for Time in Microseconds.
     */
    template<>
    inline uint32_t Time<TimeResolution::Microseconds>::getMilliseconds(uint32_t ticks)
    {
        return ticks / 1000;
    }

    /** Specialization for Time in Microseconds.
     */
    template<>
    inline uint32_t Time<TimeResolution::Microseconds>::getMicroseconds(uint32_t ticks)
    {
        return ticks;
    }

    /** The TimeEx class adds start-time and delta-time members to Time.
     *  \tparam TimeResolution indicates the time units.
     */
    template<TimeResolution::type resolution = TimeResolution::Milliseconds>
    class TimeEx : public Time<resolution>
    {
    public:
        /** Initializes a new instance.
         */
        TimeEx() 
        {
            Reset();
        }

        /** Resets the start time.
         */
        inline void Reset()
        {
            _start = _previous = Time<resolution>::getTicks();
        }

        /** Updates the time ticks (Time<>) and delta time.
         *  \returns Returns the delta-time.
         */
        inline uint32_t Update()
        {
            _previous = Time<resolution>::getTicks();

            return Time<resolution>::Update();
        }

        /** Returns the start time in milli-seconds.
         */
        inline uint32_t getStartMilliseconds() const
        {
            return Time<resolution>::getMilliseconds(_start);
        }

        /** Returns the start time in micro-seconds.
         */
        inline uint32_t getStartMicroseconds() const
        {
            return Time<resolution>::getMicroseconds(_start);
        }

        /** Returns the delta-time in ticks.
         */
        inline uint16_t getDeltaTime() const
        {
            return (uint16_t)(Time<resolution>::getTicks() - _previous);
        }

    private:
        uint32_t _start;
        uint32_t _previous;
    };

} //ATL

#endif //__TIME_H__
