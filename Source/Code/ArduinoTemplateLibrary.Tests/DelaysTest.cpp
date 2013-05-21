#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\Delays.h"
#include "..\ArduinoTemplateLibrary\Time.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class DelaysTest
	{
	public: 
		[TestMethod]
		void TestWait()
		{
			typedef Delays<Time<Milliseconds>, 4> MilliDelays;

			unsigned int delta = MilliDelays::Update();

			Assert::IsFalse(MilliDelays::Wait(1, delta));
			Assert::AreEqual(delta, MilliDelays::Update());
			Assert::IsTrue(MilliDelays::IsWaiting(1));
			Assert::IsTrue(MilliDelays::Wait(1, delta));
		}
	};
}
