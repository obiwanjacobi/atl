#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\TB6612FNG_Controller.h"
#include "TB6612FNG_DriverMock.h"

using namespace ATL;

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace ArduinoTemplateLibraryTests
{
	typedef TB6612FNG_Controller<TB6612FNG_DriverMock> TB6612FNG_TestController;
	
	[TestClass]
	public ref class TB6612FNG_ControllerTest
	{
	public: 
		[TestMethod]
		void Stop_FF0()
		{
			TB6612FNG_TestController controller;

			controller.Stop();

			Assert::IsTrue(controller.Assert(false, false, 0));
		}

		[TestMethod]
		void Break_TT0()
		{
			TB6612FNG_TestController controller;

			controller.Break();

			Assert::IsTrue(controller.Assert(true, true, 0));
		}

		[TestMethod]
		void Clockwise_FF123()
		{
			TB6612FNG_TestController controller;

			controller.Clockwise(123);

			Assert::IsTrue(controller.Assert(true, false, 123));
		}

		[TestMethod]
		void CounterClockwise_FT123()
		{
			TB6612FNG_TestController controller;

			controller.CounterClockwise(123);

			Assert::IsTrue(controller.Assert(false, true, 123));
		}
	};
}
