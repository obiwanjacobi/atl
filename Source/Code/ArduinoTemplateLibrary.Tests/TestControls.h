#ifndef __TESTCONTROLS_H__
#define __TESTCONTROLS_H__

#include "Arduino.h"
#include"..\ArduinoTemplateLibrary\Control.h"
#include"..\ArduinoTemplateLibrary\InputControl.h"

using namespace ATL;

// used with UpDownControl tests
class TestValue
{
public:
	static const char* IncrementValueText;
	static const char* DecrementValueText;

	TestValue()
	{
		Text = NULL;
	}

	const char* ToString()
	{
		if (Text == NULL)
		{
			Text = "Unit Test";
		}

		return Text;
	}

	void IncrementValue()
	{
		Text = IncrementValueText;
	}

	void DecrementValue()
	{
		Text = DecrementValueText;
	}

	const char* Text;
};

class TestControl : public Control
{
public:
	TestControl() {}
};

class TestInputControl : public InputControl
{
public:
	TestInputControl() {}
};



#endif