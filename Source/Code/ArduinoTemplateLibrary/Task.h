#ifndef __TASK_H__
#define __TASK_H__

namespace ATL {

/*
This code was taken from http://msdn.microsoft.com/en-us/magazine/jj553509.aspx
It seems a lightweight way to implement cooperative multitasking.

Example code:

class AverageTask
{
public:
  int * source;
  int sum;
  int count;
  int average;

  // A Task's state is completely stored in the Task class.
  // Do not use local vars in this method (they may generate compiler errors).
  Task_Begin(Average)
  {
    args.sum = 0;
    args.count = 0;
    args.average = 0;

    while (true)
    {
      args.sum += *args.source;
      ++args.count;
      args.average = args.sum / args.count;

      Task_Yield();
	}
  }
  Task_End

private:
  int _task;	// mandatory field in all tasks
};

*/

/*
  The Task implementation is based on macros forming a switch statement. 
  It is possible to jump in and out of switch-cases and together
  with a _task variable a Task can be 'resumed' at the correct
  position.

*/

#define Task_Begin(name) \
                                \
bool name()              \
{                                 \
	bool _yield_ = false;            \
	switch (_task)             \
	{                               \
		case 0:


#define Task_End                    \
                                \
	}                               \
	_task = 0;                 \
	return false;                   \
}


#define Task_WaitUntil(expression)      \
                                        \
_task = __LINE__; case __LINE__:  \
if (!(expression))                     \
{                                      \
	return true;                         \
}


#define Task_Return()                    \
                                         \
  _task = 0;                        \
  return false;


#define Task_WaitWhile(expression)      \
                                         \
  Task_WaitUntil(!(expression))


#define Task_WaitFor(name, parameter)   \
                                         \
  Task_WaitWhile(name(parameter))


#define Task_YieldUntil(expression)     \
                                         \
  _yield_ = true;                         \
  _task = __LINE__; case __LINE__:  \
  if (_yield_ || !(expression))           \
  {                                      \
    return true;                         \
  }


#define Task_Yield()                     \
                                         \
  Task_YieldUntil(true)

} // ATL

#endif //__TASK_H__