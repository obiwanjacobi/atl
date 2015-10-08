#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\Bit.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
    [TestClass]
    public ref class BitTest
    {
        const static uint8_t TestBitValue = 0x04;
        
    public:
        [TestMethod]
        void Bit_Set8_Test()
        {
            uint8_t target = 0;
            Bit<2>::Set(target);

            Assert::AreEqual(TestBitValue, target);
        }

        [TestMethod]
        void Bit_Set16_Test()
        {
            uint16_t target = 0;
            Bit<2 + 8>::Set(target);

            Assert::AreEqual((uint16_t)(TestBitValue << 8), target);
        }

        [TestMethod]
        void Bit_Set32_Test()
        {
            uint32_t target = 0;
            Bit<2 + 16>::Set(target);

            Assert::AreEqual((uint32_t)(TestBitValue << 16), target);
        }

        [TestMethod]
        void Bit_SetIsTrue_Test()
        {
            uint8_t target = 0;
            Bit<2>::Set(target);

            Assert::AreEqual(true, Bit<2>::IsTrue(target));
        }

        [TestMethod]
        void Bit_SetIsFalse_Test()
        {
            uint8_t target = TestBitValue;
            Bit<2>::Set(target, false);

            Assert::AreEqual(true, Bit<2>::IsFalse(target));
        }
    };
}
