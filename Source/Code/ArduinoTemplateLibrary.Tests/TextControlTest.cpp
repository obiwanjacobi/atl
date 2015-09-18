#include "stdafx.h"
#include "../ArduinoTemplateLibrary/TextControl.h"
#include "../ArduinoTemplateLibrary/FixedString.h"
#include "../ArduinoTemplateLibrary/Iterator.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	class TestCharArray
	{
	public:
		typedef char ItemT;

		bool IsValidIndex(int16_t index) const
		{
			return index >= 0 && index <= 0x7F;
		}

		int16_t IndexOf(char item) const
		{
			return (int16_t)item;
		}

		char GetAt(uint16_t index) const
		{
			return (char)index;
		}
	};

	typedef Iterator<TestCharArray> TestIterator;

	[TestClass]
	public ref class TextControlTest
	{
		typedef TextControl<FixedString<6>, TestIterator> TestTextControl;

	public: 
		[TestMethod]
		void TextControl_TryMoveCursorLeft_Selected_Success()
		{
			FixedString<6> text;
			TestIterator iterator;
			TestTextControl ctrl(&text, &iterator);

			// select text control
			bool success = ctrl.setState(Control::stateSelected);
			Assert::IsTrue(success);

			success = ctrl.TryMoveCursorLeft();
			Assert::IsTrue(success);
		}

		[TestMethod]
		void TextControl_TryMoveCursorRight_Selected_Success()
		{
			FixedString<6> text;
			TestIterator iterator;
			TestTextControl ctrl(&text, &iterator);

			// select text control
			bool success = ctrl.setState(Control::stateSelected);
			Assert::IsTrue(success);

			success = ctrl.TryMoveCursorRight();
			Assert::IsTrue(success);
		}

		[TestMethod]
		void TextControl_TryMoveCursorRight_Selected_CursorNotMoved()
		{
			FixedString<6> text;
			TestIterator iterator;
			TestTextControl ctrl(&text, &iterator);

			// select text control
			bool success = ctrl.setState(Control::stateSelected);
			Assert::IsTrue(success);
			char expected = iterator.getCurrent();

			success = ctrl.TryMoveCursorRight();
			// iterator still at same pos
			Assert::AreEqual((int)expected, (int)iterator.getCurrent());
			// the cursor has not moved, but it is still successful (handled)
			Assert::IsTrue(success);
		}
	};
}
