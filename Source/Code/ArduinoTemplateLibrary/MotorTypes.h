#ifndef __MOTORTYPES_H__
#define __MOTORTYPES_H__

namespace ATL {
namespace Hardware {
namespace Motor {

// A generic indication of what a motor can do.
// TOOD: stepper motors?
namespace MotorMode
{
	enum MotorMode
	{
		Stop,
		Break,
		Clockwise,
		CounterClockwise,
	};
} // MotorMode




}}} // ATL.Hardware.Motor

#endif //__MOTORTYPES_H__

