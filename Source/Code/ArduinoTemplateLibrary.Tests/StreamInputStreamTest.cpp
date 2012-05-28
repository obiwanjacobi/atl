#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\StreamInputStream.h"
#include "TestInputStream.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class StreamInputStreamTest
	{
	public: 
		[TestMethod]
		void AttachStream_getLength_ReportsCorrectLength()
		{
			TestInputStream stream;
			unsigned char buffer[] = { 0x00, 0x00, 0x00, 0x00 };
			stream.InitStream(buffer, 4);
			StreamInputStream<TestInputStream> target(&stream);

			Assert::AreEqual(4, (int)target.getLength());
		}

		[TestMethod]
		void AttachStream_Clear_RemovesAllData()
		{
			TestInputStream stream;
			unsigned char buffer[] = { 0x00, 0x00, 0x00, 0x00 };
			stream.InitStream(buffer, 4);
			StreamInputStream<TestInputStream> target(&stream);

			target.Clear();

			Assert::AreEqual(0, (int)target.getLength());
			Assert::AreEqual(-1, target.Read());
		}

		[TestMethod]
		void AttachStream_Read_ReturnsCorrectData()
		{
			TestInputStream stream;
			unsigned char buffer[] = { 0x00, 0x01, 0x02, 0x03 };
			stream.InitStream(buffer, 4);
			StreamInputStream<TestInputStream> target(&stream);

			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(i, target.Read());
			}

			Assert::AreEqual(0, (int)target.getLength());
			Assert::AreEqual(-1, target.Read());
		}
	};
}