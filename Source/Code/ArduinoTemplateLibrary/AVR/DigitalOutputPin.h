/*
 * DigitalOutputPin.h
 *
 * Created: 10-5-2015 08:51:49
 *  Author: Marc
 */


#ifndef DIGITALOUTPUTPIN_H_
#define DIGITALOUTPUTPIN_H_

#include "Port.h"

namespace ATL {


/*
	Initializes a BoardPinNumber to output.
 */
template<const Ports PortId, const Pins PinId>
class DigitalOutputPin
{
public:
	/*
		The ctor sets the Pin on the Port to Output.
	 */
	DigitalOutputPin()
	{
		Port<PortId>::SetDirection(PinId, Output);
        //Write(false);
	}

	/*
		The ctor sets the pinMode and initialValue.
	 */
	DigitalOutputPin(bool initialValue)
	{
		Port<PortId>::SetDirection(PinId, Output);
		Write(initialValue);
	}

	/*
		Writes the value to the BoardPinNumder.
	 */
	inline void Write(bool value) const
	{
		Port<PortId>::Write(PinId, value);
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



#endif /* DIGITALOUTPUTPIN_H_ */