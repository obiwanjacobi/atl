#ifndef __DIGITALOUTPUT_H__
#define __DIGITALOUTPUT_H__

namespace ATL {
namespace IO {

/*
	BaseT is used as base class and implements:

	void [IO.Hardware.]Write(bool value);
*/
template<class BaseT>
class DigitalOutput : public BaseT
{
public:
	DigitalOutput() 
		: _value(false)
	{
	}

	bool Write(bool value)
	{
		if (_value != value)
		{
			BaseT::Write(value);
			_value = value;

			return true;
		}

		return false;
	}

	bool Set()
	{
		return Write(true);
	}

	bool Reset()
	{
		return Write(false);
	}

	bool getValue() const
	{
		return _value;
	}

private:
	bool _value;
};

}} // ATL.IO

#endif //__DIGITALOUTPUT_H__