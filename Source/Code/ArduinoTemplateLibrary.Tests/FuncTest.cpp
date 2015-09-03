#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\Func.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace ArduinoTemplateLibraryTests
{
	class TestClass
	{
	public:
		static const int MagicNumber = 42;

		static void StaticVoidReturnVoidParam()
		{}

		static void StaticVoidReturnIntParam(int value)
		{
			Assert::AreEqual(MagicNumber, value);
		}

		static int StaticIntReturnVoidParam()
		{
			return MagicNumber;
		}

		static int StaticIntReturnIntParam(int value)
		{
			return value;
		}
	};

	[TestClass]
	public ref class FuncTest
	{
	public: 
		[TestMethod]
		void Func0()
		{
			ATL::Func0<&TestClass::StaticVoidReturnVoidParam> target;

			target.Invoke();
		}

		[TestMethod]
		void Func01()
		{
			ATL::Func01<int, &TestClass::StaticVoidReturnIntParam> target;

			target.Invoke(TestClass::MagicNumber);
		}

		[TestMethod]
		void Func()
		{
			ATL::Func<int, &TestClass::StaticIntReturnVoidParam> target;

			int returnValue = target.Invoke();

			Assert::AreEqual(TestClass::MagicNumber, returnValue);
		}

		[TestMethod]
		void Func1()
		{
			ATL::Func1<int, int, &TestClass::StaticIntReturnIntParam> target;

			int returnValue = target.Invoke(TestClass::MagicNumber);

			Assert::AreEqual(TestClass::MagicNumber, returnValue);
		}
	};
}
