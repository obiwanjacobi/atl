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

#ifndef __UPDOWNCONTROL_H__
#define __UPDOWNCONTROL_H__

#include "InputControl.h"

namespace ATL {


// ValueT implements: const char* ToString();
//                    void IncrmentValue();
//                    void DecrmentValue();
template<class ValueT>
class UpDownControl : public InputControl
{
public:
	UpDownControl(ValueT* value, uint8_t pos = 0)
		: InputControl(pos), _value(value)
	{ }

	virtual void Display(DisplayWriter* output)
	{
		InputControl::Display(output);

		output->Write(_value->ToString());
	}

	virtual bool OnNavigationCommand(NavigationCommands navCmd)
	{
		bool handled = false;

		switch (navCmd)
		{
		case Up:
			handled = TryValueUp();
			break;
		case Down:
			handled = TryValueDown();
			break;
		default:
			break;
		}

		if (handled) return true;

		return InputControl::OnNavigationCommand(navCmd);
	}

	bool TryValueUp()
	{
		if (isSelected())
		{
			_value->IncrementValue();
			return true;
		}

		return false;
	}

	bool TryValueDown()
	{
		if (isSelected())
		{
			_value->DecrementValue();
			return true;
		}

		return false;
	}

private:
	ValueT* _value;
};


} // ATL

#endif //__UPDOWNCONTROL_H__