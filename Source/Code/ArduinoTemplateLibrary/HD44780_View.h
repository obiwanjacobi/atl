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
namespace Hardware {
namespace Display {

/*
	BaseT is used as a base class and implements:

*/
template<class BaseT, const byte Rows, const byte Cols>
class HD44780_View : public BaseT
{
public:

	inline void Initialize(bool full)
	{
		BaseT::Initialize(full);

		if (full)
		{
			BaseT::SetEntryMode(BaseT::Left, false);
		}
	}

	// OutputStream interface
	inline bool Write(byte character)
	{
		// check for new-line and carriage return
		if (character == '\10')
		{
			IncrementCurrentRow();
			WriteDisplayAddress();
			return true;
		}
		if (character == '\13')
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

	inline static byte getTotalRows()
	{
		return Rows;
	}

	inline static byte getTotalColumns()
	{
		return 80 / Rows;
	}

	inline static byte getVisibleRows()
	{
		return Rows;
	}

	inline static byte getVisibleColumns()
	{
		return Cols;
	}

	// zero-based index
	inline void SetCursor(byte rowIndex, byte colIndex)
	{
		_cursorRow = rowIndex;
		_cursorCol = colIndex;
		WriteDisplayAddress();
	}

	inline byte getCursorRow() const
	{
		return _cursorRow;
	}

	inline byte getCursorCol() const
	{
		return _cursorCol;
	}

	// override controller
	inline void ReturnHome()
	{
		_cursorCol = 0;
		_cursorRow = 0;
		BaseT::ReturnHome();
	}

private:
	byte _cursorRow;
	byte _cursorCol;

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

	inline byte CalcAddress(byte rowIndex, byte colIndex)
	{
		byte rowOffsets[] = { 0x00, 0x40, 0x14, 0x54 };

		if (rowIndex >= getTotalRows())
		{
			rowIndex = 0;  // wrap rows on overflow
		}

		return (rowOffsets[rowIndex] + colIndex);
	}

	inline void WriteDisplayAddress()
	{
		BaseT::WriteDisplayAddress(CalcAddress(_cursorRow, _cursorCol));
	}
};

}}} // ATL::Hardware::Display

#endif //__HD44780_VIEW_H__