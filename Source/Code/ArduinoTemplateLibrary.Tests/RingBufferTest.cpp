#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\RingBuffer.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace ArduinoTemplateLibraryTests
{
	[TestClass]
	public ref class RingBufferTest
	{
	private:
		TestContext^ testContextInstance;

	public: 
		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		[TestMethod]
		void InitWithData_getLength_Test()
		{
			const unsigned int size = 256;
			RingBuffer<unsigned char, size> target;

			for (int i = 0; i < size - 1; i++)
			{
				Assert::IsTrue(target.Put(i));
			}

			Assert::AreEqual(size - 1, target.getLength());
		}

		[TestMethod]
		void InitWithData_ProtectAgainstOverrun_Test()
		{
			const unsigned int size = 256;
			RingBuffer<unsigned char, size> target;

			for (int i = 0; i < size - 1; i++)
			{
				Assert::IsTrue(target.Put(i));
			}

			Assert::IsFalse(target.Put(0xFF));
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
				Assert::IsTrue(target.Put(i));

				// read
				Assert::AreEqual((unsigned char)i, target.Get());
			}

			for (int i = 0; i < size - 1; i++)
			{
				Assert::IsTrue(target.Put(i));
			}

			Assert::IsFalse(target.Put(0xFF));
		}

		[TestMethod]
		void InitWithData_Get_Test()
		{
			const int size = 256;
			RingBuffer<unsigned char, size> target;

			// write
			for (int i = 0; i < size - 1; i++)
			{
				Assert::IsTrue(target.Put(i));
			}

			// read
			for (int i = 0; i < size - 1; i++)
			{
				Assert::AreEqual((unsigned char)i, target.Get());
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
				Assert::IsTrue(target.Put(i));

				// read
				Assert::AreEqual((unsigned char)i, target.Get());
			}
		}
	};
}
