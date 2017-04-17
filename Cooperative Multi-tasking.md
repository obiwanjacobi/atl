# Cooperative Multi-tasking

ATL comes with a multi-tasking solution that is very light weight and simple but does the job. Important to remember is that is it a cooperative multi-tasking solution and not a preemptive multi-threading solution. The difference is that a cooperative solution requires your Tasks to be aware that there are other tasks that need to be executed also, where as a preemptive multi-threading solution forces the switch from one thread (task) to the other.

Out of the box the macros in Task.h utilize a C++ trick that involves jumping in and out of a switch statement. The mandatory {{ unsigned int _task }} var keeps track of the state the task is in and makes it possible to resume the task where it left of when it yielded execution.

Typically a Task is a dedicated class that implements one Task method (macro) and has the mandatory {{ int _task }} (private) member variable.

{{
class MyTask
{
public:

	Task_Begin(Execute)
	{
		while (true)
		{
			Task_YieldUntil(/* some condition */);

			// perform operation
		}
	}
	Task_End

private:
	unsigned int _task;
};
}}

The Task_Begin and Task_End macro's define the (Execute) method that is Task-method. The method uses the {{ unsigned int _task }} private variable. You can see the endless {{ while(true) }} loop in the method's body which would normally hang your program. But because of the Task_YieldUntil macro it yields execution control back to the caller until {{ /* some condition */}} is met and the executes some task-specific operation.

The {{MyTask::Execute}} method must be called repeatedly -directly or indirectly- from the {{loop()}} method in the Sketch.

This way multiple Task classes can be combined and work together - without seriously hampering each other.


