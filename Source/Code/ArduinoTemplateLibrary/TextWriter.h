#ifndef __TEXTWRITER_H__
#define __TEXTWRITER_H__

#include <Arduino.h>
#include "TextFormatInfo.h"

/*
	BaseT implements void Write(byte).
	FormatInfoT implements all the public static fields defined by TextFormatInfo
*/
template<class BaseT, class FormatInfoT = TextFormatInfo>
class TextWriter : public BaseT
{
public:
	inline void Write(char value)
	{
		Write((int)value);
	}

	inline void Write(unsigned char value)
	{
		Write((unsigned int)value);
	}

	// does NOT write the terminating zero!
	inline void Write(const char str[])
	{
		const char* strPos = str;

		do
		{
			if (*strPos != '\0')
			{
				BaseT::Write(*strPos);
			}
		}
		while (*strPos++ != '\0');
	}

	inline void Write(int value)
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

	inline void Write(unsigned int value)
	{
		WriteInt(value, FormatInfoT::DefaultBase);
	}

	void Write(long value)
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

	inline void Write(unsigned long value)
	{
		WriteLong(value, FormatInfoT::DefaultBase);
	}

	inline void Write(float value)
	{
		WriteReal(value, FormatInfoT::DecimalDigits);
	}

	inline void Write(double value)
	{
		WriteReal(value, FormatInfoT::DecimalDigits);
	}

	inline void WriteLine()
	{
		Write(TextFormatInfo::NewLine);
	}

	inline void WriteLine(char value)
	{
		Write(value);
		WriteLine();
	}

	inline void WriteLine(unsigned char value)
	{
		Write(value);
		WriteLine();
	}

	inline void WriteLine(const char str[])
	{
		Write(str);
		WriteLine();
	}

	inline void WriteLine(int value)
	{
		Write(value);
		WriteLine();
	}

	inline void WriteLine(unsigned int value)
	{
		Write(value);
		WriteLine();
	}

	inline void WriteLine(long value)
	{
		Write(value);
		WriteLine();
	}

	inline void WriteLine(unsigned long value)
	{
		Write(value);
		WriteLine();
	}

	inline void WriteLine(float value)
	{
		Write(value);
		WriteLine();
	}

private:
	void WriteInt(unsigned int integer, byte base)
	{
		char buffer[11]; // an int is 2^32 and has 10 digits + terminating 0
		char* strPos = &buffer[sizeof(buffer) - 1];

		// we fill the buffer from back to front.
		*strPos = '\0';

		// safety check for base values that crash
		// base == 0 -> devide by zero
		// base == 1 -> endless loop
		if (base < 2) base = 10;

		do
		{
			unsigned int remainder = integer;
			integer /= base;
			
			char c = remainder - base * integer;
			*--strPos = c < 10 ? c + '0' : c + 'A' - 10;
		}
		while (integer != 0);

		Write(strPos);
	}

	void WriteLong(unsigned long integer, byte base)
	{
		char buffer[21]; // a long is 2^64 and has 20 digits + terminating 0
		char* strPos = &buffer[sizeof(buffer) - 1];

		// we fill the buffer from back to front.
		*strPos = '\0';

		// safety check for base values that crash
		// base == 0 -> devide by zero
		// base == 1 -> endless loop
		if (base < 2) base = 10;

		do
		{
			unsigned long remainder = integer;
			integer /= base;
			
			char c = (char)(remainder - base * integer);
			*--strPos = c < 10 ? c + '0' : c + 'A' - 10;
		}
		while (integer != 0);

		Write(strPos);
	}

	void WriteReal(double real, byte digits)
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

#endif // __TEXTWRITER_H__