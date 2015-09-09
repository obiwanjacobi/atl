#include "stdafx.h"
#include "Arduino.h"
#include "..\ArduinoTemplateLibrary\Control.h"
#include "..\ArduinoTemplateLibrary\Line.h"
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
		void Page_SetFirstInputControl_SelectsFirstLine()
		{
			Line<2> line1;
			Line<2> line2;
			Page<2> page(&line1, &line2);

			bool success = page.SetFirstInputControl();

			Assert::IsTrue(success);
			Assert::IsTrue(&line1 == page.getCurrentLine());
		}

		[TestMethod]
		void Page_TrySelectNextLine_SelectsSecondLine()
		{
			Line<2> line1;
			Line<2> line2;
			Page<2> page(&line1, &line2);

			page.SetFirstInputControl();
			bool success = page.TrySelectNextLine();

			Assert::IsTrue(success);
			Assert::IsTrue(&line2 == page.getCurrentLine());
		}
	};
}
