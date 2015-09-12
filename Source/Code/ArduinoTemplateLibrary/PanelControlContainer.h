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

#ifndef __PANELCONTROLCONTAINER_H__
#define __PANELCONTROLCONTAINER_H__

#include <stddef.h>
#include <stdint.h>
#include "ControlContainer.h"
#include "InputControl.h"
#include "Panel.h"

namespace ATL {

// abstract
template<const uint8_t MaxItems>
class PanelControlContainer : public Panel,
	                          public ControlContainer<MaxItems>
{
	typedef ControlContainer<MaxItems> BaseT;

public:
	bool SetFirstInputControl()
	{
		InputControl* ctrl = (InputControl*)BaseT::getNext(NULL, typeInputControl);
		if (ctrl != NULL)
		{
			setCurrentControl(ctrl);
			return true;
		}

		return false;
	}

	bool SetNextInputControl()
	{
		InputControl* ctrl = (InputControl*)BaseT::getNext(getCurrentControl(), typeInputControl);
		if (ctrl != NULL)
		{
			setCurrentControl(ctrl);
			return true;
		}

		return false;
	}

	bool SetPreviousInputControl()
	{
		InputControl* ctrl = (InputControl*)BaseT::getPrevious(getCurrentControl(), typeInputControl);
		if (ctrl != NULL)
		{
			setCurrentControl(ctrl);
			return true;
		}

		return false;
	}

protected:
	PanelControlContainer(uint8_t pos = 0)
		: Panel(pos)
	{ }
};


} // ATL

#endif //__PANELCONTROLCONTAINER_H__