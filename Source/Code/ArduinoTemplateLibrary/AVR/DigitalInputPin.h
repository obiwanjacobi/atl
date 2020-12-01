/*
Arduino Template Library https://github.com/obiwanjacobi/atl
Written by Marc Jacobi
Copyright 2012-2015 All Rights Reserved

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


#ifndef __DIGITALINPUTPIN_H__
#define __DIGITALINPUTPIN_H__

#include <stdint.h>
#include "Port.h"

namespace ATL {
namespace MCU {

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

}} // ATL::MCU


#endif /* __DIGITALINPUTPIN_H__ */