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

#ifndef __TEXTFORMATINFO_H__
#define __TEXTFORMATINFO_H__

#include <stdint.h>

namespace ATL {

    /** This class defines regional number-settings.
     *  See also TextWriter.
     */
    class TextFormatInfo
    {
    public:
        /** Common bases for displaying decimal numbers as text.
         *  
         */
        enum BaseTypes
        {
            /** Not set. */
            baseNone = 0,
            /** Binary (2). */
            baseBinary = 2,
            /** Octal (8). */
            baseOctal = 8,
            /** Decimal (10). */
            baseDecimal = 10,
            /** Hexadecimal (16). */
            baseHexadecimal = 16,
        };

        /** The characters that constitute a new-line. */
        static char NewLine[];
        /** The number of decimal places to display for floating point numbers. */
        static uint8_t DecimalDigits;
        /** The character that represents a negative sign. */
        static char NegativeSign;
        /** The character that represents the decimal point. */
        static char DecimalSeparator;
        /** The default BaseTypes value to use when non is specified. */
        static uint8_t DefaultBase;
    };

    char TextFormatInfo::NewLine[] = { '\n', '\r', '\0' };
    uint8_t TextFormatInfo::DecimalDigits = (uint8_t )2;
    char TextFormatInfo::NegativeSign = { '-' };
    char TextFormatInfo::DecimalSeparator = { '.' } ;
    uint8_t TextFormatInfo::DefaultBase = (uint8_t )baseDecimal;

} // ATL

#endif //__TEXTFORMATINFO_H__