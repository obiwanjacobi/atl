#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\BitArray.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class BitArrayTest
	{
        typedef BitArray<uint8_t> TestBitArray;

    public:
		[TestMethod]
		void Constructor_Initialization_Test()
		{
			TestBitArray tested(0x04);

			Assert::IsTrue(tested.IsTrue(2));
		}

        [TestMethod]
        void Set_Bit_Test()
        {
            TestBitArray tested;

            tested.Set(3, true);

            Assert::AreEqual((int)tested, (int)0x08);
        }

        [TestMethod]
        void Set_BitToFalse_Test()
        {
            TestBitArray tested(0x08);

            tested.Set(3, false);

            Assert::AreEqual((int)tested, (int)0);
        }

        [TestMethod]
        void Get_Bit_Test()
        {
            TestBitArray tested(0x08);

            Assert::IsTrue(tested.Get(3));
        }

		[TestMethod]
		void Set_MultiBit_Test()
		{
			TestBitArray tested;

			// 0x11 masked to 0x01
			tested.Set(3, 0x11, 2);

			Assert::AreEqual((int)tested, (int)0x08);
		}

		[TestMethod]
		void Get_MultiBit_Test()
		{
			TestBitArray tested(0x08);

			Assert::AreEqual((int)tested.Get(3, 2), (int)0x01);
		}

        [TestMethod]
        void Reverse_MultiBit_Test()
        {
            // 01010101
            TestBitArray tested(0x55);

            tested.Reverse();

            Assert::AreEqual((int)tested, (int)0xAA);
        }
	};
}
