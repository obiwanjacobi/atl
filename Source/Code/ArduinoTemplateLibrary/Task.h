/*
Arduino Template Library https://github.com/obiwanjacobi/atl
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

/** \file Task.h
 *  The Task implementation is based on macros forming a switch statement. 
 *  It is possible to jump in and out of switch-cases and together
 *  with a _task variable a Task can be 'resumed' at the correct
 *  position.
 *  Keep the logic inside the Task method simple for it can cause compile errors.
 *  Calling functions is no problem.
 *
 *  This code was taken from http://msdn.microsoft.com/en-us/magazine/jj553509.aspx
 *  It seems a lightweight way to implement cooperative multitasking.
 *  See Also TimeoutTask for an example.
 *  You MUST have an "uint16_t _task" (private) variable to store the task state (FSM).
 */

/** MACRO: Declare a 'Task' procedure 'name'.
 *  \return Returns an indication if the task has yielded (true) or simply exited (false).
 */
#define Task_Begin(name) \
                                \
bool name()              \
{                                 \
    bool _yield_ = false;            \
    switch (_task)             \
    {                               \
        case 0:

/** MACRO: Declare a 'Task' procedure 'name' with parameters.
 *  \return Returns an indication if the task has yielded (true) or simply exited (false).
 */
#define Task_BeginWithParams(name, parameters) \
                                \
bool name(parameters)              \
{                                 \
    bool _yield_ = false;            \
    switch (_task)             \
    {                               \
        case 0:


/** MACRO: Declare the end of the 'Task' procedure
 *  Exits the task procedure.
 */
#define Task_End                    \
                                \
    }                               \
    _task = 0;                 \
    return false;                   \
}


/** Asynchronously waits for the expression to become true.
 *  The expression is evaluated before the Task procedure is exited.
 */
#define Task_WaitUntil(expression)      \
                                        \
    _task = __LINE__; case __LINE__:  \
    if (!(expression))                     \
    {                                      \
        return true;                         \
    }


/** MACRO: Exits the Task procedure immediately.
 *  \return Returns false from the Task procedure.
 */
#define Task_Return()                    \
                                         \
    _task = 0;                        \
    return false;


/** MACRO: Yields from the Task procedure until the expression evaluates to true.
 *  The Task procedure is yielded (exited) first and on reentry is the expression evaluated.
 *  \return Returns true from the Task procedure.
 */
#define Task_YieldUntil(expression)     \
                                         \
    _yield_ = true;                         \
    _task = __LINE__; case __LINE__:  \
    if (_yield_ || !(expression))           \
    {                                      \
        return true;                         \
    }


/** MACRO: Yields from the Task procedure.
 *  The Task procedure is yielded (exited) first and on reentry is the procedure resumed.
 *  \return Returns true from the Task procedure.
 */
#define Task_Yield()                     \
                                         \
    Task_YieldUntil(true)

} // ATL

#endif //__TASK_H__