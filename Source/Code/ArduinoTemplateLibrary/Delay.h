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


#ifndef __DELAY_H__
#define __DELAY_H__

#include "Time.h"

namespace ATL {

    /** The Delay class abstracts how a synchronous delay is performed.
     *  It is a static class and cannot be instantiated.
     *  \tparam TimeRes is the TimeResolution in milli- or micro-seconds.
     */
    template<const TimeResolution::type TimeRes>
    class Delay
    {
    public:
        /** Blocks execution for a period of timeout in the specified TimeRes.
         *  \param timeout the amount of time to wait.
         */
        inline static void Wait(uint32_t timeout);
    };

        
} // ATL

#endif /* __DELAY_H__ */