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

#ifndef __HD44780_DISPLAYWRITER_H__
#define __HD44780_DISPLAYWRITER_H__

#include "DisplayWriter.h"

namespace ATL {

    /** An implementation for the DisplayWriter used in the UI framework for the HD44780 LCD display.
     *  The class derives from DisplayWriter and BaseT.
     *  \tparam BaseT is a TextWriter => HD44780_View => HD44780_Controller type that implements:
     *  `void Write(const char*)` (TextWriter)
     *  `uint8_t getCursorRow()` (HD44780_View)
     *  `uint8_t getCursorCol()` (HD44780_View)
     *  `void SetCursor(uint8_t, uint8_t)` (HD44780_View)
     *  `void setEnableCursor(bool)` (HD44780_Controller)
     *  `bool getEnableCursor()` (HD44780_Controller)
     *  `void setEnableBlink(bool)` (HD44780_Controller)
     *  `bool getEnableBlink()` (HD44780_Controller).
     */
    template<class BaseT>
    class HD44780_DisplayWriter : public DisplayWriter, public BaseT
    {
    public:
        /** Calls the `TextWriter::Write` method.
         *  \param text points to a zer-terminated string.
         */
        virtual void Write(const char* text)
        {
            BaseT::Write(text);
        }

        /** Calls the `HD44780_View::SetCursor` method.
         *  Will also call `HD44780_View::getCursorRow` and `HD44780_View::getCursorCol` 
         *  when `DisplayWriter::DontCare` values are specified.
         *  \param lineIndex indicates the display line.
         *  \param columnIndex indicates the display column (char position).
         */
        virtual void GoTo(uint8_t lineIndex, uint8_t columnIndex)
        {
            if (lineIndex == DontCare)
                lineIndex = BaseT::getCursorRow();
            if (columnIndex == DontCare)
                columnIndex = BaseT::getCursorCol();

            BaseT::SetCursor(lineIndex, columnIndex);
        }

        /** Calls the `HD44780_View::SetCursor` and `HD44780_Controller::setEnableCursor` methods.
         *  May also call the `HD44780_Controller::setEnableBlink` method for edit mode.
         *  \param lineIndex indicates the display line.
         *  \param columnIndex indicates the display column (char position).
         *  \param edit indicates if a blinking cursor is displayed.
         */
        virtual void SetCursor(uint8_t lineIndex, uint8_t columnIndex, bool edit)
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

            if (BaseT::getEnableBlink() != edit)
            {
                BaseT::setEnableBlink(edit);
            }

            BaseT::SetCursor(lineIndex, columnIndex);
        }
    };


} // ATL

#endif //__HD44780_DISPLAYWRITER_H__