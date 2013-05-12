/*  
	Arduino Template Library http://atl.codeplex.com
	Written by Marc Jacobi
	Copyright 2012-2013 All Rights Reserved

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

#ifndef __PUSHBUTTON_H__
#define __PUSHBUTTON_H__

namespace ATL {
namespace IO {

/*
	BaseT is used as base class and implements:

	bool [IO.Hardware.]Read();
	bool [IO.Hardware.]getValue();

	void OnButtonStateChanged(ButtonState state);
*/

// TODO: Implement debounce and hold timeout

template<class BaseT>
class PushButton : public BaseT
{
public:
	enum ButtonStates
	{
		stateUnknown,
		stateOpen,
		stateClosed,
		
		// TODO: impl
		//stateHold,
	};

	PushButton() 
		: _state(stateUnknown)
	{
	}

	// call this method repeatedly (main loop)
	bool ScanButton()
	{
		if (BaseT::Read())
		{
			SetState(BaseT::getValue());
			return true;
		}

		if(_state == stateUnknown)
		{
			SetState(false);
		}

		return false;
	}

	ButtonStates getState() const
	{
		return _state;
	}

private:
	ButtonStates _state;

	void SetState(bool value)
	{
		_state = value ? stateClosed : stateOpen;
	}
};

}} // ATL.IO

#endif //__PUSHBUTTON_H__