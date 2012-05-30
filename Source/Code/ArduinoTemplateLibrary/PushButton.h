#ifndef __PUSHBUTTON_H__
#define __PUSHBUTTON_H__

namespace ATL {
namespace IO {

/*
	BaseT is used as base class and implements:

	bool [IO.Hardware.]Read();
	bool [IO.Hardware.]getValue();

	void OnButtonStateChanged(ButtonState* state);
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

	PushBustton()
	{
		_state = stateUnknown;
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

	ButtonStates getState()
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