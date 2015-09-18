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

#ifndef __INPUTCONTROL_H__
#define __INPUTCONTROL_H__

#include "NavigationController.h"
#include "Control.h"

namespace ATL {


// abstract
class InputControl : public Control,
					 public NavigationController
{
public:
	virtual bool OnNavigationCommand(NavigationCommands keyCmd)
	{
		switch (keyCmd)
		{
		case Enter:
			return TrySelect();
		case Exit:
			return TryDeselect();
		default:
			break;
		}

		return NavigationController::OnNavigationCommand(keyCmd);
	}

	bool TrySelect()
	{
		if (getIsFocussed())
		{
			setState(Control::stateSelected);
			return true;
		}
		return false;
	}

	bool TryDeselect()
	{
		if (getIsSelected())
		{
			setState(Control::stateFocused);
			return true;
		}
		return false;
	}

	virtual bool IsOfType(ControlTypes type) const
	{
		return ((typeInputControl & type) == typeInputControl) ||
			Control::IsOfType(type);
	}

protected:
	InputControl(uint8_t pos = 0)
		: Control(pos)
	{ }

    virtual bool BeforeChangeState(ControlState newState)
    {
        if (!Control::BeforeChangeState(newState)) return false;

        // don't allow focus when disabled (or hidden).
        if (newState == Control::stateFocused &&
            !getIsEnabled())
        {
            return false;
        }

        return true;
    }
};


} // ATL

#endif //__INPUTCONTROL_H__