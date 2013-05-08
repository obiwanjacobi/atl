#ifndef __ANALOGOUTPUTPIN_H__
#define __ANALOGOUTPUTPIN_H__

#include <Arduino.h>

namespace ATL {

template<const byte BoardPinNumber>
class AnalogOutputPin : DigitalOutputPin<BoardPinNumber>
{
public:
	void Write(byte value)
	{
		analogWrite(BoardPinNumber, value);
	}
};

} // ATL

#endif //__ANALOGOUTPUTPIN_H__