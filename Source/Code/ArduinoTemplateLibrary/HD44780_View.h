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

#ifndef __HD44780_VIEW_H__
#define __HD44780_VIEW_H__

namespace ATL {

/*
	BaseT is used as a base class and implements [HD44780_Controller]:
		void [HD44780_Controller]Initialize(bool);
		void [HD44780_Controller]ReturnHome();
		void [HD44780_Controller]WriteData(unsigend char);
		void [HD44780_Controller]WriteDisplayAddress(uint8_t );
		void [HD44780_Controller]SetEntryMode(Direction, bool);
		[HD44780_Controller]Direction::Left (0);
		[HD44780_Controller]Direction::Right (1);
	Rows: the number of rows the display has
	Cols: the number of (visible) columns the display has.

	Typically the BaseT is the HD44780_Controller template class or derivative.
*/
template<class BaseT, const uint8_t Rows, const uint8_t Cols>
class HD44780_View : public BaseT
{
public:

	/*
		Initializes the BaseT and the display entry mode.
	 */
	inline void Initialize(bool full)
	{
		BaseT::Initialize(full);

		if (full)
		{
			BaseT::SetEntryMode(BaseT::Left, false);
		}
	}

	/*
		Implements the OutputStream write method to output characters.
		Will keep track of the cursor position and handles carriage (13) return and new line (10).

		This allows a TextWriter template class to be wrapped around the display.
	 */
	inline bool Write(uint8_t character)
	{
		// check for new-line and carriage return
		if (character == '\n')
		{
			IncrementCurrentRow();
			WriteDisplayAddress();
			return true;
		}
		if (character == '\r')
		{
			_cursorCol = 0;
			WriteDisplayAddress();
			return true;
		}

		IncrementCurrentCol();
		BaseT::WriteData(character);
		return true;
	}

	/*inline void Flush()
	{}*/

	inline static uint8_t getTotalRows()
	{
		return Rows;
	}

	inline static uint8_t getTotalColumns()
	{
		return 80 / Rows;
	}

	inline static uint8_t getVisibleRows()
	{
		return Rows;
	}

	inline static uint8_t getVisibleColumns()
	{
		return Cols;
	}

	/*
		Sets the current cursor position.
		The indexes as zero-based.
	 */
	inline void SetCursor(uint8_t rowIndex, uint8_t colIndex)
	{
		_cursorRow = rowIndex;
		_cursorCol = colIndex;
		WriteDisplayAddress();
	}

	/*
		Returns the current Cursor row position index.
	 */
	inline uint8_t getCursorRow() const
	{
		return _cursorRow;
	}

	/*
		Returns the current Cursor column position index.
	 */
	inline uint8_t getCursorCol() const
	{
		return _cursorCol;
	}

	/*
		Overrides the Controller method to adjust current cursor position.
	*/
	inline void ReturnHome()
	{
		_cursorCol = 0;
		_cursorRow = 0;
		BaseT::ReturnHome();
	}

private:
	uint8_t _cursorRow;
	uint8_t _cursorCol;

	void IncrementCurrentRow()
	{
		if (_cursorRow + 1 > getTotalRows())
		{
			_cursorRow = 0;
		}
		else
		{
			_cursorRow++;
		}
	}

	void IncrementCurrentCol()
	{
		if (_cursorCol + 1 > getTotalColumns())
		{
			_cursorCol = 0;
			IncrementCurrentRow();
		}
		else
		{
			_cursorCol++;
		}
	}

	inline uint8_t CalcAddress(uint8_t rowIndex, uint8_t colIndex)
	{
		static uint8_t rowOffsets[] = { 0x00, 0x40, 0x14, 0x54 };

		if (rowIndex >= getTotalRows())
		{
			rowIndex = 0;  // wrap rows on overflow
		}

		return (rowOffsets[rowIndex] + colIndex);
	}

	// writes the data address to match the current cursor position.
	inline void WriteDisplayAddress()
	{
		BaseT::WriteDisplayAddress(CalcAddress(_cursorRow, _cursorCol));
	}
};

} // ATL

#endif //__HD44780_VIEW_H__