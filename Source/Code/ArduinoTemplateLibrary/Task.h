#ifndef __TASK_H__
#define __TASK_H__

namespace ATL {

/*
This code was taken from http://msdn.microsoft.com/en-us/magazine/jj553509.aspx
It seems a lightweight way to implement cooperative multitasking.

Example code:

struct AverageArgs
{
  int * source;
  int sum;
  int count;
  int average;
  int _task;	// mandatory field in all arg structs
};

A Task's state is completely stored in the args struct (passed by ref).
Do not use local vars (they may generate compiler errors).

Task_Begin(Average, AverageArgs& args)
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
*/

#define Task_Begin(name, parameter) \
                                \
bool name(parameter)              \
{                                 \
	bool _yield_ = false;            \
	switch (args._task)             \
	{                               \
		case 0:


#define Task_End                    \
                                \
	}                               \
	args._task = 0;                 \
	return false;                   \
}


#define Task_WaitUntil(expression)      \
                                        \
args._task = __LINE__; case __LINE__:  \
if (!(expression))                     \
{                                      \
	return true;                         \
}


#define Task_Return()                    \
                                         \
  args._task = 0;                        \
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
  args._task = __LINE__; case __LINE__:  \
  if (_yield_ || !(expression))           \
  {                                      \
    return true;                         \
  }


#define Task_Yield()                     \
                                         \
  Task_YieldUntil(true)

} // ATL

#endif //__TASK_H__