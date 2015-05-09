#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\BitArray.h"

using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class BitArrayTest
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
		void Constructor_Initialization_Test()
		{
			BitArray<unsigned char> tested(0x04);

			Assert::IsTrue(tested.IsTrue(2));
		}

		[TestMethod]
		void Set_MultiBit_Test()
		{
			BitArray<unsigned char> tested;

			// 0x11 masked to 0x01
			tested.Set(3, 0x11, 2);

			Assert::AreEqual((unsigned char)tested, (unsigned char)0x08);
		}

		[TestMethod]
		void Get_MultiBit_Test()
		{
			BitArray<unsigned char> tested(0x08);

			Assert::AreEqual(tested.Get(3, 2), (unsigned char)0x01);
		}
	};
}
