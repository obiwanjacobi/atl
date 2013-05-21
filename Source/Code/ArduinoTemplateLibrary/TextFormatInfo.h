/*  
	Arduino Template Library http://atl.codeplex.com
	Written by Marc Jacobi
	Copyright 2012-2013 All Rights Reserved

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
	static unsigned char DecimalDigits;
	static char NegativeSign;
	static char DecimalSeparator;
	static unsigned char DefaultBase;
};

char TextFormatInfo::NewLine[] = { '\10', '\13', '\0' };
unsigned char TextFormatInfo::DecimalDigits = (unsigned char)2;
char TextFormatInfo::NegativeSign = { '-' };
char TextFormatInfo::DecimalSeparator = { '.' } ;
unsigned char TextFormatInfo::DefaultBase = (unsigned char)baseDecimal;

}} // ATL.IO

#endif //__TEXTFORMATINFO_H__