#include "stdafx.h"
#include "Arduino.h"
#include "..\ArduinoTemplateLibrary\Control.h"
#include "..\ArduinoTemplateLibrary\Page.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class PageTest
	{
	public: 
		[TestMethod]
		void TestMethod1()
		{
			Line<2> line1;
			Line<2> line2;
			Page page(&line1, &line2);
		}
	};
}
