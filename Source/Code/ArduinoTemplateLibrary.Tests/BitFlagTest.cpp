#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\BitFlag.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class BitFlagTest
	{
        const static uint8_t TestBitIndex = 2;
        const static uint8_t TestBitValue = 0x04;

	public: 
        [TestMethod]
        void BitFlag_Set8_Test()
        {
            uint8_t target = 0;
            BitFlag::Set(target, TestBitIndex);

            Assert::AreEqual(TestBitValue, target);
        }

        [TestMethod]
        void BitFlag_Set16_Test()
        {
            uint16_t target = 0;
            BitFlag::Set(target, TestBitIndex + 8);

            Assert::AreEqual((uint16_t)(TestBitValue << 8), target);
        }

        [TestMethod]
        void BitFlag_Set32_Test()
        {
            uint32_t target = 0;
            BitFlag::Set(target, TestBitIndex + 16);

            Assert::AreEqual((uint32_t)(TestBitValue << 16), target);
        }

        [TestMethod]
        void BitFlag_SetIsTrue_Test()
        {
            uint8_t target = 0;
            BitFlag::Set(target, TestBitIndex);

            Assert::AreEqual(true, BitFlag::IsTrue(target, TestBitIndex));
        }

        [TestMethod]
        void BitFlag_SetIsFalse_Test()
        {
            uint8_t target = TestBitValue;
            BitFlag::Set(target, TestBitIndex, false);

            Assert::AreEqual(true, BitFlag::IsFalse(target, TestBitIndex));
        }
	};
}
