#ifndef __TEMPLATE__
#define __TEMPLATE__

class TB6612FNG_DriverMock
{
public:
	inline void Send(bool in1, bool in2, unsigned char pwm)
	{
		_in1 = in1;
		_in2 = in2;
		_pwm = pwm;
	}

	inline bool Assert(bool in1, bool in2, unsigned char pwm)
	{
		return (_in1 == in1 && _in2 == in2 && _pwm == pwm);
	}

private:
	bool _in1;
	bool _in2;
	unsigned char _pwm;
};

#endif //__TEMPLATE__