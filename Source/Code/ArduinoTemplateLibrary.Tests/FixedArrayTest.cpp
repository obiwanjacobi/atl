#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\FixedArray.h"


using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class FixedArrayTest
	{
		static const int MagicNumber = 42;

	public: 
		[TestMethod]
		void Array_IsValidIndex_InvalidIndex_False()
		{
			FixedArray<int, 2> tested;

			Assert::IsFalse(tested.IsValidIndex(2));
		}

		[TestMethod]
		void Array_GetAt_InvalidIndex_DefaultInt()
		{
			FixedArray<int, 2> tested;

			Assert::AreEqual(0, tested.GetAt(2));
		}

		[TestMethod]
		void Array_SetAt_ValidIndexAndValue_GetAtRetrieves()
		{
			const unsigned char testIndex = 0;
			FixedArray<int, 2> tested;

			tested.SetAt(testIndex, MagicNumber);

			Assert::AreEqual(MagicNumber, tested.GetAt(testIndex));
		}
	};
}
