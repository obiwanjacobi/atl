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

#ifndef __HD44780_DISPLAYWRITER_H__
#define __HD44780_DISPLAYWRITER_H__

#include "DisplayWriter.h"

namespace ATL {

/*
BaseT is used as a base class and implements:
	uint8_t [HD44780_View]getCursorRow();
	uint8_t [HD44780_View]getCursorCol();
	void [HD44780_View]SetCursor(uint8_t row, uint8_t col);
	void [HD44780_Controller]setEnableCursor(bool);
	bool [HD44780_Controller]getEnableCursor();
	void [HD44780_Controller]setEnableBlink(bool);
	bool [HD44780_Controller]getEnableBlink();
*/
template<class BaseT>
class HD44780_DisplayWriter : public DisplayWriter, public BaseT
{
public:
	// writes text to the lcd.
	virtual void Write(const char* text)
	{
		BaseT::Write(text);
	}

	// sets the starting position for the following Write call.
	virtual void GoTo(uint8_t lineIndex, uint8_t columnIndex)
	{
		if (lineIndex == DontCare)
			lineIndex = BaseT::getCursorRow();
		if (columnIndex == DontCare)
			columnIndex = BaseT::getCursorCol();

		BaseT::SetCursor(lineIndex, columnIndex);
	}

	// sets the (blinking) cursor position to indicate a selected state of the control.
	virtual void SetCursor(uint8_t lineIndex, uint8_t columnIndex, bool blink)
	{
		if (lineIndex == DontCare && columnIndex == DontCare)
		{
			BaseT::setEnableCursor(false);
			return;
		}

		if (!BaseT::getEnableCursor())
		{
			BaseT::setEnableCursor(true);
		}

		if (BaseT::getEnableBlink() != blink)
		{
			BaseT::setEnableBlink(blink);
		}

		BaseT::SetCursor(lineIndex, columnIndex);
	}
};


} // ATL

#endif //__HD44780_DISPLAYWRITER_H__