#ifndef __DIGITALINPUT_H__
#define __DIGITALINPUT_H__

namespace ATL {
namespace IO {

/*
	BaseT is used as base class and implements:

	bool [IO.Hardware.]Read();
*/
template<class BaseT>
class DigitalInput : public BaseT
{
public:
	DigitalInput()
	{
		_value = false;
	}

	bool Read()
	{
		bool value = BaseT::Read();

		if (_value != value)
		{
			_value = value;
			return true;
		}

		return false;
	}

	bool getValue() const
	{
		return _value;
	}

private:
	bool _value;
}

}} // ATL.IO

#endif //__DIGITALINPUT_H__