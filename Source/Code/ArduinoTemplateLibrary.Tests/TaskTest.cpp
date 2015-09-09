#include "stdafx.h"
#include "Arduino.h"
#include "..\ArduinoTemplateLibrary\Task.h"
#include "..\ArduinoTemplateLibrary\Time.h"

using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ATL;

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

		[TestMethod]
		void MultipleCountingTasksTest()
		{
			CountingTask task1(5);
			CountingTask task2(7);
			CountingTask task3(3);
			CountingTask task4(15);
			
			bool running1 = true;
			bool running2 = true;
			bool running3 = true;
			bool running4 = true;

			while (true)
			{
				if (running1) running1 = task1.Execute();
				if (running2) running2 = task2.Execute();
				if (running3) running3 = task3.Execute();
				if (running4) running4 = task4.Execute();

				if (!running1 && !running2 && !running3 && !running4) break;
			};

			Assert::AreEqual(task1.LoopEnd, task1.LoopCount);
			Assert::AreEqual(task2.LoopEnd, task2.LoopCount);
			Assert::AreEqual(task3.LoopEnd, task3.LoopCount);
			Assert::AreEqual(task4.LoopEnd, task4.LoopCount);
		}
	};
}
