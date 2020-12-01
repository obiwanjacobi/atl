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

#ifndef __PANEL_H__
#define __PANEL_H__

#include <stddef.h>
#include <stdint.h>
#include "ControlContainer.h"
#include "Control.h"
#include "InputControl.h"

namespace ATL {

    /** The Panel abstract class maintains a reference to the current control.
     */
    class Panel : public InputControl
    {
    public:
        /** Retrieves the current control.
         *  \return Returns NULL if no current control is set.
         */
        inline InputControl* getCurrentControl() const
        {
            return _currentControl;
        }

        /** Assigns the current control to ctrl.
         *  The old current control (if any) will be set to `stateNormal`.
         *  The new current control (ctrl - if not NULL) will be set to `stateFocused`.
         *  \param ctrl is the control make current. Can be NULL.
         */
        void setCurrentControl(InputControl* ctrl)
        {
            if (_currentControl != NULL)
            {
                _currentControl->setState(ControlState::Normal);
                setState(ControlState::Normal);
            }

            _currentControl = ctrl;

            if (_currentControl != NULL)
            {
                _currentControl->setState(ControlState::Focused);
                setState(ControlState::Focused);
            }
        }

        /** Forwards the call unchanged to the current control (if any).
         *  \param output is used to output text and set the cursor position.
         *  \param mode indicates what is to be displayed.
         */
        virtual void Display(DisplayWriter* output, ControlDisplayMode mode = ControlDisplayMode::Normal)
        {
            if (_currentControl != NULL)
            {
                _currentControl->Display(output, mode);
            }
        }

        /** Forwards the call unchanged to the current control (if any).
         *  \param navCmd is the navigation command.
         */
        virtual bool OnNavigationCommand(NavigationCommands navCmd)
        {
            if (_currentControl != NULL)
            {
                return _currentControl->OnNavigationCommand(navCmd);
            }

            return false;
        }

        /** Overridden to respond to the `typePanel` type.
         *  \param type the requested type.
         *  \return Returns true if the type is part of the class hierarchy.
         */
        virtual bool IsOfType(ControlTypes type) const
        {
            return ((ControlTypes::Panel & type.value) == ControlTypes::Panel) || InputControl::IsOfType(type);
        }

    protected:
        /** For derived classes.
         *  \param pos is the optional control position.
         */
        Panel(uint8_t pos = 0)
            : InputControl(pos), _currentControl(NULL)
        { }

        /** Overridden to disallow `stateSelected`
         *  \param newState is the proposed state.
         *  \return Returns true if the state change may occur.
         */
        virtual bool BeforeChangeState(ControlState newState)
        {
            return newState != ControlState::Selected && 
                   InputControl::BeforeChangeState(newState);
        }

    private:
        InputControl* _currentControl;
    };


} // ATL

#endif //__PANEL_H__