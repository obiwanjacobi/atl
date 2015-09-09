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

#ifndef __HORIZONTALPANEL_H__
#define __HORIZONTALPANEL_H__

#include <stddef.h>
#include <stdint.h>

#include "DisplayWriter.h"
#include "Control.h"
#include "Panel.h"


namespace ATL {


template<const unsigned char MaxItems>
class HorizontalPanel : public Panel<MaxItems>
{
	typedef Panel<MaxItems> PanelT;

public:
	HorizontalPanel(uint8_t pos = 0)
		: PanelT(pos)
	{ }

	virtual bool OnKeyCommand(KeyCommands keyCmd)
	{
		switch (keyCmd)
		{
		case Left:
			return PanelT::SetPreviousInputControl();
		case Right:
			return PanelT::SetNextInputControl();
		default:
			break;
		}

		return PanelT::OnKeyCommand(keyCmd);
	}

	virtual void Display(DisplayWriter* output)
	{
		PanelT::Display(output);

		Control* ctrl = PanelT::getNext(NULL);
		while (ctrl != NULL)
		{
			if (ctrl->isVisible())
			{
				output->GoTo(DisplayWriter::DontCare, ctrl->getPosition());
				ctrl->Display(output);
			}

			ctrl = PanelT::getNext(ctrl);
		}
	}
};


} // ATL

#endif //__HORIZONTALPANEL_H__