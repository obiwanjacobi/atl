#include "stdafx.h"
#include "Arduino.h"
#include "..\ArduinoTemplateLibrary\Control.h"
#include "TestControls.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL::UI;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class InputControlTest
	{
	public:
		[TestMethod]
		void InputControl_FocusedTrySelect_SetSelectedState()
		{
			TestInputControl tic;
			// control has to have focus
			tic.setState(ControlState::Focused);

			bool successful = tic.TrySelect();

			Assert::IsTrue(successful);
			Assert::IsTrue(tic.isSelected());
		}

		[TestMethod]
		void InputControl_SelectedTryDeselect_ResetSelectedState()
		{
			TestInputControl tic;
			// control has to be selected
			tic.setState(ControlState::Selected);

			bool successful = tic.TryDeselect();

			Assert::IsTrue(successful);
			Assert::IsTrue(tic.isFocussed());
		}

		[TestMethod]
		void InputControl_NormalTrySelect_ReturnFalse()
		{
			TestInputControl tic;

			bool successful = tic.TrySelect();

			Assert::IsFalse(successful);
			Assert::IsFalse(tic.isSelected());
		}

		[TestMethod]
		void InputControl_NormalTryDeselect_ReturnFalse()
		{
			TestInputControl tic;

			bool successful = tic.TryDeselect();

			Assert::IsFalse(successful);
			Assert::IsFalse(tic.isFocussed());
		}

		[TestMethod]
		void InputControl_FocusedKeyEnter_SetSelectedState()
		{
			TestInputControl tic;
			// control has to have focus
			tic.setState(ControlState::Focused);

			bool successful = tic.OnKeyCommand(KeyCommands::Enter);

			Assert::IsTrue(successful);
			Assert::IsTrue(tic.isSelected());
		}

		[TestMethod]
		void InputControl_SelectedKeyExit_ResetSelectedState()
		{
			TestInputControl tic;
			// control has to be selected
			tic.setState(ControlState::Selected);

			bool successful = tic.OnKeyCommand(KeyCommands::Exit);

			Assert::IsTrue(successful);
			Assert::IsTrue(tic.isFocussed());
		}
	};
}
