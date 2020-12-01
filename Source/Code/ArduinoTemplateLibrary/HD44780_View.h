/*
Arduino Template Library https://github.com/obiwanjacobi/atl
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

    /** The HD44780_View class implements an ATL output-stream and cursor manipulation.
     *  \tparam BaseT is a HD44780_Controller type that implements:
     *  `void Initialize(bool)` (HD44780_Controller)
     *  `void ReturnHome()` (HD44780_Controller)
     *  `void WriteData(unsigend char)` (HD44780_Controller)
     *  `void WriteDisplayAddress(uint8_t )` (HD44780_Controller)
     *  `void SetEntryMode(Direction, bool)` (HD44780_Controller)
     *  `Direction::Left` (0)(HD44780_Controller)
     *  `Direction::Right` (1)(HD44780_Controller).
     *  \tparam Rows is the number if text rows on the display. Typical values are 1, 2 and 4.
     *  \tparam Cols is the number of (visible) characters on one line. Typical values are 8, 16, 20 and 40.
     */
    template<class BaseT, const uint8_t Rows, const uint8_t Cols>
    class HD44780_View : public BaseT
    {
    public:

        /** Initializes the BaseT and sets the display entry mode.
         *  \param full indicates a full initialization. See also HD44780_Controller.
         */
        inline void Initialize(bool full = true)
        {
            BaseT::Initialize(full);

            if (full)
            {
                BaseT::SetEntryMode(BaseT::Left, false);
            }
        }

        /** Implements the OutputStream write method to output characters.
         *  This allows a TextWriter template class to be wrapped around the display.
         *  Will keep track of the cursor position and handles carriage (\\r) return and new line (\\n).
         *  \param character is the single character to write to the display (ASCII).
         */
        inline bool Write(char character)
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

        /** Retrieves the Rows template parameter.
         *  \return Returns the Rows value.
         */
        inline uint8_t getTotalRows()
        {
            return Rows;
        }

        /** Retrieves the total number f characters per line.
         *  This value is calculated by 80/Rows - due to the internal memory layout of the LCD display.
         *  \return Returns the 80/Rows value.
         */
        inline uint8_t getTotalColumns()
        {
            return 80 / Rows;
        }

        /** Retrieves the Rows template parameter.
         *  \return Returns the Rows value.
         */
        inline uint8_t getVisibleRows()
        {
            return Rows;
        }

        /** Retrieves the Cols template parameter.
         *  \return Returns the Cols value.
         */
        inline uint8_t getVisibleColumns()
        {
            return Cols;
        }

        /** Sets the current cursor position.
         *  The cursor position (display address) is where the next character written will appear.
         *  \param rowIndex is a zero-based index indicating the line (row).
         *  \param colIndex is a zero-based index indicating the character position.
         */
        inline void SetCursor(uint8_t rowIndex, uint8_t colIndex)
        {
            _cursorRow = rowIndex;
            _cursorCol = colIndex;
            WriteDisplayAddress();
        }

        /** Returns the current Cursor row position index.
         *  \return Returns the current row index.
         */
        inline uint8_t getCursorRow() const
        {
            return _cursorRow;
        }

        /** Returns the current Cursor column position index.
         *  \return Returns the current column index.
         */
        inline uint8_t getCursorCol() const
        {
            return _cursorCol;
        }

        /** Overrides the Controller method to adjust current cursor position.
         *  Send the return-home command to the display.
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