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

#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <stddef.h>
#include <stdint.h>
#include "DisplayWriter.h"
#include "EnumScope.h"


namespace ATL {

    /** Enumerates the base types of controls.
     *  Used to implement a DynamicCast.
     */
    BeginEnum(ControlTypes)
    {
        /** Control type is not set or unknown. */
        Unknown = 0,
        /** Control type is the root class for controls. */
        Control = 0x01,
        /** Control type is an input control (navigation). */
        InputControl = 0x02,
        /** Control type is a control panel (collection). */
        Panel = 0x03,
        /** Control type is page (lines with controls). */
        Page = 0x04,
    }
    EndEnum(ControlTypes)

    /** Enumerates the state a Control can be in.
     *  Only one state is active at a time.
     */
    BeginEnum(ControlState)
    {
        /** Control state is normal - no special considerations. */
        Normal,     // no other states active
        /** Control state is hidden, it will not be displayed and cannot receive input. */
        Hidden,     // control is not displayed
        /** Control state is disabled, it cannot receive input but it is still displayed. */
        Disabled,   // control is displayed as read-only
        /** Control state is focused, the cursor is displayed at its start.
        *  Only one Control can have the focus at one time. */
        Focused,    // control is high-lighted
        /** Control state is selected, the edit-cursor is displayed at its start.
        *  Only one Control can have be selected at one time. */
        Selected,   // control is active/selected (entered)
    }
    EndEnum(ControlState)

    /** Enumerates the mode in which the Display method can be called.
     */
    BeginEnum(ControlDisplayMode)
    {
        /** Display normal content based on the control state. */
        Normal,
        /** Display is called to position the cursor for selected/edit mode */
        Cursor,
    }
    EndEnum(ControlDisplayMode)


    // abstract
    /** The Control class is the root base class for all controls in the UI framework.
     *  It implements that basic interface (virtual methods) for interacting with all controls.
     *  The Control class is abstract - it cannot be instantiated.
     */
    class Control
    {
    public:
        /** Retrieves the position for the control.
         *  \return the position value.
         */
        inline uint8_t getPosition() const
        {
            return _pos;
        }

        /** Assigns a new position value to the control.
         *  \param newPos is the new position value.
         */
        inline void setPosition(uint8_t newPos)
        {
            _pos = newPos;
        }

        /** Indicates if the control is hidden (not visible).
         *  \returns Returns true if hidden.
         */
        inline bool getIsHidden() const
        {
            return _state == ControlState::Hidden;
        }

        /** Indicates if the control is visible (not hidden).
         *  \returns Returns true if visible.
         */
        inline bool getIsVisible() const
        {
            return !getIsHidden();
        }

        /** Indicates if the control is disabled.
         *  \returns Returns true if disabled.
         */
        inline bool getIsDisabled() const
        {
            return _state == ControlState::Disabled;
        }

        /** Indicates if the control is not disabled and not hidden.
         *  \returns Returns true if enabled.
         */
        inline bool getIsEnabled() const
        {
            return !getIsDisabled() && !getIsHidden();
        }

        /** Indicates if the control has the focus.
         *  \returns Returns true if focused.
         */
        inline bool getIsFocussed() const
        {
            return _state == ControlState::Focused;
        }

        /** Indicates if the control has the selection.
         *  \returns Returns true if selected.
         */
        inline bool getIsSelected() const
        {
            return _state == ControlState::Selected;
        }

        /** Indicates if the control is focused or selected.
         *  \returns Returns true if active.
         */
        inline bool getIsActive() const
        {
            return getIsFocussed() || getIsSelected();
        }

        /** Retrieves the state of the Control.
         *  \returns Returns the control state.
         */
        inline ControlState getState() const
        {
            return _state;
        }

        /** Assigns a new state to the Control.
         *  Calls the `BeforeChangeState` method to allow sub-classes to prevent state change.
         *  \param newState is the new state value to set.
         *  \return Returns true if successful.
         */
        inline bool setState(ControlState newState)
        {
            if (BeforeChangeState(newState))
            {
                _state = newState;
                return true;
            }
            return false;
        }

        /** Called to let the Control draw itself using the DisplayWriter.
         *  At Control level this method does nothing.
         *  \param output is a pointer to the DisplayWriter object.
         *  \param mode is the enum that indicates in what mode Display is called.
         */
        virtual void Display(DisplayWriter* /*output*/, ControlDisplayMode /*mode*/)
        { }

        /** Indicates if this object is of the specified type.
         *  \param type indicates the requested type.
         *  \return Returns true when the object is of the same type.
         */
        virtual bool IsOfType(ControlTypes type) const
        {
            return (type.value & ControlTypes::Control) == ControlTypes::Control;
        }

        /** Dynamically casts a Control pointer to the specified type.
         *  \param ctrl is the pointer to the Control. Can be NULL.
         *  \param type is the Control type to cast ctrl to.
         *  \return Returns NULL if ctrl is NULL or ctrl is not of the same type. Otherwise the ctrl pointer is returned.
         */
        static Control* DynamicCast(Control* ctrl, ControlTypes type)
        {
            if (ctrl == NULL) return NULL;
            if (ctrl->IsOfType(type)) return ctrl;
            return NULL;
        }

    protected:
        /** Constructor for derived classes.
        *  \param position indicates the position of this control relative to others.
        */
        Control(uint8_t position = 0)
            : _state(ControlState::Normal), _pos(position)
        { }

        /** Called by `setState()` to allow derived classes to prevent state changes.
         *  This method will not allow setting the same state multiple times.
         *  \param newState is the proposed state to set. The current state can be retrieved with `getState()`.
         *  \return Returns true if the state change is allowed.
         */
        virtual bool BeforeChangeState(ControlState newState)
        {
            return _state != newState;
        }

    private:
        ControlState _state;
        uint8_t _pos;
    };


} // ATL

#endif //__CONTROL_H__