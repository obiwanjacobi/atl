#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\BufferedInputStream.h"
#include "..\ArduinoTemplateLibrary\RingBuffer.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;
using namespace ATL::IO;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class BufferedInputStreamTest
	{
	public: 
		[TestMethod]
		void InitWithData_Read_ProducesBytes()
		{
			const int size = 256;
			BufferedInputStream<RingBuffer<unsigned char, size>> target;

			for (int i = 0; i < size / 2; i++)
			{
				Assert::IsTrue(target.Write(i));
			}

			for (int i = 0; i < size; i++)
			{
				int value = target.Read();

				if (value == -1)
				{
					Assert::AreEqual(size / 2, i);
					break;
				}

				Assert::AreEqual(i, value);
			}
		}
	};
}
