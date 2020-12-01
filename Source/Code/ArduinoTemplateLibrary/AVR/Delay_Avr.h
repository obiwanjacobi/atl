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


#ifndef __DELAY_MCU_H__
#define __DELAY_MCU_H__


#include <util/delay.h>
#include "../Delay.h"

namespace ATL {

    /** Specialization of the Delay class for Milliseconds.
     */
    template<>
    class Delay<TimeResolution::Milliseconds>
    {
    public:
        /** Blocks execution for a period of timeout in the specified TimeRes.
         *  \param timeout the amount of time to wait.
         */
        inline static void Wait(uint32_t timeout)
        {
            _delay_ms(timeout);
        }
    };

    /** Specialization of the Delay class for Microseconds.
     */
    template<>
    class Delay<TimeResolution::Microseconds>
    {
    public:
        /** Blocks execution for a period of timeout in the specified TimeRes.
         *  \param timeout the amount of time to wait.
         */
        inline static void Wait(uint32_t timeout)
        {
            _delay_us(timeout);
        }
    };

} // ATL

#endif /* __DELAY_MCU_H__ */