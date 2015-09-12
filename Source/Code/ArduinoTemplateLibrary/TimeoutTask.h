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

#include "Delays.h"
#include "Task.h"

namespace ATL {

/*
	Calls the BaseT::OnTimeout when the Timeout has expired.
	Call the Execute method repeatedly.

	BaseT is used as a base class and implements:
		void OnTimeout();
		uint16_t [IdentifiableObject] getId();

	The DelaysT is a Delays<> type used to keep track of time.
	The Timeout is specified in the same quantity as the DelaysT is specified (Milli- or MicroSeconds).
*/
template<class BaseT, typename DelaysT, const timeout_t Timeout>
class TimeoutTask : public BaseT
{
public:
	TimeoutTask()
		: _task(0)
	{}

	/*
		Call this method repeatedly from the main loop.
		Each time the Timeout expires the BaseT::OnTimeout() method is called.
	 */
	Task_Begin(Execute)
	{
		while(true)
		{
			Task_YieldUntil(DelaysT::Wait(BaseT::getId(), Timeout));
			BaseT::OnTimeout();
		}
	}
	Task_End

	/*
		Returns the Timeout template parameter.
	 */
	inline timeout_t getTimeout() const
	{
		return Timeout;
	}

private:
	uint16_t _task;
};

} // ATL

#endif //__TIMEOUTTASK_H__