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

#ifndef __TIME_ARDUINO_H__
#define __TIME_ARDUINO_H__

#include <stdint.h>
#include "..\Time.h"

namespace ATL {

    /** Specialized implementation that updates the Milliseconds.
     *  \return Returns the delta milliseconds that have elapsed since the last call.
     */
    template<>
    uint32_t Time<TimeResolution::Milliseconds>::Update()
    {
        uint32_t previous = _ticks;

        _ticks = millis();

        return _ticks - previous;
    }

    /** Specialized implementation that updates the Microseconds.
     *  \return Returns the delta micorseconds that have elapsed since the last call.
     */
    template<>
    uint32_t Time<TimeResolution::Microseconds>::Update()
    {
        uint32_t previous = _ticks;

        _ticks = micros();

        return _ticks - previous;
    }

} // ATL

#endif //__TIME_ARDUINO_H__