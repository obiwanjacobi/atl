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

#include "BitArray.h"
#include "Delays.h"
#include "Task.h"

namespace ATL {

	/*
		The different states the PushButton can be in.
	 */
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
	The class implements full tactile push button handling, including debouncing and hold detection.

	BaseT is used as base class and implements:
		bool [IO::DigitalInputPin] Read();
		uint16_t [IdentifiableObject] getId();
	DelaysT see Delays.h
	debounceTimeout: timeout for contact debounce in units used in DelaysT
	holdTimout: button contact closed timeout for stateHold
	InverseValue: how digital input value translates to button state
		false => 0=stateOpen | 1=stateClosed
		true => 0=stateClosed | 1=stateOpen
*/
template<class BaseT, typename DelaysT, 
	const timeout_t debounceTimeout, const timeout_t holdTimeout, 
	const bool InverseValue=false>
class PushButton : public BaseT
{
	// bit array indexes
	#define CurrentStateIndex 0
	#define PrevStateIndex 3
	#define ButtonStateLength 3

public:

	/*
		Call this method repeatedly (main loop).
		Returns true when the task is yielding.
	 */
	Task_Begin(ScanButton)
	{
		SampleButtonState();

		// debounce
		if (DebounceButton())
		{
			Task_YieldUntil(WaitForDebounce());

			setPrevState(getState());
			setState(ConvertToButtonState(BaseT::Read()));
		}

		// hold
		if (getState() == stateClosed)
		{
			if(WaitForHold())
			{
				setPrevState(getState());
				setState(stateHold);
			}
		}
		else if (DelaysT::IsWaiting(BaseT::getId()))
		{
			DelaysT::Clear(BaseT::getId());
		}
	}
	Task_End

	/*
		Returns the current state of the push button.
	 */
	inline ButtonStates getState() const
	{
		return (ButtonStates)_states.Get(CurrentStateIndex, ButtonStateLength);
	}

	/*
		Returns the debounceTimeout template parameter.
	 */
	inline timeout_t getDebounceTimeout() const
	{
		return debounceTimeout;
	}

	/*
		Returns the holdTimeout template parameter.
	 */
	inline timeout_t getHoldTimeout() const
	{
		return holdTimeout;
	}

	/*
		Returns the InverseValue template parameter.
	 */
	inline bool getInverseValue() const
	{
		return InverseValue;
	}

private:
	int _task;
	BitArray<byte> _states;

	inline void SampleButtonState()
	{
		ButtonStates newState = ConvertToButtonState(BaseT::Read());
		ButtonStates state = getState();

		// new state, but not in hold
		if (state != newState 
			&& !(newState == stateClosed && state == stateHold)
			)
		{
			setPrevState(state);
			setState(newState);
		}
	}

	inline bool DebounceButton()
	{
		ButtonStates prevState = getPrevState();
		ButtonStates state = getState();

		// button changed (meaningful) states
		if (prevState != state 
			&& state != stateHold
			&& prevState != stateUnknown 
			&& prevState != statePending
			)
		{
			DelaysT::Clear(BaseT::getId());
			setState(statePending);
			return true;
		}

		return false;
	}

	inline ButtonStates getPrevState() const
	{
		return (ButtonStates)_states.Get(PrevStateIndex, ButtonStateLength);
	}

	inline void setPrevState(ButtonStates state)
	{
		_states.Set(PrevStateIndex, state, ButtonStateLength);
	}

	inline void setState(ButtonStates state)
	{
		_states.Set(CurrentStateIndex, state, ButtonStateLength);
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

} // ATL

#endif //__PUSHBUTTON_H__