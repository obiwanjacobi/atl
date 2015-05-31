/*
 * Button.h
 *
 * Created: 16-5-2015 10:42:44
 *  Author: Marc
 */


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../BitArray.h"

namespace ATL {
namespace IO {

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


template <class BaseT, const bool InverseValue=false>
class Button : public BaseT
{
    // bit array indexes
    #define CurrentStateIndex 0
    #define PrevStateIndex 3
    #define ButtonStateLength 3

public:
    /*
		Returns the current state of the push button.
	 */
	inline ButtonStates getButtonState() const
	{
		return (ButtonStates)_states.Get(CurrentStateIndex, ButtonStateLength);
	}

    inline void SetButtonValue()
    {
        SetButtonValue(BaseT::Read());
    }

protected:
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

    inline static ButtonStates ConvertToButtonState(bool value)
    {
        return Implementation::ConvertBoolToButtonState<InverseValue>::Convert(value);
    }

    inline void SetButtonValue(bool newValue)
    {
        SetButtonState(ConvertToButtonState(newValue));
    }

    inline bool SetButtonState(ButtonStates newState)
    {
        ButtonStates state = getButtonState();

        // new state, but not in hold
        if (state != newState &&
        !(newState == stateClosed && state == stateHold))
        {
            setPrevState(state);
            setState(newState);

            return true;
        }

        return false;
    }

private:
    BitArray<unsigned char> _states;
};

}} // ATL::IO

#endif /* BUTTON_H_ */