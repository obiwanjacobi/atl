/*  
	Arduino Template Library http://atl.codeplex.com
	Written by Marc Jacobi
	Copyright 2012-2015 All Rights Reserved

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __TASK_H__
#define __TASK_H__

namespace ATL {
namespace Process {

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

  // A Task's state is completely stored in the Task class or passed in as an argument.
  // Do not use local vars in this method (they may generate compiler errors).
  Task_Begin(Average, args)
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


#define Task_BeginWithParams(name, parameters) \
                                \
bool name(parameters)              \
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

}} // ATL::Process

#endif //__TASK_H__