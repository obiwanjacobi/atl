#ifndef __MYTEXTFORMATINFO_H__
#define __MYTEXTFORMATINFO_H__


/*
  This class defines custom regional number-settings.
*/
class MyTextFormatInfo
{
public:
  static char NewLine[];
  static unsigned char DecimalDigits;
  static char NegativeSign;
  static char DecimalSeparator;
  static unsigned char DefaultBase;
};


char MyTextFormatInfo::NewLine[] = { '\n', '\0' };
unsigned char MyTextFormatInfo::DecimalDigits = (unsigned char)4;
char MyTextFormatInfo::NegativeSign = { '-' };
char MyTextFormatInfo::DecimalSeparator = { ',' } ;
unsigned char MyTextFormatInfo::DefaultBase = (unsigned char)ATL::IO::TextFormatInfo::baseHexadecimal;


#endif //__MYTEXTFORMATINFO_H__
