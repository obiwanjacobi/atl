#ifndef __DIGITALOUTPUTPIN_H__
#define __DIGITALOUTPUTPIN_H__

#include <Arduino.h>

namespace ATL {

template<byte BoardPinNumber>
class DigitalOutputPin
{
public:
	DigitalOutputPin()
	{
		pinMode(BoardPinNumber, OUTPUT);
	}

	void Write(bool value)
	{
		digitalWrite(BoardPinNumber, value);
	}
};

} // ATL

#endif //__DIGITALOUTPUTPIN_H__