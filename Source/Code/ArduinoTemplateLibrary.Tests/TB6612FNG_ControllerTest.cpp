#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\MotorTypes.h"
#include "..\ArduinoTemplateLibrary\TB6612FNG_Controller.h"
#include "TB6612FNG_DriverMock.h"

using namespace ATL::Hardware::Motor;

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace ArduinoTemplateLibraryTests
{
	typedef TB6612FNG_Controller<TB6612FNG_DriverMock> TB6612FNG_TestController;
	
	[TestClass]
	public ref class TB6612FNG_ControllerTest
	{
	public: 
		[TestMethod]
		void TestStop()
		{
			TB6612FNG_TestController controller;

			controller.Drive(MotorMode::Stop, 0);

			Assert::IsTrue(controller.Assert(false, false, 0));
		}

		[TestMethod]
		void TestBreak()
		{
			TB6612FNG_TestController controller;

			controller.Drive(MotorMode::Break, 0);

			Assert::IsTrue(controller.Assert(true, true, 0));
		}

		[TestMethod]
		void TestClockwise()
		{
			TB6612FNG_TestController controller;

			controller.Drive(MotorMode::Clockwise, 123);

			Assert::IsTrue(controller.Assert(true, false, 123));
		}

		[TestMethod]
		void TestCounterClockwise()
		{
			TB6612FNG_TestController controller;

			controller.Drive(MotorMode::CounterClockwise, 123);

			Assert::IsTrue(controller.Assert(false, true, 123));
		}
	};
}
