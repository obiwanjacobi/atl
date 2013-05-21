#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\StreamOutputStream.h"
#include "TestOutputStream.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL::IO;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class StreamOutputStreamTest
	{
	public: 
		[TestMethod]
		void AttachStream_getLength_ReportsCorrectLength()
		{
			TestOutputStream stream;
			unsigned char buffer[] = { 0x00, 0x00, 0x00, 0x00 };
			stream.InitStream(buffer, 4);
			StreamOutputStream<TestOutputStream> target(&stream);

			// buffer is still empty, so length is zero.
			Assert::AreEqual(0, (int)target.getLength());
		}

		[TestMethod]
		void AttachStream_Write_DataIntoBuffer()
		{
			TestOutputStream stream;
			unsigned char buffer[] = { 0x00, 0x00, 0x00, 0x00 };
			stream.InitStream(buffer, 4);
			StreamOutputStream<TestOutputStream> target(&stream);

			target.Write(0xFF);
			target.Write(0xF0);

			// no length on arduino output streams.
			//Assert::AreEqual(2, (int)target.getLength());

			Assert::AreEqual((unsigned char)0xFF, buffer[0]);
			Assert::AreEqual((unsigned char)0xF0, buffer[1]);
		}
	};
}
