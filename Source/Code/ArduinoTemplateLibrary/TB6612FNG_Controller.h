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

#ifndef __TB6612FNG_CONTROLLER_H__
#define __TB6612FNG_CONTROLLER_H__

#include <stdint.h>

namespace ATL {

    /** The controller class implements the logic of how to talk to the TB6612FNG chip
     *  but leaving the details of how the chip is actually connected to the driver class.
     *  See also the TB6612FNG_Driver template class.
     *  \tparam BaseT is used as a base class and implements:
     *  `void Send(bool in1, bool in2, uint8_t pwm)` (TB6612FNG_Driver)
     */
    template<class BaseT>
    class TB6612FNG_Controller : public BaseT
    {
    public:
        /** Sends a stop command.
         */
        inline void Stop()
        {
            BaseT::Send(false, false, 0);
        }

        /** Sends a break command.
         */
        inline void Break()
        {
            BaseT::Send(true, true, 0);
        }

        /** Sends a 'turn the motor clockwise' command.
         *  \param speed is value between 0 (slow) and 255 (fast).
         */
        inline void Clockwise(uint8_t speed)
        {
            BaseT::Send(true, false, speed);
        }

        /** Sends a 'turn the motor counter-clockwise' command.
         *  \param speed is value between 0 (slow) and 255 (fast).
         */
        inline void CounterClockwise(uint8_t speed)
        {
            BaseT::Send(false, true, speed);
        }
    };

} // ATL

#endif //__TB6612FNG_CONTROLLER_H__