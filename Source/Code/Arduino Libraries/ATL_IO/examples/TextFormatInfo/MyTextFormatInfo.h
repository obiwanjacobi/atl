#ifndef __MYTEXTFORMATINFO_H__
#define __MYTEXTFORMATINFO_H__

#include <stdint.h>

/*
  This class defines custom regional number-settings.
*/
class MyTextFormatInfo
{
public:
  static char NewLine[];
  static uint8_t DecimalDigits;
  static char NegativeSign;
  static char DecimalSeparator;
  static uint8_t DefaultBase;
};


char MyTextFormatInfo::NewLine[] = { '\n', '\0' };
uint8_t MyTextFormatInfo::DecimalDigits = (uint8_t)4;
char MyTextFormatInfo::NegativeSign = { '-' };
char MyTextFormatInfo::DecimalSeparator = { ',' } ;
uint8_t MyTextFormatInfo::DefaultBase = (uint8_t)ATL::TextFormatInfo::baseHexadecimal;


#endif //__MYTEXTFORMATINFO_H__
