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

#ifndef __VERTICALPANEL_H__
#define __VERTICALPANEL_H__

#include <stddef.h>
#include <stdint.h>

#include "NavigationController.h"
#include "Control.h"
#include "PanelControlContainer.h"


namespace ATL {


template<const uint8_t MaxItems>
class VerticalPanel : public PanelControlContainer<MaxItems>
{
	typedef PanelControlContainer<MaxItems> BaseT;

public:
	VerticalPanel(uint8_t pos = 0)
		: BaseT(pos)
	{ }

	virtual bool OnNavigationCommand(NavigationCommands navCmd)
	{
		switch (navCmd)
		{
		case Up:
			return BaseT::SetPreviousInputControl();
		case Down:
			return BaseT::SetNextInputControl();
		default:
			break;
		}

		return BaseT::OnNavigationCommand(navCmd);
	}

	virtual void Display(DisplayWriter* output, Control::ControlDisplayMode mode = Control::modeNormal)
	{
		if (mode == Control::modeCursor)
		{
			BaseT::Display(output, mode);
			return;
		}

		for (uint8_t i = 0; i < BaseT::getCount(); i++)
		{
			Control* ctrl = BaseT::GetAt(i);

			if (ctrl->getIsVisible())
			{
				output->GoTo(ctrl->getPosition(), 0);
				ctrl->Display(output, mode);
			}
		}
	}
};


} // ATL

#endif //__VERTICALPANEL_H__