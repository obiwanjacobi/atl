#include "stdafx.h"
#include "..\ArduinoTemplateLibrary\Task.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace ArduinoTemplateLibraryTests
{
	class CountingTask
	{
	public:
		CountingTask(int loops)
		{
			_task = 0;
			LoopCount = 0;
			LoopEnd = loops;
		}

		int LoopCount;
		int LoopEnd;

		Task_Begin(Execute)
		{
			Task_YieldUntil(Increment());

			System::Diagnostics::Trace::WriteLine("CountingTask is finished");
		}
		Task_End

	private:
		int _task;

		inline bool Increment()
		{
			return (++LoopCount == LoopEnd);
		}
	};

	[TestClass]
	public ref class TaskTest
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
		void CountingTaskTest()
		{
			CountingTask task(5);
			
			while (task.Execute())
			{
			};

			Assert::AreEqual(task.LoopEnd, task.LoopCount);
		}
	};
}
