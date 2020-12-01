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

#ifndef __DISPLAYWRITER_H__
#define __DISPLAYWRITER_H__

#include <stddef.h>
#include <stdint.h>

namespace ATL {


    /** The DisplayWriter is used to 'draw' Control instance onto a display.
     *  It detaches the details of how the display is driven from the Control UI framework.
     *  This class is abstract and cannot be instantiated. See also HD44780_DisplayWriter for a full implementation.
     */
    class DisplayWriter
    {
    public:
        /** This value can be passed to the `GoTo()` and `SetCursor()` methods. */
        static const uint8_t DontCare = 0xFF;

        /** Writes the text to the current (cursor) position on the display.
         *  \param text points to a NULL terminated string.
         */
        virtual void Write(const char* /*text*/)
        { }

        /** Repositions the current cursor position to the specified lineIndex and columnIndex.
         *  \param lineIndex is a zero-based index for the line in the display.
         *  \param columnIndex is a zero-based index for the column in the display.
         */
        virtual void GoTo(uint8_t /*lineIndex*/, uint8_t /*columnIndex*/)
        { }

        /** Displays a cursor at the specified lineIndex and columnIndex.
         *  If edit is true, the edit-cursor is displayed.
         *  \param lineIndex is a zero-based index for the line in the display.
         *  \param columnIndex is a zero-based index for the column in the display.
         *  \param edit is an indication to display a 'edit' cursor
         */
        virtual void SetCursor(uint8_t /*lineIndex*/, uint8_t /*columnIndex*/, bool /*edit*/)
        { }

    protected:
        DisplayWriter()
        { }
    };



} // ATL

#endif //__DISPLAYWRITER_H__