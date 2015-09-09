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


class PanelBase : public InputControl
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
			_currentControl->setState(Normal);
			setState(Normal);
		}

		_currentControl = ctrl;

		if (_currentControl != NULL)
		{
			_currentControl->setState(Focused);
			setState(Focused);
		}
	}

	virtual bool OnKeyCommand(KeyCommands keyCmd)
	{
		if (_currentControl != NULL)
		{
			return _currentControl->OnKeyCommand(keyCmd);
		}

		return false;
	}

	virtual bool IsOfType(ControlTypes type) const
	{
		return ((typePanel & type) == typePanel) || InputControl::IsOfType(type);
	}

protected:
	PanelBase(uint8_t pos = 0)
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
class Panel : public PanelBase,
	public ControlContainer<MaxItems>
{
	typedef ControlContainer<MaxItems> CollecitonT;

public:
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
		InputControl* ctrl = (InputControl*)CollecitonT::getNext(getCurrentControl(), typeInputControl);
		if (ctrl != NULL)
		{
			setCurrentControl(ctrl);
			return true;
		}

		return false;
	}

	bool SetPreviousInputControl()
	{
		InputControl* ctrl = (InputControl*)CollecitonT::getPrevious(getCurrentControl(), typeInputControl);
		if (ctrl != NULL)
		{
			setCurrentControl(ctrl);
			return true;
		}

		return false;
	}

	

protected:
	Panel(uint8_t pos = 0)
		: PanelBase(pos)
	{ }
};


	/*
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

*/


} // ATL

#endif //__PANEL_H__