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

#ifndef __PAGE_H__
#define __PAGE_H__

#include <stddef.h>
#include <stdint.h>

#include "NavigationController.h"
#include "ControlContainer.h"
#include "InputControl.h"
#include "DisplayWriter.h"
#include "VerticalPanel.h"

namespace ATL {

template<const unsigned char MaxLines>
class Page : public VerticalPanel<MaxLines>
{
	typedef VerticalPanel<MaxLines> BaseT;

public:
	Page() {}

	Page(PanelBase* line1, PanelBase* line2)
    {
		Add(line1);
		Add(line2);
    }

	Page(PanelBase* line1, PanelBase* line2, PanelBase* line3, PanelBase* line4)
	{
		Add(line1);
		Add(line2);
		Add(line3);
		Add(line4);
	}

	inline void Add(PanelBase* line)
	{
		if (line == NULL) return;

		if (line->getPosition() == 0)
		{
			line->setPosition(BaseT::getCount());
		}

		BaseT::Add(line);
	}

    virtual void Display(DisplayWriter* output)
    {
		BaseT::Display(output);
        DisplayCursor(output);
    }

    virtual bool OnKeyCommand(KeyCommands keyCmd)
    {
        bool handled = false;

        switch(keyCmd)
        {
            case Up:
            handled = TrySelectPreviousLine();
            break;
            case Down:
            handled = TrySelectNextLine();
            break;
            default:
            break;
        }

        if (handled) return true;

        // skip VerticalPanel!
        return Panel<MaxLines>::OnKeyCommand(keyCmd);
    }

    bool TrySelectNextLine()
    {
        InputControl* currentCtrl = getCurrentInputControl();

        if (currentCtrl == NULL ||
           (currentCtrl != NULL && !currentCtrl->isSelected()))
        {
			if (BaseT::SetNextInputControl())
            {
                //EnsureFirstControl();
                return true;
            }
        }

        return false;
    }

    bool TrySelectPreviousLine()
    {
        InputControl* currentCtrl = getCurrentInputControl();

        if (currentCtrl == NULL ||
           (currentCtrl != NULL && !currentCtrl->isSelected()))
        {
			if (BaseT::SetPreviousInputControl())
            {
                //EnsureFirstControl();
                return true;
            }
        }

        return false;
    }

	inline PanelBase* getCurrentLine() const
    {
		return (PanelBase*)Control::DynamicCast(BaseT::getCurrentControl(), typePanel);
    }

    InputControl* getCurrentInputControl() const
    {
		PanelBase* currentLine = getCurrentLine();

        if (currentLine != NULL)
        {
            return currentLine->getCurrentControl();
        }

        return NULL;
    }

protected:
    /*inline bool EnsureFirstControl()
    {
        PanelBase* line = getCurrentLine();
        return line->SetFirstInputControl();
    }*/

    inline void DisplayCursor(DisplayWriter* output)
    {
        InputControl* ctrl = getCurrentInputControl();
        if (ctrl != NULL)
        {
			PanelBase* line = getCurrentLine();
            output->SetCursor(line->getPosition(), ctrl->getPosition(), ctrl->isSelected());
        }
        else
        {
            // cursor off
            output->SetCursor(DisplayWriter::DontCare, DisplayWriter::DontCare, false);
        }
    }
};


} // ATL

#endif //__PAGE_H__