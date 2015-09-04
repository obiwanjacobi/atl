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

#include <Arduino.h>

namespace ATL {
namespace Hardware {
namespace Display {

/*
	Timing profile class for the HD44780 LCD display.
*/
class HD44780_Profile
{
public:
	inline static void WaitPowerUp()
	{
		//delay(50);
		delay(10);
	}

	inline static void WaitInitializeLong()
	{
		//delayMicroseconds(4100);
		delayMicroseconds(1000);
	}

	inline static void WaitInitialize()
	{
		//delayMicroseconds(100);
		delayMicroseconds(30);
	}

	inline static void WaitInitializeShort()
	{
		//delayMicroseconds(40);
		delayMicroseconds(20);
	}

	inline static void WaitForCommand()
	{
		//delayMicroseconds(40);
		delayMicroseconds(15);
	}

	inline static void WaitForCommandLong()
	{
		//delayMicroseconds(1640);
		delayMicroseconds(800);
	}

	inline static void WaitPulseEnable()
	{
		//delayMicroseconds(37);
		delayMicroseconds(8);
	}
};

}}} // ATL::Hardware::Display

#endif //__HD44780_PROFILE_H__