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

#ifndef __TB6612FNG_CONTROLLER_H__
#define __TB6612FNG_CONTROLLER_H__

namespace ATL {
namespace Hardware {
namespace Motor {

/*
	BaseT is used as a base class and implements:
		void Send(bool in1, bool in2, byte pwm);
	See also the TB6612FNG_Driver template class.

	The controller class implements the logic of how to talk to the chip
	but leaving the details of of the chip is actually connected to the driver class.
*/
template<class BaseT>
class TB6612FNG_Controller : public BaseT
{
public:
	inline void Stop()
	{
		BaseT::Send(false, false, 0);
	}

	inline void Break()
	{
		BaseT::Send(true, true, 0);
	}

	inline void Clockwise(unsigned char speed)
	{
		BaseT::Send(true, false, speed);
	}

	inline void CounterClockwise(unsigned char speed)
	{
		BaseT::Send(false, true, speed);
	}
};

}}} // ATL.Hardware.Motor

#endif //__TB6612FNG_CONTROLLER_H__