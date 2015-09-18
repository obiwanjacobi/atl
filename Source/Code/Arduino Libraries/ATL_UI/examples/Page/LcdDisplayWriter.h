#ifndef __LCDDISPLAYWRITER_H__
#define __LCDDISPLAYWRITER_H__

#include <ATL_UI.h>

/*
 * The LcdDisplayWriter class implements the DisplayWriter 'interface' (abstract class).
 * Each method uses ATL TextWriter and/or HD44780 functionality to implement it.
 * This way the ATL-UI is not hard linked to the ATL LCD implementation.
 * You can easily use a different display (library).
 * The DisplayWriter, however, is defined by the ATL UI framework and cannot be changed.
 */

/*
 * We use the same BaseT trick that ATL uses.
 * This allows us to stack this class on top an LCD stack and thanks to C++ multiple inheritence
 * we also implement the DisplayWriter methods.
 *
 * NOTE: This class is provided as a sample. ATL has a HD44780_DisplayWriter class that has a full implementation.
 */
template<class BaseT>
class LcdDisplayWriter : public ATL::DisplayWriter,
                         public BaseT
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
	virtual void SetCursor(uint8_t /*lineIndex*/, uint8_t /*columnIndex*/, bool /*blink*/)
	{
		// not used in this example
	}
};




#endif // __LCDDISPLAYWRITER_H__
