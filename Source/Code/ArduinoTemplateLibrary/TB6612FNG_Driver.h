#ifndef __TB6612FNG_DRIVER_H__
#define __TB6612FNG_DRIVER_H__

#include "MotorTypes.h"

#include "DigitalOutputPin.h"
#include "AnalogOutputPin.h"

namespace ATL {
namespace Hardware {
namespace Motor {

/*
	This driver class writes to one port of a Toshiba TB6612FNG - a dual 1A motor driver/controller.
	Use two instances of this class to drive both channels of the chip.

	The class implements the IO routines for direct connection onto an Arduino.
	Implement your own class when you have multiplexing in between the IO pins.
*/

template<const unsigned char In1_BoardPinNumber, const unsigned char In2_BoardPinNumber, const unsigned char Pwm_BoardPinNumber>
class TB6612FNG_Driver
{
public:
	void Send(bool in1, bool in2, unsigned char pwm)
	{
		_in1.Write(in1);
		_in2.Write(in1);

		if (pwm > 0)
		{
			_pwm.Write(pwm);
		}
		else
		{
			_pwm.Write(true);
		}
	}

private:
	DigitalOutputPin<In1_BoardPinNumber> _in1;
	DigitalOutputPin<In2_BoardPinNumber> _in2;
	AnalogOutputPin<Pwm_BoardPinNumber> _pwm;
};

}}} // ATL.Hardware.Motor

#endif //__TB6612FNG_DRIVER_H__