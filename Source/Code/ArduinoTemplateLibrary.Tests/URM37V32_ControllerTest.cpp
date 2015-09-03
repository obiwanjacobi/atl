#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\URM37V32_Driver.h"
#include "..\ArduinoTemplateLibrary\URM37V32_Controller.h"
#include "TestInputStream.h"
#include "TestOutputStream.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;
using namespace ATL::Hardware::Sensor;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class URM37V32_ControllerTest
	{
	private:
		unsigned char CalcChecksum(unsigned char command, unsigned char data1, unsigned char data2)
		{
			return (command + data1 + data2);
		}

		typedef URM37V32_Controller<URM37V32_Driver<TestInputStream, TestOutputStream> > URM37V32_TestController;

	public: 
		[TestMethod]
		void SetAutonomousTriggerMode_CheckCommandsSent()
		{
			const int length = 3 * 4;	// 3 commands of 4 bytes
			unsigned char inBuffer[length];
			unsigned char outBuffer[length];

			URM37V32_TestController controller;

			controller.InitOutputStream(outBuffer, length);
			controller.InitInputStream(inBuffer, length);

			// init response
			const unsigned char Command = 0x44;
			unsigned int threshold = 67;

			inBuffer[0] = Command;
			inBuffer[1] = 0x02;
			inBuffer[2] = 0xaa;
			inBuffer[3] = CalcChecksum(inBuffer[0], inBuffer[1], inBuffer[2]);

			inBuffer[4] = Command;
			inBuffer[5] = 0x00;
			inBuffer[6] = threshold;
			inBuffer[7] = CalcChecksum(inBuffer[4], inBuffer[5], inBuffer[6]);

			inBuffer[8] = Command;
			inBuffer[9] = 0x01;
			inBuffer[10] = (threshold >> 8);
			inBuffer[11] = CalcChecksum(inBuffer[8], inBuffer[9], inBuffer[10]);
			
			controller.SetAutonomousTriggerMode(threshold);

			for(int i = 0; i < length; i++)
			{
				Assert::AreEqual(inBuffer[i], outBuffer[i]);
			}
		}

		[TestMethod]
		void SetPassiveControlMode_CheckCommandsSent()
		{
			const int length = 1 * 4;	// 1 command of 4 bytes
			unsigned char inBuffer[length];
			unsigned char outBuffer[length];

			URM37V32_TestController controller;

			controller.InitOutputStream(outBuffer, length);
			controller.InitInputStream(inBuffer, length);

			// init response
			const unsigned char Command = 0x44;

			inBuffer[0] = Command;
			inBuffer[1] = 0x02;
			inBuffer[2] = 0xbb;
			inBuffer[3] = CalcChecksum(inBuffer[0], inBuffer[1], inBuffer[2]);
			
			controller.SetPassiveControlMode();

			for(int i = 0; i < length; i++)
			{
				Assert::AreEqual(inBuffer[i], outBuffer[i]);
			}
		}
	};
}
