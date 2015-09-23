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

#ifndef __HD44780_PROFILE_H__
#define __HD44780_PROFILE_H__

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
            //delay(50);
            delay(10);
        }

        /** Performs a delay that is part of the full initialization.
         */
        inline static void WaitInitializeLong()
        {
            //delayMicroseconds(4100);
            delayMicroseconds(1000);
        }

        /** Performs a delay that is part of the full initialization.
         */
        inline static void WaitInitialize()
        {
            //delayMicroseconds(100);
            delayMicroseconds(30);
        }

        /** Performs a delay that is part of the full initialization.
         */
        inline static void WaitInitializeShort()
        {
            //delayMicroseconds(40);
            delayMicroseconds(20);
        }

        /** Performs a delay the display needs to process a command.
         */
        inline static void WaitForCommand()
        {
            //delayMicroseconds(40);
            delayMicroseconds(15);
        }

        /** Performs a delay the display needs to process a command.
         */
        inline static void WaitForCommandLong()
        {
            //delayMicroseconds(1640);
            delayMicroseconds(800);
        }

        /** Performs a delay the display needs to read the enable line.
         */
        inline static void WaitPulseEnable()
        {
            //delayMicroseconds(37);
            delayMicroseconds(8);
        }

    private:
        HD44780_Profile()
        { }
    };

} // ATL

#endif //__HD44780_PROFILE_H__