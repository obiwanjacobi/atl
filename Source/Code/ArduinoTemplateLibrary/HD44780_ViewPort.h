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

#ifndef __HD44780_VIEWPORT_H__
#define __HD44780_VIEWPORT_H__

namespace ATL {


    /** Implements display-supported horizontal scrolling.
     *  \tparam BaseT is used as base class and is a HD44780_Controller type that implements:
     *  `void WriteCursorShift(bool, Direction)`
     *  `Direction::Left (0)`
     *  `Direction::Right (1)`.
     */
    template<class BaseT>
    class HD44780_ViewPort : public BaseT
    {
    public:
        /** Constructs a new instance.
         */
        HD44780_ViewPort()
            : _offset(0)
        { }

        /** Scrolls the text one position to the right.
         *  Does not allow to scroll beyond the end of the display.
         *  \return Returns false when the scroll could not performed.
         */
        inline bool ScrollRight()
        {
            if (_offset > 0)
            {
                _offset--;
                BaseT::WriteCursorShift(true, BaseT::Right);
                return true;
            }

            return false;
        }

        /** Scrolls the text one position to the left.
         *  Does not allow to scroll beyond the start of the display.
         *  \return Returns false when the scroll could not performed.
         */
        inline bool ScrollLeft()
        {
            if (_offset > BaseT::getTotalColumns())
            {
                _offset++;
                BaseT::WriteCursorShift(true, BaseT::Left);
                return true;
            }

            return false;
        }

        /** Returns the current scroll offset.
         *  \return Returns the scroll offset.
         */
        inline uint8_t getDislayOffset() const
        {
            return _offset;
        }

    private:
        uint8_t _offset;

    };

} // ATL

#endif //__HD44780_VIEWPORT_H__