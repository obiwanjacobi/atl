#include "stdafx.h"
#include "Arduino.h"
#include "..\ArduinoTemplateLibrary\Control.h"
#include "..\ArduinoTemplateLibrary\HorizontalPanel.h"
#include "TestControls.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class HorizontalPanelTest
	{
	public:
		[TestMethod]
		void HP_CurrentControl_NoCurrentCtrl_Null()
		{
			HorizontalPanel<2> tested;
			TestInputControl tic;

			Assert::IsFalse(tested.getCurrentControl() != NULL);

			tested.Add(&tic);

			Assert::IsFalse(tested.getCurrentControl() != NULL);
		}

		[TestMethod]
		void HP_KeyLeft_NoCurrentCtrl_SelectsLastControl()
		{
			HorizontalPanel<2> tested;
			TestInputControl tic1;
			TestInputControl tic2;

			tested.Add(&tic1);
			tested.Add(&tic2);

			bool handled = tested.OnNavigationCommand(NavigationCommands::Left);

			Assert::IsTrue(handled);
			Assert::IsTrue(tested.getCurrentControl() != NULL);
			Assert::IsTrue(&tic2 == tested.getCurrentControl());
		}

		[TestMethod]
		void HP_KeyRight_NoCurrentCtrl_SelectsFirstControl()
		{
			HorizontalPanel<2> tested;
			TestInputControl tic1;
			TestInputControl tic2;

			tested.Add(&tic1);
			tested.Add(&tic2);

            bool handled = tested.OnNavigationCommand(NavigationCommands::Right);

			Assert::IsTrue(handled);
			Assert::IsTrue(tested.getCurrentControl() != NULL);
			Assert::IsTrue(&tic1 == tested.getCurrentControl());
		}

		[TestMethod]
		void HP_KeyUp_NoCurrentCtrl_NotHandled()
		{
			HorizontalPanel<2> tested;
			TestInputControl tic1;
			TestInputControl tic2;

			tested.Add(&tic1);
			tested.Add(&tic2);

            bool handled = tested.OnNavigationCommand(NavigationCommands::Up);

			Assert::IsFalse(handled);
			Assert::IsFalse(tested.getCurrentControl() != NULL);
		}

		[TestMethod]
		void HP_KeyDown_NoCurrentCtrl_NotHandled()
		{
			HorizontalPanel<2> tested;
			TestInputControl tic1;
			TestInputControl tic2;

			tested.Add(&tic1);
			tested.Add(&tic2);

            bool handled = tested.OnNavigationCommand(NavigationCommands::Down);

			Assert::IsFalse(handled);
			Assert::IsFalse(tested.getCurrentControl() != NULL);
		}
	};
}
