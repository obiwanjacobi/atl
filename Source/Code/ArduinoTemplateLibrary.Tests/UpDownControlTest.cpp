#include "stdafx.h"
#include "Arduino.h"
#include "..\ArduinoTemplateLibrary\UpDownControl.h"
#include "TestControls.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class UpDownControlTest
	{
	public: 
		[TestMethod]
		void TryValueUp_NotSelected_False()
		{
			TestValue tv;
			UpDownControl<TestValue> udc(&tv);

			bool successful = udc.TryValueUp();

			Assert::IsFalse(successful);
			Assert::IsFalse(TestValue::IncrementValueText == tv.ToString());
		}

		[TestMethod]
		void TryValueUp_IsSelected_True()
		{
			TestValue tv;
			UpDownControl<TestValue> udc(&tv);

			udc.setState(ControlState::Selected);

			bool successful = udc.TryValueUp();

			Assert::IsTrue(successful);
			Assert::IsTrue(TestValue::IncrementValueText == tv.ToString());
		}

		[TestMethod]
		void TryValueDown_NotSelected_False()
		{
			TestValue tv;
			UpDownControl<TestValue> udc(&tv);

			bool successful = udc.TryValueDown();

			Assert::IsFalse(successful);
			Assert::IsFalse(TestValue::DecrementValueText == tv.ToString());
		}

		[TestMethod]
		void TryValueDown_IsSelected_True()
		{
			TestValue tv;
			UpDownControl<TestValue> udc(&tv);

			udc.setState(ControlState::Selected);

			bool successful = udc.TryValueDown();

			Assert::IsTrue(successful);
			Assert::IsTrue(TestValue::DecrementValueText == tv.ToString());
		}
	};
}
