/*
 * DigitalInputPin.h
 *
 * Created: 10-5-2015 08:51:31
 *  Author: Marc
 */


#ifndef DIGITALINPUTPIN_H_
#define DIGITALINPUTPIN_H_

#include "Port.h"

namespace ATL {

/*
	Initializes a Pin on a Port to input.
 */
template <const Ports PortId, const Pins PinId>
class DigitalInputPin
{
public:
	/*
		The ctor sets the Pin as Input.
	 */
	DigitalInputPin()
	{
		Port<PortId>::SetDirection(PinId, Input);
	}

	/*
		Reads the value from the Pin on the Port.
	 */
	inline bool Read()
	{
		return Port<PortId>::Read(PinId);
	}

	/*
		Enables (true) or disables (false) the internal pull-up resistor the AVR (MCU) has on digital input pins.
	 */
	inline void EnableInternalPullup(bool enable = true)
	{
		Port<PortId>::EnablePullup(PinId, enable);
	}

    /*
		Returns the PortId template parameter.
	 */
	inline uint8_t getPortNumber() const
	{
		return PortId;
	}

	/*
		Returns the PinId template parameter.
	 */
	inline uint8_t getPinNumber() const
	{
		return PinId;
	}
};

} // ATL


#endif /* DIGITALINPUTPIN_H_ */