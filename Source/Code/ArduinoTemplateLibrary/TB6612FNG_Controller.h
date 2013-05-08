#ifndef __TB6612FNG_CONTROLLER_H__
#define __TB6612FNG_CONTROLLER_H__

#include "MotorTypes.h"

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
	void Drive(MotorMode::MotorMode mode, unsigned char speed)
	{
		switch(mode)
		{
		case MotorMode::Stop:
			Stop();
			break;

		case MotorMode::Break:
			Break();
			break;

		case MotorMode::Clockwise:
			Clockwise(speed);
			break;

		case MotorMode::CounterClockwise:
			CounterClockwise(speed);
			break;
		}
	}

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