#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\RingBuffer.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class RingBufferTest
	{
    public:
		[TestMethod]
		void InitWithData_getLength_Test()
		{
			const unsigned int size = 256;
			RingBuffer<unsigned char, size> target;

			for (int i = 0; i < size - 1; i++)
			{
				Assert::IsTrue(target.Write(i));
			}

			Assert::AreEqual((uint16_t)(size - 1), (uint16_t)target.getLength());
		}

		[TestMethod]
		void InitWithData_ProtectAgainstOverrun_Test()
		{
			const unsigned int size = 256;
			RingBuffer<unsigned char, size> target;

			for (int i = 0; i < size - 1; i++)
			{
				Assert::IsTrue(target.Write(i));
			}

			Assert::IsFalse(target.Write(0xFF));
		}

		[TestMethod]
		void InitWithData_ProtectAgainstOverrun_WithWrapAround_Test()
		{
			const int size = 256;
			RingBuffer<unsigned char, size> target;
			
			// move
			for (int i = 0; i < size * 2.5; i++)
			{
				// write
				Assert::IsTrue(target.Write(i));

				// read
				Assert::AreEqual((unsigned char)i, target.Read());
			}

			for (int i = 0; i < size - 1; i++)
			{
				Assert::IsTrue(target.Write(i));
			}

			Assert::IsFalse(target.Write(0xFF));
		}

		[TestMethod]
		void InitWithData_Read_Test()
		{
			const int size = 256;
			RingBuffer<unsigned char, size> target;

			// write
			for (int i = 0; i < size - 1; i++)
			{
				Assert::IsTrue(target.Write(i));
			}

			// read
			for (int i = 0; i < size - 1; i++)
			{
				Assert::AreEqual((unsigned char)i, target.Read());
			}
		}

		[TestMethod]
		void InitWithData_WrapAround_Test()
		{
			const int size = 256;
			RingBuffer<unsigned char, size> target;
			
			for (int i = 0; i < size * 2.5; i++)
			{
				// write
				Assert::IsTrue(target.Write(i));

				// read
				Assert::AreEqual((unsigned char)i, target.Read());
			}
		}
	};
}
