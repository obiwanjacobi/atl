/*  
	Arduino Template Library http://atl.codeplex.com
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

#include "TextFormatInfo.h"

namespace ATL {

/*
	BaseT implements void [IO]Write(byte).
	FormatInfoT implements all the public static fields defined by TextFormatInfo
*/
template<class BaseT, class FormatInfoT = TextFormatInfo>
class TextWriter : public BaseT
{
public:
	inline void Write(const char value)
	{
		Write((int)value);
	}

	inline void Write(const unsigned char value)
	{
		Write((unsigned int)value);
	}

	// does NOT write the terminating zero!
	inline void Write(const char str[])
	{
		const char* strPos = str;

		while (*strPos != '\0')
		{
			BaseT::Write(*strPos);
			strPos++;
		}
	}

	inline void Write(const int value)
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

	inline void Write(const unsigned int value)
	{
		WriteInt(value, FormatInfoT::DefaultBase);
	}

	void Write(const long value)
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

	inline void Write(const unsigned long value)
	{
		WriteLong(value, FormatInfoT::DefaultBase);
	}

	inline void Write(const float value)
	{
		WriteReal(value, FormatInfoT::DecimalDigits);
	}

	inline void Write(const double value)
	{
		WriteReal(value, FormatInfoT::DecimalDigits);
	}

	inline void WriteLine()
	{
		Write(FormatInfoT::NewLine);
	}

	inline void WriteLine(const char value)
	{
		Write(value);
		WriteLine();
	}

	inline void WriteLine(const unsigned char value)
	{
		Write(value);
		WriteLine();
	}

	inline void WriteLine(const char str[])
	{
		Write(str);
		WriteLine();
	}

	inline void WriteLine(const int value)
	{
		Write(value);
		WriteLine();
	}

	inline void WriteLine(const unsigned int value)
	{
		Write(value);
		WriteLine();
	}

	inline void WriteLine(const long value)
	{
		Write(value);
		WriteLine();
	}

	inline void WriteLine(const unsigned long value)
	{
		Write(value);
		WriteLine();
	}

	inline void WriteLine(const float value)
	{
		Write(value);
		WriteLine();
	}

private:
	void WriteInt(unsigned int integer, unsigned char base)
	{
		// an int is 2^32 and has 10 digits + terminating 0
		WriteInternal<unsigned int, 11>(integer, base);
	}

	void WriteLong(unsigned long integer, unsigned char base)
	{
		// a long is 2^64 and has 20 digits + terminating 0
		WriteInternal<unsigned long, 21>(integer, base);
	}

	template<typename T, const unsigned char bufferSize>
	void WriteInternal(T integer, unsigned char base)
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

	void WriteReal(double real, unsigned char digits)
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
		unsigned long integer = (unsigned long)real;
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
				unsigned int number = (unsigned int)remainder;
				WriteInt(number, TextFormatInfo::baseDecimal);
				remainder -= number;

				digits--;
			}
		}
	}
};

} // ATL

#endif // __TEXTWRITER_H__