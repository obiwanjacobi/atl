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

#ifndef __PANEL_H__
#define __PANEL_H__

#include <stddef.h>
#include <stdint.h>
#include "ControlContainer.h"
#include "Control.h"
#include "InputControl.h"

namespace ATL {


class Panel : public InputControl
{
public:
	inline InputControl* getCurrentControl() const
	{
		return _currentControl;
	}

	void setCurrentControl(InputControl* ctrl)
	{
		if (_currentControl != NULL)
		{
			_currentControl->setState(Control::stateNormal);
			setState(Control::stateNormal);
		}

		_currentControl = ctrl;

		if (_currentControl != NULL)
		{
			_currentControl->setState(Control::stateFocused);
			setState(Control::stateFocused);
		}
	}

	virtual void Display(DisplayWriter* output, Control::ControlDisplayMode mode = Control::modeNormal)
	{
		if (_currentControl != NULL)
		{
			_currentControl->Display(output, mode);
		}
	}

	virtual bool OnNavigationCommand(NavigationCommands navCmd)
	{
		if (_currentControl != NULL)
		{
			return _currentControl->OnNavigationCommand(navCmd);
		}

		return false;
	}

	virtual bool IsOfType(ControlTypes type) const
	{
		return ((typePanel & type) == typePanel) || InputControl::IsOfType(type);
	}

protected:
	Panel(uint8_t pos = 0)
		: InputControl(pos), _currentControl(NULL)
	{ }

	virtual bool BeforeChangeState(Control::ControlState newState)
	{
		return newState != Control::stateSelected;
	}

private:
	InputControl* _currentControl;
};


} // ATL

#endif //__PANEL_H__