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

#ifndef __HD44780_PROFILE_H__
#define __HD44780_PROFILE_H__

#include "Delay.h"

namespace ATL {

    /** The HD44780_Profile class contains static methods that perform synchronous delays used for timing the digital signals to the LCD display.
     *  It is a static class and cannot be instantiated.
     */
    class HD44780_Profile
    {
    public:
        /** Performs a delay the display needs to power up.
         */
        inline static void WaitPowerUp()
        {
            //Delay<TimeResolution::Milliseconds>::Wait(50);
            Delay<TimeResolution::Milliseconds>::Wait(10);
        }

        /** Performs a delay that is part of the full initialization.
         */
        inline static void WaitInitializeLong()
        {
            //Delay<TimeResolution::Microseconds>::Wait(4100);
            Delay<TimeResolution::Microseconds>::Wait(1000);
        }

        /** Performs a delay that is part of the full initialization.
         */
        inline static void WaitInitialize()
        {
            //Delay<TimeResolution::Microseconds>::Wait(100);
            Delay<TimeResolution::Microseconds>::Wait(30);
        }

        /** Performs a delay that is part of the full initialization.
         */
        inline static void WaitInitializeShort()
        {
            //Delay<TimeResolution::Microseconds>::Wait(40);
            Delay<TimeResolution::Microseconds>::Wait(20);
        }

        /** Performs a delay the display needs to process a command.
         */
        inline static void WaitForCommand()
        {
            //Delay<TimeResolution::Microseconds>::Wait(40);
            Delay<TimeResolution::Microseconds>::Wait(15);
        }

        /** Performs a delay the display needs to process a command.
         */
        inline static void WaitForCommandLong()
        {
            //Delay<TimeResolution::Microseconds>::Wait(1640);
            Delay<TimeResolution::Microseconds>::Wait(800);
        }

        /** Performs a delay the display needs to read the enable line.
         */
        inline static void WaitPulseEnable()
        {
            //Delay<TimeResolution::Microseconds>::Wait(37);
            Delay<TimeResolution::Microseconds>::Wait(8);
        }

    private:
        HD44780_Profile() { }
    };

} // ATL

#endif //__HD44780_PROFILE_H__