#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\Func.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace ArduinoTemplateLibraryTests
{
	class TestClass
	{
	public:
		static void StaticVoidReturnVoidParam()
		{}

		static void StaticVoidReturnIntParam(int value)
		{
			Assert::AreEqual(42, value);
		}

		static int StaticIntReturnVoidParam()
		{
			return 42;
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

			target.Invoke(42);
		}

		[TestMethod]
		void Func()
		{
			ATL::Func<int, &TestClass::StaticIntReturnVoidParam> target;

			int returnValue = target.Invoke();

			Assert::AreEqual(42, returnValue);
		}

		[TestMethod]
		void Func1()
		{
			ATL::Func1<int, int, &TestClass::StaticIntReturnIntParam> target;

			int returnValue = target.Invoke(42);

			Assert::AreEqual(42, returnValue);
		}
	};
}
