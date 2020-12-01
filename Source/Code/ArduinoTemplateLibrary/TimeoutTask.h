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

#ifndef __TIMEOUTTASK_H__
#define __TIMEOUTTASK_H__

#include <stdint.h>
#include "Delays.h"
#include "Task.h"

namespace ATL {

    /** The TimeoutTask counts a timer down asynchronously (non-blocking).
     *  Calls the BaseT::OnTimeout when the Timeout has expired.
     *  Call the Execute method repeatedly.
     *  \tparam BaseT is used as a base class and implements:
     *  `void OnTimeout()`
     *  `uint16_t getId()` (IdentifiableObject).
     *  \tparam DelaysT is a Delays<> type used to keep track of timeouts.
     *  \tparam Timeout is specified in the same quantity as the DelaysT is specified (Milli- or MicroSeconds).
     */
    template<class BaseT, typename DelaysT, const uint32_t Timeout>
    class TimeoutTask : public BaseT
    {
    public:
        /** Constructs the instance.
         */
        TimeoutTask()
            : _task(0)
        { }

        /** Call this method repeatedly from the main loop.
         *  Each time the Timeout expires the BaseT::OnTimeout() method is called.
         */
        Task_Begin(Execute)
        {
            while (true)
            {
                Task_YieldUntil(DelaysT::Wait(BaseT::getId(), Timeout));
                BaseT::OnTimeout();
            }
        }
        Task_End

        /** Returns the Timeout template parameter.
         */
        inline uint32_t getTimeout() const
        {
            return Timeout;
        }

    private:
        uint16_t _task; // required by the Task macros
    };

} // ATL

#endif //__TIMEOUTTASK_H__