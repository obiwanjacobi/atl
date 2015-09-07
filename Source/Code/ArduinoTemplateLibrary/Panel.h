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


// abstract
template<const unsigned char MaxItems>
class Panel : public InputControl,
              public ControlContainer<MaxItems>
{
	typedef ControlContainer<MaxItems> CollecitonT;

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
		InputControl* ctrl = (InputControl*)CollecitonT::getNext(NULL, typeInputControl);
        if (ctrl != NULL)
        {
            setCurrentControl(ctrl);
            return true;
        }

        return false;
    }

    bool SetNextInputControl()
    {
		InputControl* ctrl = (InputControl*)CollecitonT::getNext(_currentControl, typeInputControl);
        if (ctrl != NULL)
        {
            setCurrentControl(ctrl);
            return true;
        }

        return false;
    }

    bool SetPreviousInputControl()
    {
		InputControl* ctrl = (InputControl*)CollecitonT::getPrevious(_currentControl, typeInputControl);
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

    virtual bool BeforeChangeState(ControlState newState)
    {
        return newState != Selected;
    }

private:
    InputControl* _currentControl;
};



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
        switch(keyCmd)
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


template<const unsigned char MaxItems>
class VerticalPanel : public Panel<MaxItems>
{
	typedef Panel<MaxItems> PanelT;

public:
    VerticalPanel(uint8_t pos = 0)
        : PanelT(pos)
    { }

    virtual bool OnKeyCommand(KeyCommands keyCmd)
    {
        switch(keyCmd)
        {
            case Up:
				return PanelT::SetPreviousInputControl();
            case Down:
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
                output->GoTo(ctrl->getPosition(), 0);
                ctrl->Display(output);
            }

			ctrl = PanelT::getNext(ctrl);
        }
    }
};


} // ATL

#endif //__PANEL_H__