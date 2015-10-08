#include "stdafx.h"
#include "avr.h"
#include "..\ArduinoTemplateLibrary\AVR\UsartConfig.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace ATL::MCU;

namespace ArduinoTemplateLibraryTests
{
    [TestClass]
    public ref class UsartConfigTest
    {
    public: 
        [TestMethod]
        void InitAsync_9600_CorrectUBRRAndMode()
        {
            UsartConfig tested;

            // sort of default rate
            bool success = tested.InitAsync(9600);

            Assert::IsTrue(success);
            Assert::AreEqual(12, (int)tested.getUBRR());
            Assert::AreEqual((int)UsartModes::AsyncDoubleSpeed, (int)tested.getMode().value);
            //Assert::AreEqual(9600, (int)tested.getBaudRate());    //9615
        }

        [TestMethod]
        void InitAsync_31250_CorrectUBRRAndMode()
        {
            UsartConfig tested;

            // midi rate
            bool success = tested.InitAsync(31250);

            Assert::IsTrue(success);
            Assert::AreEqual(1, (int)tested.getUBRR());
            Assert::AreEqual((int)UsartModes::Async, (int)tested.getMode().value);
            Assert::AreEqual(31250, (int)tested.getBaudRate());
        }
    };
}
