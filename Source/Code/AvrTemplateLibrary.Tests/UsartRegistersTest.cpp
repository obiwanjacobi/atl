#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\AVR\UsartRegisters.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace ATL::MCU;

namespace AvrTemplateLibraryTests
{
    [TestClass]
    public ref class UsartRegistersTest
    {
    public: 
        [TestInitialize]
        void TestInitialize()
        {
            Registers::Clear();
        }

        [TestMethod]
        void Usart_UBRR0_Index()
        {
            volatile uint16_t& reg = UsartRegisters<UsartIds::UsartId0>::getUBRR();
            reg = 107;

            Assert::AreEqual(107, (int)UBRR0);
        }

        [TestMethod]
        void Usart_UCSR0A_Index()
        {
            volatile uint8_t& reg = UsartRegisters<UsartIds::UsartId0>::getUCSRA();
            reg = 107;

            Assert::AreEqual(107, (int)UCSR0A);
        }

        [TestMethod]
        void Usart_UCSR0B_Index()
        {
            volatile uint8_t& reg = UsartRegisters<UsartIds::UsartId0>::getUCSRB();
            reg = 107;

            Assert::AreEqual(107, (int)UCSR0B);
        }

        [TestMethod]
        void Usart_UCSR0C_Index()
        {
            volatile uint8_t& reg = UsartRegisters<UsartIds::UsartId0>::getUCSRC();
            reg = 107;

            Assert::AreEqual(107, (int)UCSR0C);
        }
    };
}
