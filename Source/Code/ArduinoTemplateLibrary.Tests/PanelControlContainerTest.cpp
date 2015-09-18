#include "stdafx.h"
#include "Arduino.h"
#include "..\ArduinoTemplateLibrary\Control.h"
#include "..\ArduinoTemplateLibrary\PanelControlContainer.h"
#include "TestControls.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
    class TestPanel : public PanelControlContainer<2>
    {};

	[TestClass]
	public ref class PanelControlContainerTest
	{
	public:
		[TestMethod]
		void Panel_GetAt_FirstControl_IsIndexZero()
		{
            TestPanel tested;
			TestInputControl tic;

			tested.Add(&tic);

			Assert::IsTrue(&tic == tested.GetAt(0));
		}

		[TestMethod]
		void Panel_IndexOf_FirstControl_IsIndexZero()
		{
            TestPanel tested;
			TestInputControl tic;

			tested.Add(&tic);

			Assert::AreEqual((char)0, tested.IndexOf(&tic));
		}
	};
}
