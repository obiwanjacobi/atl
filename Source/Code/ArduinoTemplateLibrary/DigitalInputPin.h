#ifndef __DIGITALINPUTPIN_H__
#define __DIGITALINPUTPIN_H__

#include <Arduino.h>

namespace ATL {

template <const byte BoardPinNumber>
class DigitalInputPin
{
public:
	DigitalInputPin()
	{
		pinMode(BoardPinNumber, INPUT);
	}

	bool Read()
	{
		return digitalRead(BoardPinNumber);
	}

	// Enables (true) or disables (false) the internal pullup resistor the Arduino has on digital input pins.
	inline void EnableInternalPullup(bool enable = true)
	{
		digitalWrite(BoardPinNumber, enable);
	}
};

} // ATL

#endif //__DIGITALINPUTPIN_H__