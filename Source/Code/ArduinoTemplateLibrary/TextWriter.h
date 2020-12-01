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

#ifndef __TEXTWRITER_H__
#define __TEXTWRITER_H__

#include <stdint.h>
#include "TextFormatInfo.h"

namespace ATL {

    /** The TextWriter class writes textual representations to a
     *  \tparam BaseT is derived from and implements 'void Write(byte)'.
     *  \tparam FormatInfoT implements all the public static fields defined by TextFormatInfo
     */
    template<class BaseT, class FormatInfoT = TextFormatInfo>
    class TextWriter : public BaseT
    {
    public:
        /** Writes the char value to the out stream as is.
         *  \param value is the character to write.
         */
        inline void Write(const char value)
        {
            Write((int16_t)value);
        }

        /** Writes a textual representation for the value.
         *  \param value is the number to convert to string.
         */
        inline void Write(const uint8_t value)
        {
            Write((uint16_t)value);
        }

        /** Writes a string to the out stream as is.
         *  Does NOT write the terminating zero!
         *  \param str points to the string to write.
         */
        inline void Write(const char str[])
        {
            const char* strPos = str;

            while (*strPos != '\0')
            {
                BaseT::Write(*strPos);
                strPos++;
            }
        }

        /** Writes a textual representation for the value.
         *  \param value is the number to convert to string.
         */
        inline void Write(const int16_t value)
        {
            // test for negative with decimals
            if (FormatInfoT::DefaultBase == TextFormatInfo::baseDecimal)
            {
                if (value < 0)
                {
                    BaseT::Write(FormatInfoT::NegativeSign);
                    WriteInt(-value, FormatInfoT::DefaultBase);
                }
                else
                {
                    WriteInt(value, FormatInfoT::DefaultBase);
                }
            }
            else
            {
                return WriteInt(value, FormatInfoT::DefaultBase);
            }
        }

        /** Writes a textual representation for the value.
         *  \param value is the number to convert to string.
         */
        inline void Write(const uint16_t value)
        {
            WriteInt(value, FormatInfoT::DefaultBase);
        }

        /** Writes a textual representation for the value.
         *  \param value is the number to convert to string.
         */
        void Write(const int32_t value)
        {
            // test for negative with decimals
            if (FormatInfoT::DefaultBase == TextFormatInfo::baseDecimal)
            {
                if (value < 0)
                {
                    BaseT::Write(FormatInfoT::NegativeSign);
                    WriteLong(-value, FormatInfoT::DefaultBase);
                }
                else
                {
                    WriteLong(value, FormatInfoT::DefaultBase);
                }
            }
            else
            {
                return WriteLong(value, FormatInfoT::DefaultBase);
            }
        }

        /** Writes a textual representation for the value.
         *  \param value is the number to convert to string.
         */
        inline void Write(const uint32_t value)
        {
            WriteLong(value, FormatInfoT::DefaultBase);
        }

        /** Writes a textual representation for the value.
         *  \param value is the number to convert to string.
         */
        inline void Write(const float value)
        {
            WriteReal(value, FormatInfoT::DecimalDigits);
        }

        /** Writes a textual representation for the value.
         *  \param value is the number to convert to string.
         */
        inline void Write(const double value)
        {
            WriteReal(value, FormatInfoT::DecimalDigits);
        }

        /** Writes a the NewLine characters to the out stream.
         */
        inline void WriteLine()
        {
            Write(FormatInfoT::NewLine);
        }

        /** Writes the char value to the out stream as is followed by a NewLine.
         *  \param value is the character to write.
         */
        inline void WriteLine(const char value)
        {
            Write(value);
            WriteLine();
        }

        /** Writes a textual representation for the value followed by a NewLine.
         *  \param value is the number to convert to string.
         */
        inline void WriteLine(const uint8_t value)
        {
            Write(value);
            WriteLine();
        }

        /** Writes a string to the out stream as is followed by a NewLine.
         *  Does NOT write the terminating zero!
         *  \param str points to the string to write.
         */
        inline void WriteLine(const char str[])
        {
            Write(str);
            WriteLine();
        }

        /** Writes a textual representation for the value followed by a NewLine.
         *  \param value is the number to convert to string.
         */
        inline void WriteLine(const int16_t value)
        {
            Write(value);
            WriteLine();
        }

        /** Writes a textual representation for the value followed by a NewLine.
         *  \param value is the number to convert to string.
         */
        inline void WriteLine(const uint16_t value)
        {
            Write(value);
            WriteLine();
        }

        /** Writes a textual representation for the value followed by a NewLine.
         *  \param value is the number to convert to string.
         */
        inline void WriteLine(const int32_t value)
        {
            Write(value);
            WriteLine();
        }

        /** Writes a textual representation for the value followed by a NewLine.
         *  \param value is the number to convert to string.
         */
        inline void WriteLine(const uint32_t value)
        {
            Write(value);
            WriteLine();
        }

        /** Writes a textual representation for the value followed by a NewLine.
         *  \param value is the number to convert to string.
         */
        inline void WriteLine(const float value)
        {
            Write(value);
            WriteLine();
        }

    private:
        inline void WriteInt(uint16_t integer, uint8_t base)
        {
            // an int is 2^32 and has 10 digits + terminating 0
            WriteInternal<unsigned int, 11>(integer, base);
        }

        inline void WriteLong(uint32_t integer, uint8_t base)
        {
            // a long is 2^64 and has 20 digits + terminating 0
            WriteInternal<uint32_t, 21>(integer, base);
        }

        template<typename T, const uint8_t bufferSize>
        void WriteInternal(T integer, uint8_t base)
        {
            char buffer[bufferSize];
            char* strPos = &buffer[sizeof(buffer) - 1];

            // we fill the buffer from back to front.
            *strPos = '\0';

            // safety check for base values that crash
            // base == 0 -> divide by zero
            // base == 1 -> endless loop
            if (base < 2) base = 10;

            do
            {
                T remainder = integer;
                integer /= base;

                char c = (char)(remainder - base * integer);
                *--strPos = c < 10 ? c + '0' : c + 'A' - 10;
            }
            while (integer != 0);

            Write(strPos);
        }

        void WriteReal(double real, uint8_t digits)
        {
            if (real < 0.0)
            {
                BaseT::Write(FormatInfoT::NegativeSign);
                real = -real;
            }

            double rounding = 0.5;

            if (digits > 0)
            {
                for (int n = 0; n < digits; n++)
                {
                    rounding /= 10.0;
                }
            }

            real += rounding;

            // integral part
            uint32_t integer = (uint32_t)real;
            double remainder = real - (double)integer;
            WriteLong(integer, TextFormatInfo::baseDecimal);

            if (digits > 0)
            {
                // decimal point
                BaseT::Write(FormatInfoT::DecimalSeparator);

                // decimals
                while (digits > 0)
                {
                    remainder *= 10.0;
                    uint16_t number = (unsigned int)remainder;
                    WriteInt(number, TextFormatInfo::baseDecimal);
                    remainder -= number;

                    digits--;
                }
            }
        }
    };

} // ATL

#endif // __TEXTWRITER_H__