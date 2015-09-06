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
#include "Control.h"
#include "InputControl.h"
#include "Panel.h"

namespace ATL {

template<const unsigned char MaxItems>
class Line : public HorizontalPanel<MaxItems>
{
public:
    Line(uint8_t pos = 0)
        : HorizontalPanel(pos)
    { }
};


class Page : public VerticalPanel<2>
{
public:
    Page(Panel* line1, Panel* line2)
    {
        Add(line1);
        Add(line2);
    }

    virtual void Display(DisplayWriter* output)
    {
        VerticalPanel::Display(output);
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
        return Panel::OnKeyCommand(keyCmd);
    }

    bool TrySelectNextLine()
    {
        InputControl* currentCtrl = getCurrentInputControl();

        if (currentCtrl == NULL ||
           (currentCtrl != NULL && !currentCtrl->isSelected()))
        {
            if (VerticalPanel::SetNextInputControl())
            {
                EnsureFirstControl();
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
            if (VerticalPanel::SetPreviousInputControl())
            {
                EnsureFirstControl();
                return true;
            }
        }

        return false;
    }

    inline Panel* getCurrentLine() const
    {
        return (Panel*)Control::DynamicCast(getCurrentControl(), typePanel);
    }

    InputControl* getCurrentInputControl() const
    {
        Panel* currentLine = getCurrentLine();

        if (currentLine != NULL)
        {
            return currentLine->getCurrentControl();
        }

        return NULL;
    }

protected:
    inline bool EnsureFirstControl()
    {
        Panel* line = getCurrentLine();
        return line->SetFirstInputControl();
    }

    inline void DisplayCursor(DisplayWriter* output)
    {
        InputControl* ctrl = getCurrentInputControl();
        if (ctrl != NULL)
        {
            Panel* line = getCurrentLine();
            output->SetCursor(line->getPosition(), ctrl->getPosition(), ctrl->isSelected());
        }
        else
        {
            // cursor off
            output->SetCursor(DisplayWriter::DontCare, DisplayWriter::DontCare, false);
        }
    }
};


template<const unsigned char MaxItems>
class PageController : public ControlContainer<MaxItems>
{
public:
    inline Page* getCurrentPage() const
    {
        return _currentPage;
    }

private:
    Page* _currentPage;
};




} // ATL

#endif //__PAGE_H__