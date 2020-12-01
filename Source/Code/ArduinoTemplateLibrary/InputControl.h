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

#ifndef __INPUTCONTROL_H__
#define __INPUTCONTROL_H__

#include "NavigationController.h"
#include "Control.h"

namespace ATL {


    /** The InputControl is the abstract base class for all Controls that accept input stimuli.
     *  This class derives from Control and from NavigationController (the input).
     *  It can be 'detected' by the Control::DynamicCast using the typeInputControl enum value.
     */
    class InputControl : public Control,
                         public NavigationController
    {
    public:
        /** Implements selection behavior on the `Enter` and `Exit` navigation commands.
         *  If the Control is in `stateFocused` and the `Enter` commands is provided, it will
         *  try to transition to the `stateSelected` state (`TrySelect()`). If the Control is
         *  `stateSelected` and the `Exit` command is provided, it will try to transition the
         *  `stateFocused` state (`TryDeselect()`).
         *  \param navCmd the navigation command.
         *  \return Returns true when the command was handled.
         */
        virtual bool OnNavigationCommand(NavigationCommands navCmd)
        {
            switch (navCmd)
            {
            case NavigationCommands::Enter:
                return TrySelect();
            case NavigationCommands::Exit:
                return TryDeselect();
            default:
                break;
            }

            return NavigationController::OnNavigationCommand(navCmd);
        }

        /** Attempts to get the Control from the `stateFocused` to the `stateSelected` state.
         *  \return Returns true if successful.
         */
        bool TrySelect()
        {
            if (getIsFocussed())
            {
                setState(ControlState::Selected);
                return true;
            }
            return false;
        }

        /** Attempts to get the Control from the `stateSelected` to the `stateFocused` state.
         *  \return Returns true if successful.
         */
        bool TryDeselect()
        {
            if (getIsSelected())
            {
                setState(ControlState::Focused);
                return true;
            }
            return false;
        }

        /** Overridden to implement the typeInputControl type flag.
         *  \param type indicates the requested type.
         *  \return Returns true if the type flag matches the class hierarchy.
         */
        virtual bool IsOfType(ControlTypes type) const
        {
            return ((ControlTypes::InputControl & type.value) == ControlTypes::InputControl) ||
                Control::IsOfType(type);
        }

    protected:
        /** For derived classes.
         *  \param pos is the position relative to its siblings.
         */
        InputControl(uint8_t pos = 0)
            : Control(pos)
        { }

        /** Overridden to disallow going to the `stateFocused` when not enabled.
         *  \param newState is the proposed state.
         */
        virtual bool BeforeChangeState(ControlState newState)
        {
            if (!Control::BeforeChangeState(newState)) return false;

            // don't allow focus when disabled (or hidden).
            if (newState == ControlState::Focused &&
                !getIsEnabled())
            {
                return false;
            }

            return true;
        }
    };


} // ATL

#endif //__INPUTCONTROL_H__