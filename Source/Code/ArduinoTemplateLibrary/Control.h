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

#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <stddef.h>
#include <stdint.h>

#include "DisplayWriter.h"

namespace ATL {


enum ControlTypes
{
    typeUnknown = 0,
    typeControl = 0x01,
    typeInputControl = 0x02,
    typePanel = 0x03,
};


enum ControlState
{
    Normal,     // no other states active
    Hidden,     // control is not displayed
    Disabled,   // control is displayed as read-only
    Focused,    // control is high-lighted
    Selected,   // control is active/selected (entered)
};



// abstract
class Control
{
protected:
    Control(uint8_t position = 0)
		: _pos(position)
    { }

public:
    inline uint8_t getPosition() const
    {
        return _pos;
    }

	inline void setPosition(uint8_t newPos)
	{
		_pos = newPos;
	}

    inline bool isHidden() const
    {
        return _state == Hidden;
    }

    inline bool isVisible() const
    {
        return !isHidden();
    }

    inline bool isDisabled() const
    {
        return _state == Disabled;
    }

    inline bool isEnabled() const
    {
        return !isDisabled() && !isHidden();
    }

    inline bool isFocussed() const
    {
        return _state == Focused;
    }

    inline bool isSelected() const
    {
        return _state == Selected;
    }

    inline bool isActive() const
    {
        return isFocussed() || isSelected();
    }

    inline ControlState getState() const
    {
        return _state;
    }

    inline bool setState(ControlState newState)
    {
        if (BeforeChangeState(newState))
        {
            _state = newState;
            return true;
        }
        return false;
    }

    virtual void Display(DisplayWriter* /*output*/) {}

    virtual bool IsOfType(ControlTypes type) const
    {
        return (type & typeControl) == typeControl;
    }

    static Control* DynamicCast(Control* ctrl, ControlTypes type)
    {
        if (ctrl == NULL) return NULL;
        if (ctrl->IsOfType(type)) return ctrl;
        return NULL;
    }

protected:
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