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

#ifndef __LABELCONTROL_H__
#define __LABELCONTROL_H__

#include <stddef.h>
#include <stdint.h>
#include "Control.h"

namespace ATL {

    /** The LabelControl displays a static text and does not accept any input.
     *  The LabelControl is not an InputControl so it does not accept navigation commands.
     */
    class LabelControl : public Control
    {
    public:
        /** Constructs the instance with an optional position.
         *  Call `setText()` to assign text to the control.
         *  \param pos is the position relative to its siblings.
         */
        LabelControl(uint8_t pos = 0)
            : Control(pos), _text(NULL)
        { }

        /** Constructs an initialized instance with an optional position.
         *  \param text points to a zero-terminated string. The string is NOT copied.
         *  \param pos is the position relative to its siblings.
         */
        LabelControl(const char* text, uint8_t pos = 0)
            : Control(pos), _text(text)
        { }

        /** Outputs the text to the display (if available).
         *  Does nothing in modeCursor.
         *  \param output is a pointer to the display writer that is used to output and position text.
         *  \param mode is the display mode and results in different behavior.
         */
        virtual void Display(DisplayWriter* output, Control::ControlDisplayMode mode = Control::modeNormal)
        {
            if (mode == Control::modeCursor) return;

            if (_text != NULL)
            {
                output->Write(_text);
            }
        }

        /** Retrieves the text the LabelControl displays.
         *  \return Returns the pointer to the text.
         */
        inline const char* getText() const
        {
            return _text;
        }

        /** Assigns the text the LabelControl displays.
         *  \param text points to a zero-terminated string. The string is NOT copied.
         */
        inline void setText(const char* text)
        {
            _text = text;
        }

    protected:
        /** Overridden to disallow `stateFocused` and `stateSelected` states.
         *  \param newState is the proposed state.
         */
        virtual bool BeforeChangeState(Control::ControlState newState)
        {
            return newState != ControlState::Focused && 
                   newState != ControlState::Selected && 
                   Control::BeforeChangeState(newState);
        }

    private:
        const char* _text;
    };

} // ATL

#endif //__LABELCONTROL_H__