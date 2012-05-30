#ifndef __TEXTFORMATINFO_H__
#define __TEXTFORMATINFO_H__

#include <Arduino.h>

namespace ATL {
namespace IO {

class TextFormatInfo
{
public:
	enum BaseTypes
	{
		baseNone = 0,
		baseBinary = 2,
		baseOctal = 8,
		baseDecimal = 10,
		baseHexadecimal = 16,
	};

	static char NewLine[];
	static byte DecimalDigits;
	static char NegativeSign;
	static char DecimalSeparator;
	static byte DefaultBase;
};

char TextFormatInfo::NewLine[] = { '\10', '\13', '\0' };
byte TextFormatInfo::DecimalDigits = (byte)2;
char TextFormatInfo::NegativeSign = { '-' };
char TextFormatInfo::DecimalSeparator = { '.' } ;
byte TextFormatInfo::DefaultBase = (byte)baseDecimal;

}} // ATL.IO

#endif //__TEXTFORMATINFO_H__