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

#ifndef __STATICSTRING_H__
#define __STATICSTRING_H__

#include <avr/pgmspace.h>
#include <stdint.h>

namespace ATL {

    /** The StaticString class contains a string stored in PROGMEM.
     */
    class StaticString
    {
    public:
        // declare PROGMEM string and pass in the var
        /** Constructs an initialized instance.
         *  Declare a PROGMEM array and pass in the variable.
         *  \param str points to the PROGMEM string.
         */
        StaticString(const char* str)
            : _str(str)
        { }

        /** Reads the entire string from PROGMEM.
         *  \param target points to a buffer that will receive the string.
         *  \param targetLen indicates the size of the target buffer.
         */
        inline void Read(char* target, size_t targetLen)
        {
            strncpy_P(target, _str, targetLen);
        }

    private:
        const char* _str;
    };

} // ATL

#endif //__STATICSTRING_H__