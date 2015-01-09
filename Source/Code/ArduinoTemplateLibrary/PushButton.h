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

#ifndef __PUSHBUTTON_H__
#define __PUSHBUTTON_H__

#include "Task.h"

namespace ATL {
namespace IO {

	enum ButtonStates
	{
		// button state not initialized / known
		stateUnknown,
		// button contact is open / not pushed
		stateOpen,
		// button contact is closed / pushed
		stateClosed,
		// button contact remains closed / pushed (holdTimeout)
		stateHold,
		// button state sensing is pending for debounce (debounceTimeout)
		statePending,
	};

namespace Implementation {

// template with static converter function for reversed logic
template<const bool ReversedLogic>
struct ConvertBoolToButtonState
{
	inline static ButtonStates Convert(bool value)
	{
		return stateUnknown;
	}
};

template<>
struct ConvertBoolToButtonState<false>
{
	inline static ButtonStates Convert(bool value)
	{
		return value ? stateClosed : stateOpen;
	}
};

template<>
struct ConvertBoolToButtonState<true>
{
	inline static ButtonStates Convert(bool value)
	{
		return value ? stateOpen : stateClosed;
	}
};

} // ATL::IO::Implementation

/*
	BaseT is used as base class and implements:
		bool [IO::DigitalInputPin] Read();
		unsigned int [IdentifiableObject] getId();
	DelaysT see Delays.h
	debounceTimeout: timeout for contact debounce in units used in DelaysT
	holdTimout: button contact closed timeout for stateHold
	InverseValue: how digital input value translates to button state
		false => 0=stateOpen | 1=stateClosed
		true => 0=stateClosed | 1=stateOpen
*/
template<class BaseT, typename DelaysT, 
	const unsigned int debounceTimeout, const unsigned int holdTimeout, 
	const bool InverseValue=false>
class PushButton : public BaseT
{
public:

	PushButton() 
		: _state(stateUnknown), _prevState(stateUnknown)
	{ }

	// call this method repeatedly (main loop)
	// returns true when the task is yielding
	Task_Begin(ScanButton)
	{
		SampleButtonState();

		if (DebounceButton())
		{
			Task_YieldUntil(WaitForDebounce());

			_prevState = _state;
			_state = ConvertToButtonState(BaseT::Read());
		}

		// TODO: hold
	}
	Task_End

	inline ButtonStates getState() const
	{
		return _state;
	}

	inline bool hasStateChanged() const
	{
		return	_prevState != _state && 
				_prevState != stateUnknown && 
				_prevState != statePending;
	}

	inline unsigned int getDebounceTimeout() const
	{
		return debounceTimeout;
	}

	inline unsigned int getHoldTimeout() const
	{
		return holdTimeout;
	}

	inline bool getInverseValue() const
	{
		return InverseValue;
	}

private:
	int _task;
	ButtonStates _prevState;
	ButtonStates _state;

	inline void SampleButtonState()
	{
		ButtonStates newState = ConvertToButtonState(BaseT::Read());

		if (_state != newState)
		{
			_prevState = _state;
			_state = newState;
		}
	}

	inline bool DebounceButton()
	{
		// button changed (meaningful) states
		if (hasStateChanged())
		{
			_state = statePending;
			return true;
		}

		return false;
	}

	inline bool WaitForDebounce() const
	{
		return DelaysT::Wait(BaseT::getId(), getDebounceTimeout());
	}

	inline bool WaitForHold() const
	{
		return DelaysT::Wait(BaseT::getId(), getHoldTimeout());
	}

	inline static ButtonStates ConvertToButtonState(bool value)
	{
		return Implementation::ConvertBoolToButtonState<InverseValue>::Convert(value);
	}
};

}} // ATL::IO

#endif //__PUSHBUTTON_H__