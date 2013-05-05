#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\Time.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

// Faking time
static unsigned long g_ticks = 0;

unsigned long millis()
{
	g_ticks += 13;
	return g_ticks;
}

unsigned long micros()
{
	g_ticks += 133;
	return g_ticks;
}


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

			unsigned long delta = time.Update();

			Assert::AreEqual(ticks + delta, time.getMilliseconds());
		}
	};
}
