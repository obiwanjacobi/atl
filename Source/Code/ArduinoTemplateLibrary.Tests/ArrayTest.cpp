#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\Array.h"
#include "..\ArduinoTemplateLibrary\ArrayRef.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class ArrayTest
	{
		static const int MagicNumber = 42;

	public: 
		[TestMethod]
		void Array_IsValidIndex_InvalidIndex_False()
		{
			Array<int, 2> tested;

			Assert::IsFalse(tested.IsValidIndex(2));
		}

		[TestMethod]
		void Array_GetAt_InvalidIndex_DefaultInt()
		{
			Array<int, 2> tested;

			Assert::AreEqual(0, tested.GetAt(2));
		}

		[TestMethod]
		void Array_SetAt_ValidIndexAndValue_GetAtRetrieves()
		{
			const unsigned char testIndex = 0;
			Array<int, 2> tested;

			tested.SetAt(testIndex, MagicNumber);

			Assert::AreEqual(MagicNumber, tested.GetAt(testIndex));
		}

		[TestMethod]
		void ArrayRef_IsValidIndex_InvalidIndex_False()
		{
			int array[2] = {};
			ArrayRef<int, 2> tested(array);

			Assert::IsFalse(tested.IsValidIndex(2));
		}

		[TestMethod]
		void ArrayRef_GetAt_InvalidIndex_DefaultInt()
		{
			int array[2] = {};
			ArrayRef<int, 2> tested(array);

			Assert::AreEqual(0, tested.GetAt(2));
		}

		[TestMethod]
		void ArrayRef_SetAt_ValidIndexAndValue_GetAtRetrieves()
		{
			const unsigned char testIndex = 0;
			int array[2] = {};
			ArrayRef<int, 2> tested(array);

			tested.SetAt(testIndex, MagicNumber);

			Assert::AreEqual(MagicNumber, tested.GetAt(testIndex));
		}
	};
}
