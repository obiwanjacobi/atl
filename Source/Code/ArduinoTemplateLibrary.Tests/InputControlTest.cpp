#include "stdafx.h"
#include "Arduino.h"
#include "..\ArduinoTemplateLibrary\Control.h"
#include "TestControls.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class InputControlTest
	{
	public:
		[TestMethod]
		void InputControl_NormalTrySelect_Fails()
		{
			TestInputControl tic;

			bool successful = tic.TrySelect();

			Assert::IsFalse(successful);
			Assert::AreEqual((int)ControlState::Normal, (int)tic.getState().value);
		}

		[TestMethod]
		void InputControl_FocusedTrySelect_SetSelectedState()
		{
			TestInputControl tic;
			// control has to have focus
			tic.setState(ControlState::Focused);

			bool successful = tic.TrySelect();

			Assert::IsTrue(successful);
			Assert::IsTrue(tic.getIsSelected());
		}

		[TestMethod]
		void InputControl_SelectedTryDeselect_ResetSelectedState()
		{
			TestInputControl tic;
			// control has to be selected
			tic.setState(ControlState::Selected);

			bool successful = tic.TryDeselect();

			Assert::IsTrue(successful);
			Assert::IsTrue(tic.getIsFocussed());
		}

		[TestMethod]
		void InputControl_NormalTrySelect_ReturnFalse()
		{
			TestInputControl tic;

			bool successful = tic.TrySelect();

			Assert::IsFalse(successful);
			Assert::IsFalse(tic.getIsSelected());
		}

		[TestMethod]
		void InputControl_NormalTryDeselect_ReturnFalse()
		{
			TestInputControl tic;

			bool successful = tic.TryDeselect();

			Assert::IsFalse(successful);
			Assert::IsFalse(tic.getIsFocussed());
		}

		[TestMethod]
		void InputControl_FocusedKeyEnter_SetSelectedState()
		{
			TestInputControl tic;
			// control has to have focus
			tic.setState(ControlState::Focused);

			bool successful = tic.OnNavigationCommand(NavigationCommands::Enter);

			Assert::IsTrue(successful);
			Assert::IsTrue(tic.getIsSelected());
		}

		[TestMethod]
		void InputControl_SelectedKeyExit_ResetSelectedState()
		{
			TestInputControl tic;
			// control has to be selected
			tic.setState(ControlState::Selected);

			bool successful = tic.OnNavigationCommand(NavigationCommands::Exit);

			Assert::IsTrue(successful);
			Assert::IsTrue(tic.getIsFocussed());
		}
	};
}
