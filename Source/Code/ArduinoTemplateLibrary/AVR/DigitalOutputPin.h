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


#ifndef __DIGITALOUTPUTPIN_H__
#define __DIGITALOUTPUTPIN_H__

#include <stdint.h>
#include "Port.h"

namespace ATL {
namespace MCU {


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

}} // ATL::MCU



#endif /* __DIGITALOUTPUTPIN_H__ */