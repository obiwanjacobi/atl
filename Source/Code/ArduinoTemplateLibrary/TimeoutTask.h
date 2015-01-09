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

#ifndef __TIMEOUTTASK_H__
#define __TIMEOUTTASK_H__

#include "Task.h"

namespace ATL {
namespace Process {

/*
	Calls the BaseT::OnTimeout when the Timeout has expired.
	Call the Execute method repeatedly.

	BaseT is used as a base class and implements:
		void OnTimeout();

	The DelaysT is a Delays<> type used to keep track of time.
	The Timeout is specified in the same quantity as the DelaysT is specified (Milli- or MicroSeconds).
*/
template<class BaseT, typename DelaysT, const int Timeout>
class TimeoutTask : public BaseT
{
public:
	TimeoutTask()
		: _task(0)
	{}

	Task_Begin(Execute)
	{
		while(true)
		{
			Task_YieldUntil(DelaysT::Wait((unsigned int)this, Timeout));
			BaseT::OnTimeout();
		}
	}
	Task_End

private:
	int _task;
};

}} // ATL::Process

#endif //__TIMEOUTTASK_H__