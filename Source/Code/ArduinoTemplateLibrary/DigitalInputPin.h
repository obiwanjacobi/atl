#ifndef __DIGITALINPUTPIN_H__
#define __DIGITALINPUTPIN_H__

#include <Arduino.h>

namespace ATL {

template <byte BoardPinNumber>
class DigitalInputPin
{
public:
	DigitalInputPin()
	{
		pinMode(BoardPinNumber, INPUT);
	}

	bool Read() const
	{
		return digitalRead(BoardPinNumber);
	}

	// Enables (true) or disables (false) the internal pullup resistor the Arduino has on digital input pins.
	inline void EnableInternalPullup(bool enable = true) const
	{
		digitalWrite(BoardPinNumber, enable);
	}
};

} // ATL

#endif //__DIGITALINPUTPIN_H__