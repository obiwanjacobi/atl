#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\TextWriter.h"
#include "TestOutputStream.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL::IO;

namespace ArduinoTemplateLibraryTests
{
	typedef TextWriter<TestOutputStream> TestTextWriter;

	[TestClass]
	public ref class TextWriterTest
	{
	public: 
		[TestMethod]
		void Text_Write_ReportsCorrectLength()
		{
			unsigned char buffer[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

			TestTextWriter target;
			target.InitOutputStream(buffer, 7);

			target.Write("123456");

			Assert::AreEqual(6, (int)target.getLength());
		}

		[TestMethod]
		void Text_Write_DoesNotWriteTerminatingZero()
		{
			unsigned char buffer[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

			TestTextWriter target;
			target.InitOutputStream(buffer, 7);

			target.Write("123456");

			Assert::AreEqual((int)'6', (int)buffer[5]);
			Assert::AreEqual((int)0xFF, (int)buffer[6]);
		}

		[TestMethod]
		void PositiveInt_Write_ConvertsToText()
		{
			unsigned char buffer[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

			TestTextWriter target;
			target.InitOutputStream(buffer, 7);

			target.Write(123456);

			Assert::AreEqual(6, (int)target.getLength());
			Assert::AreEqual((int)'1', (int)buffer[0]);
			Assert::AreEqual((int)'2', (int)buffer[1]);
			Assert::AreEqual((int)'3', (int)buffer[2]);
			Assert::AreEqual((int)'4', (int)buffer[3]);
			Assert::AreEqual((int)'5', (int)buffer[4]);
			Assert::AreEqual((int)'6', (int)buffer[5]);
			Assert::AreEqual((int)0xFF, (int)buffer[6]);
		}

		[TestMethod]
		void NegativeInt_Write_ConvertsToText()
		{
			unsigned char buffer[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

			TestTextWriter target;
			target.InitOutputStream(buffer, 7);

			target.Write(-23456);

			Assert::AreEqual(6, (int)target.getLength());
			Assert::AreEqual((int)'-', (int)buffer[0]);
			Assert::AreEqual((int)'2', (int)buffer[1]);
			Assert::AreEqual((int)'3', (int)buffer[2]);
			Assert::AreEqual((int)'4', (int)buffer[3]);
			Assert::AreEqual((int)'5', (int)buffer[4]);
			Assert::AreEqual((int)'6', (int)buffer[5]);
			Assert::AreEqual((int)0xFF, (int)buffer[6]);
		}

		[TestMethod]
		void PositiveLong_Write_ConvertsToText()
		{
			unsigned char buffer[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

			TestTextWriter target;
			target.InitOutputStream(buffer, 7);

			target.Write(123456L);

			Assert::AreEqual(6, (int)target.getLength());
			Assert::AreEqual((int)'1', (int)buffer[0]);
			Assert::AreEqual((int)'2', (int)buffer[1]);
			Assert::AreEqual((int)'3', (int)buffer[2]);
			Assert::AreEqual((int)'4', (int)buffer[3]);
			Assert::AreEqual((int)'5', (int)buffer[4]);
			Assert::AreEqual((int)'6', (int)buffer[5]);
			Assert::AreEqual((int)0xFF, (int)buffer[6]);
		}

		[TestMethod]
		void NegativeLong_Write_ConvertsToText()
		{
			unsigned char buffer[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

			TestTextWriter target;
			target.InitOutputStream(buffer, 7);

			target.Write(-23456L);

			Assert::AreEqual(6, (int)target.getLength());
			Assert::AreEqual((int)'-', (int)buffer[0]);
			Assert::AreEqual((int)'2', (int)buffer[1]);
			Assert::AreEqual((int)'3', (int)buffer[2]);
			Assert::AreEqual((int)'4', (int)buffer[3]);
			Assert::AreEqual((int)'5', (int)buffer[4]);
			Assert::AreEqual((int)'6', (int)buffer[5]);
			Assert::AreEqual((int)0xFF, (int)buffer[6]);
		}

		[TestMethod]
		void PositiveDouble_Write_ConvertsToText()
		{
			unsigned char buffer[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

			TestTextWriter target;
			target.InitOutputStream(buffer, 7);

			target.Write(12.456);

			// rounded off to 2 decimal digits!
			Assert::AreEqual(5, (int)target.getLength());
			Assert::AreEqual((int)'1', (int)buffer[0]);
			Assert::AreEqual((int)'2', (int)buffer[1]);
			Assert::AreEqual((int)'.', (int)buffer[2]);
			Assert::AreEqual((int)'4', (int)buffer[3]);
			Assert::AreEqual((int)'6', (int)buffer[4]);
			Assert::AreEqual((int)0xFF, (int)buffer[5]);
		}

		[TestMethod]
		void NegativeDouble_Write_ConvertsToText()
		{
			unsigned char buffer[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

			TestTextWriter target;
			target.InitOutputStream(buffer, 7);

			target.Write(-23.56);

			Assert::AreEqual(6, (int)target.getLength());
			Assert::AreEqual((int)'-', (int)buffer[0]);
			Assert::AreEqual((int)'2', (int)buffer[1]);
			Assert::AreEqual((int)'3', (int)buffer[2]);
			Assert::AreEqual((int)'.', (int)buffer[3]);
			Assert::AreEqual((int)'5', (int)buffer[4]);
			Assert::AreEqual((int)'6', (int)buffer[5]);
			Assert::AreEqual((int)0xFF, (int)buffer[6]);
		}
	};
}
