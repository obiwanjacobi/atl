#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\ValueContainer.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class ValueContainerTest
	{
	private:
		TestContext^ testContextInstance;

	public: 
		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		[TestMethod]
		void InitWithAny_IsInRange_Test()
		{
			int expected = 12345;
			ValueContainer<int> target;
			target.SetAny();

			Assert::IsTrue(target.IsInRange(expected));
		};

		[TestMethod]
		void InitWithNone_IsInRange_Test()
		{
			int expected = 12345;
			ValueContainer<int> target;
			target.SetNone();

			Assert::IsFalse(target.IsInRange(expected));
		};

		[TestMethod]
		void InitWithSingleValue_getMode_Test()
		{
			int expected = 12345;
			ValueContainer<int> target;
			target.SetSingle(expected);

			Assert::AreEqual((int)ValueContainer<int>::Single, (int)target.getMode());
		};

		[TestMethod]
		void InitWithSingleValue_getValue_Test()
		{
			int expected = 12345;
			ValueContainer<int> target;
			target.SetSingle(expected);

			Assert::AreEqual(expected, target.getValue());
		};

		[TestMethod]
		void InitWithSingleValue_IsInRange_Test()
		{
			int expected = 12345;
			ValueContainer<int> target;
			target.SetSingle(expected);

			Assert::IsTrue(target.IsInRange(expected));
		};

		[TestMethod]
		void InitWithRange_getMode_Test()
		{
			int begin = 1234;
			int end = 12345;
			ValueContainer<int> target;
			target.SetRange(begin, end);

			Assert::AreEqual((int)ValueContainer<int>::Range, (int)target.getMode());
		};

		[TestMethod]
		void InitWithRange_IsInRange_Test()
		{
			int begin = 1234;
			int end = 12345;
			ValueContainer<int> target;
			target.SetRange(begin, end);

			Assert::IsTrue(target.IsInRange(begin));
			Assert::IsTrue(target.IsInRange(end));
		};

		[TestMethod]
		void InitWithRange_Normalize_Test()
		{
			int begin = 1234;
			int end = 12345;
			ValueContainer<int> target;
			target.SetRange(end, begin);
			target.Normalize();

			Assert::AreEqual(begin, target.getBegin());
			Assert::AreEqual(end, target.getEnd());
		};

		[TestMethod]
		void InitWithReverseRange_IsInRange_Test()
		{
			int begin = 1234;
			int end = 12345;
			ValueContainer<int> target;
			target.SetRange(end, begin);

			Assert::IsTrue(target.IsInRange(begin));
			Assert::IsTrue(target.IsInRange(end));
		};
	};
}
