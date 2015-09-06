#include "stdafx.h"
#include "Arduino.h"
#include "..\ArduinoTemplateLibrary\Time.h"
#include "..\ArduinoTemplateLibrary\Arduino\Time_Arduino.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class TimeTest
	{
	public: 
		[TestMethod]
		void MillisecondsTime()
		{
			Time<Milliseconds> time;

			unsigned long ticks = time.getMilliseconds();

			System::Threading::Thread::Sleep(1000);

			unsigned long delta = time.Update();

			Assert::AreEqual(ticks + delta, time.getMilliseconds());
		}
	};
}
