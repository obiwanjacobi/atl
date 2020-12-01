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

#ifndef __UPDOWNCONTROL_H__
#define __UPDOWNCONTROL_H__

#include "InputControl.h"

namespace ATL {


    /** The UpDownControl edits a value with the `Up` and `Down` commands.
     *  Management of the value itself is outside this class.
     *  \tparam ValueT represents the type that controls the value and implements:
     *  `const char* ToString()`
     *  `void IncrmentValue()`
     *  `void DecrmentValue()`.
     */
    template<class ValueT>
    class UpDownControl : public InputControl
    {
    public:
        /** Constructs an initialized instance.
         *  \param value points to the value instance. Must not be NULL.
         *  \pos is the optional position relative to its siblings.
         */
        UpDownControl(ValueT* value, uint8_t pos = 0)
            : InputControl(pos), _value(value)
        { }

        /** Writes the value as text to the DisplayWriter.
         *  Calls ValueT::ToString() to retrieve that text.
         *  \param output is used to output text and position the cursor.
         *  \mode indicates what to display.
         */
        virtual void Display(DisplayWriter* output, ControlDisplayMode mode = ControlDisplayMode::Normal)
        {
            if (mode == ControlDisplayMode::Normal)
            {
                output->Write(_value->ToString());
            }
        }

        /** Overridden to increment and decrement the value on the `Up` and `Down` commands.
         *  \param navCmd is the navigation command.
         *  \return Returns true if the command was handled.
         */
        virtual bool OnNavigationCommand(NavigationCommands navCmd)
        {
            bool handled = false;

            switch (navCmd)
            {
            case NavigationCommands::Up:
                handled = TryValueUp();
                break;
            case NavigationCommands::Down:
                handled = TryValueDown();
                break;
            default:
                break;
            }

            if (handled) return true;

            return InputControl::OnNavigationCommand(navCmd);
        }

        /** Attempts to increment the value.
         *  \return Returns true if successful.
         */
        bool TryValueUp()
        {
            if (getIsSelected())
            {
                _value->IncrementValue();
                return true;
            }

            return false;
        }

        /** Attempts to decrement the value.
         *  \return Returns true if successful.
         */
        bool TryValueDown()
        {
            if (getIsSelected())
            {
                _value->DecrementValue();
                return true;
            }

            return false;
        }

        /** Retrieve the reference to the value object this instance was constructed with.
         *  \return Returns the ValueT pointer.
         */
        inline ValueT* getValueObject() const
        {
            return _value;
        }

    private:
        ValueT* _value;
    };


} // ATL

#endif //__UPDOWNCONTROL_H__