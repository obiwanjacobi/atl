#include "stdafx.h"
#include "Arduino.h"
#include "..\ArduinoTemplateLibrary\Control.h"
#include "..\ArduinoTemplateLibrary\HorizontalPanel.h"
#include "..\ArduinoTemplateLibrary\VerticalPanel.h"
#include "TestControls.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class PanelTest
	{
	public:
		// generic panel/controlcontainer/collection methods

		[TestMethod]
		void HP_GetAt_FirstControl_IsIndexZero()
		{
			HorizontalPanel<2> tested;
			TestInputControl tic;

			tested.Add(&tic);

			Assert::IsTrue(&tic == tested.GetAt(0));
		}

		[TestMethod]
		void HP_IndexOf_FirstControl_IsIndexZero()
		{
			HorizontalPanel<2> tested;
			TestInputControl tic;

			tested.Add(&tic);

			Assert::AreEqual((char)0, tested.IndexOf(&tic));
		}

		//
		// Horizontal Panel Tests
		//

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

			bool handled = tested.OnNavigationCommand(Left);

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

			bool handled = tested.OnNavigationCommand(Right);

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

			bool handled = tested.OnNavigationCommand(Up);

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

			bool handled = tested.OnNavigationCommand(Down);

			Assert::IsFalse(handled);
			Assert::IsFalse(tested.getCurrentControl() != NULL);
		}

		//
		// Vertical Panel Tests
		//

		[TestMethod]
		void VP_CurrentControl_NoCurrentCtrl_Null()
		{
			VerticalPanel<2> tested;
			TestInputControl tic;

			Assert::IsFalse(tested.getCurrentControl() != NULL);

			tested.Add(&tic);

			Assert::IsFalse(tested.getCurrentControl() != NULL);
		}

		[TestMethod]
		void VP_KeyUp_NoCurrentCtrl_SelectsLastControl()
		{
			VerticalPanel<2> tested;
			TestInputControl tic1;
			TestInputControl tic2;

			tested.Add(&tic1);
			tested.Add(&tic2);

			bool handled = tested.OnNavigationCommand(Up);

			Assert::IsTrue(handled);
			Assert::IsTrue(tested.getCurrentControl() != NULL);
			Assert::IsTrue(&tic2 == tested.getCurrentControl());
		}

		[TestMethod]
		void VP_KeyDown_NoCurrentCtrl_SelectsFirstControl()
		{
			VerticalPanel<2> tested;
			TestInputControl tic1;
			TestInputControl tic2;

			tested.Add(&tic1);
			tested.Add(&tic2);

			bool handled = tested.OnNavigationCommand(Down);

			Assert::IsTrue(handled);
			Assert::IsTrue(tested.getCurrentControl() != NULL);
			Assert::IsTrue(&tic1 == tested.getCurrentControl());
		}

		[TestMethod]
		void VP_KeyLeft_NoCurrentCtrl_NotHandled()
		{
			VerticalPanel<2> tested;
			TestInputControl tic1;
			TestInputControl tic2;

			tested.Add(&tic1);
			tested.Add(&tic2);

			bool handled = tested.OnNavigationCommand(Left);

			Assert::IsFalse(handled);
			Assert::IsFalse(tested.getCurrentControl() != NULL);
		}

		[TestMethod]
		void VP_KeyRight_NoCurrentCtrl_NotHandled()
		{
			VerticalPanel<2> tested;
			TestInputControl tic1;
			TestInputControl tic2;

			tested.Add(&tic1);
			tested.Add(&tic2);

			bool handled = tested.OnNavigationCommand(Right);

			Assert::IsFalse(handled);
			Assert::IsFalse(tested.getCurrentControl() != NULL);
		}
	};
}
