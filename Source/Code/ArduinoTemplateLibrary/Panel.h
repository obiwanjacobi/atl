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

#include "Array.h"
#include "Collection.h"
#include "Control.h"
#include "InputControl.h"

using namespace ATL;

namespace ATL {
namespace UI {

template<const unsigned char MaxItems>
class ControlContainer : public Collection<Array<Control*, MaxItems> >
{
public:
	ControlContainer()
		: Collection<Array<Control*, MaxItems> >(_array)
	{ }

    Control* getNext(Control* currentCtrl, ControlTypes type = typeControl) const
    {
        int8_t index = IndexOf(currentCtrl);

        if (index != -1)
        {
            index++;
        }
        else if (getCount() > 0)
        {
            index = 0;
        }

		while (index >= 0 && index < getCount())
        {
            Control* ctrl = Control::DynamicCast(GetAt(index), type);

            if (ctrl != NULL) return ctrl;

            index++;
        }

        return NULL;
    }

    Control* getPrevious(Control* currentCtrl, ControlTypes type = typeControl) const
    {
        int8_t index = IndexOf(currentCtrl);

        if (index != -1)
        {
            index--;
        }
		else if (getCount() > 0)
        {
			index = getCount() - 1;
        }

		while (index >= 0 && index < getCount())
        {
            Control* ctrl = Control::DynamicCast(GetAt(index), type);

            if (ctrl != NULL) return ctrl;

            index--;
        }

        return NULL;
    }

private:
	Array<Control*, MaxItems> _array;
};


// abstract
template<const unsigned char MaxItems>
class Panel : public InputControl,
              public ControlContainer<MaxItems>
{
public:
    inline InputControl* getCurrentControl() const
    {
        return _currentControl;
    }

    virtual bool OnKeyCommand(KeyCommands keyCmd)
    {
        if (_currentControl != NULL)
        {
            return _currentControl->OnKeyCommand(keyCmd);
        }

        return false;
    }

    bool SetFirstInputControl()
    {
        InputControl* ctrl = (InputControl*)getNext(NULL, typeInputControl);
        if (ctrl != NULL)
        {
            setCurrentControl(ctrl);
            return true;
        }

        return false;
    }

    bool SetNextInputControl()
    {
        InputControl* ctrl = (InputControl*)getNext(_currentControl, typeInputControl);
        if (ctrl != NULL)
        {
            setCurrentControl(ctrl);
            return true;
        }

        return false;
    }

    bool SetPreviousInputControl()
    {
        InputControl* ctrl = (InputControl*)getPrevious(_currentControl, typeInputControl);
        if (ctrl != NULL)
        {
            setCurrentControl(ctrl);
            return true;
        }

        return false;
    }

    void setCurrentControl(InputControl* ctrl)
    {
        if (_currentControl != NULL)
        {
            _currentControl->setState(Normal);
            setState(Normal);
        }

        _currentControl = ctrl;

        if(_currentControl != NULL)
        {
            _currentControl->setState(Focused);
            setState(Focused);
        }
    }

    virtual bool IsOfType(ControlTypes type) const
    {
        return ((typePanel & type) == typePanel) || InputControl::IsOfType(type);
    }

protected:
    Panel(uint8_t pos = 0)
        : InputControl(pos), _currentControl(NULL)
    { }

    virtual bool BeforeChangeState(ControlState currentState, ControlState newState)
    {
        return newState != Selected;
    }

private:
    InputControl* _currentControl;
};

template<const unsigned char MaxItems>
class HorizontalPanel : public Panel<MaxItems>
{
public:
    HorizontalPanel(uint8_t pos = 0)
        : Panel(pos)
    {}

    virtual bool OnKeyCommand(KeyCommands keyCmd)
    {
        switch(keyCmd)
        {
            case Left:
            return SetPreviousInputControl();
            case Right:
            return SetNextInputControl();
            default:
            break;
        }

        return Panel::OnKeyCommand(keyCmd);
    }

    virtual void Display(DisplayWriter* output)
    {
        Panel::Display(output);

        Control* ctrl = getNext(NULL);
        while (ctrl != NULL)
        {
            if (ctrl->isVisible())
            {
                output->GoTo(DisplayWriter::DontCare, ctrl->getPosition());
                ctrl->Display(output);
            }

            ctrl = getNext(ctrl);
        }
    }
};


template<const unsigned char MaxItems>
class VerticalPanel : public Panel<MaxItems>
{
public:
    VerticalPanel(uint8_t pos = 0)
        : Panel(pos)
    { }

    virtual bool OnKeyCommand(KeyCommands keyCmd)
    {
        switch(keyCmd)
        {
            case Up:
            return SetPreviousInputControl();
            case Down:
            return SetNextInputControl();
            default:
            break;
        }

        return Panel::OnKeyCommand(keyCmd);
    }

    virtual void Display(DisplayWriter* output)
    {
        Panel::Display(output);

        Control* ctrl = getNext(NULL);
        while (ctrl != NULL)
        {
            if (ctrl->isVisible())
            {
                output->GoTo(ctrl->getPosition(), 0);
                ctrl->Display(output);
            }

            ctrl = getNext(ctrl);
        }
    }
};


}} // ATL::UI

#endif //__PANEL_H__