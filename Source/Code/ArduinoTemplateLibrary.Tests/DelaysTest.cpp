#include "stdafx.h"

#define ATL_Delays_MaxItems 4
#include "..\ArduinoTemplateLibrary\Delays.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;



//// Faking time
//static unsigned long g_ticks = 0;
//
//unsigned long millis()
//{
//	g_ticks += 13;
//	return g_ticks;
//}
//
//unsigned long micros()
//{
//	g_ticks += 133;
//	return g_ticks;
//}

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class DelaysTest
	{
	public: 
		[TestMethod]
		void TestWait()
		{
			typedef Delays<Milliseconds> MilliDelays;

			unsigned int delta = MilliDelays::Update();

			Assert::IsFalse(MilliDelays::Wait(1, delta));
			Assert::AreEqual(delta, MilliDelays::Update());
			Assert::IsTrue(MilliDelays::IsWaiting(1));
			Assert::IsTrue(MilliDelays::Wait(1, delta));
		}
	};
}