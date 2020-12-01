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

#ifndef __SERIALI2COUTPUT_H__
#define __SERIALI2COUTPUT_H__

#include <Wire.h>

namespace ATL {

    // wrapper class around Arduino Wire library.
    template<const uint8_t I2CAddress>
    class SerialI2COutput
    {
    public:
        inline bool Write(uint8_t data)
        {
            Wire.beginTransmission(I2CAddress);
            Wire.write(data);
            return Wire.endTransmission() == 0;
        }
    
        inline bool Write(uint8_t data[], uint8_t length)
        {
            Wire.beginTransmission(I2CAddress);
            Wire.write(data, length);
            return Wire.endTransmission() == 0;
        }

        inline uint8_t getI2CAddress() const
        {
            return I2CAddress;
        }
    };

} // ATL

#endif // __SERIALI2COUTPUT_H__

