#include "stdafx.h"
#include "Arduino.h"
#include "..\ArduinoTemplateLibrary\Delays.h"
#include "..\ArduinoTemplateLibrary\Time.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class DelaysTest
	{
	public: 
		[TestMethod]
		[TestCategory("Static")]
		void Wait_ForDelay()
		{
			typedef Delays<Time<Milliseconds>, 4> MilliDelays;

			unsigned long delta = MilliDelays::Update();

			Assert::IsFalse(MilliDelays::Wait(1, delta));
			Assert::AreEqual(delta, MilliDelays::Update());
			Assert::IsTrue(MilliDelays::IsWaiting(1));
			Assert::IsTrue(MilliDelays::Wait(1, delta));
		}
	};
}
