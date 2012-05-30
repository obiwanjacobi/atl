#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\Delegate.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

namespace ArduinoTemplateLibraryTests
{
	class TestClass
	{
	public:
		void ReturnVoidParamVoid()
		{}

		void ReturnVoidParamInt(int value)
		{}

		int ReturnIntParamVoid()
		{
			return 42;
		}

		int ReturnIntParamInt(int value)
		{
			return value;
		}
	};

	[TestClass]
	public ref class DelegateTest
	{
	public:
		[TestMethod]
		void Delegate0()
		{
			TestClass instance;
			ATL::Delegate0<TestClass, &TestClass::ReturnVoidParamVoid> target(&instance);

			target.Invoke();
		}

		[TestMethod]
		void Delegate01()
		{
			TestClass instance;
			ATL::Delegate01<TestClass, int, &TestClass::ReturnVoidParamInt> target(&instance);

			target.Invoke(42);
		}

		[TestMethod]
		void Delegate()
		{
			TestClass instance;
			ATL::Delegate<TestClass, int, &TestClass::ReturnIntParamVoid> target(&instance);

			int value = target.Invoke();

			Assert::AreEqual(42, value);
		}

		[TestMethod]
		void Delegate1()
		{
			TestClass instance;
			ATL::Delegate1<TestClass, int, int, &TestClass::ReturnIntParamInt> target(&instance);

			int value = target.Invoke(42);

			Assert::AreEqual(42, value);
		}
	};
}
