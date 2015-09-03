#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\Bit.h"
#include "..\ArduinoTemplateLibrary\BitFlag.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class BitTest
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

		const static unsigned char TestBitIndex = 2;
		const static unsigned char TestBitValue = 0x04;
		typedef Bit<TestBitIndex> TestBit2;
		typedef BitFlag TestBit1;
		

		[TestMethod]
		void Bit2_Set_Test()
		{
			unsigned char target = 0;
			TestBit2::Set(target);

			Assert::AreEqual(TestBitValue, target);
		}

		[TestMethod]
		void Bit1_Set_Test()
		{
			unsigned char target = 0;
			TestBit1::Set(target, TestBitIndex);

			Assert::AreEqual(TestBitValue, target);
		}

		[TestMethod]
		void Bit2_SetIsTrue_Test()
		{
			unsigned char target = 0;
			TestBit2::Set(target);

			Assert::AreEqual(true, TestBit2::IsTrue(target));
		}

		[TestMethod]
		void Bit1_SetIsTrue_Test()
		{
			unsigned char target = 0;
			TestBit1::Set(target, TestBitIndex);

			Assert::AreEqual(true, TestBit1::IsTrue(target, TestBitIndex));
		}

		[TestMethod]
		void Bit2_SetIsFalse_Test()
		{
			unsigned char target = TestBitValue;
			TestBit2::Set(target, false);

			Assert::AreEqual(true, TestBit2::IsFalse(target));
		}

		[TestMethod]
		void Bit1_SetIsFalse_Test()
		{
			unsigned char target = TestBitValue;
			TestBit1::Set(target, TestBitIndex, false);

			Assert::AreEqual(true, TestBit1::IsFalse(target, TestBitIndex));
		}

		void CompileErrorTest()
		{
			unsigned char compileErr = 0;
			
			// Bit index 8 is too large for unsigned char (0-7)
			//Bit<unsigned char, 8>::Set(compileErr);
		}
	};
}
