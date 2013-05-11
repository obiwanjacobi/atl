/*  
	Arduino Template Library http://atl.codeplex.com
	Written by Marc Jacobi
	Copyright 2012-2013 All Rights Reserved

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

#ifndef __DELAYS_H__
#define __DELAYS_H__

#include "Time.h"

namespace ATL {

#ifndef ATL_Delays_MaxItems
	#define ATL_Delays_MaxItems		8
#endif

template<TimeResolution resolution = Milliseconds>
class Delays
{
public:
	static unsigned int Update()
	{
		_delta = _time.Update();
		return _delta;
	}

	static bool IsWaiting(int id)
	{
		for(int i = 0; i < ATL_Delays_MaxItems; i++)
		{
			if (_ids[i] == id)
			{
				return true;
			}
		}

		return false;
	}

	static bool Wait(unsigned int id, unsigned int milliseconds)
	{
		int emptyIndex = -1;

		for(int i = 0; i < ATL_Delays_MaxItems; i++)
		{
			if (emptyIndex == -1 && _ids[i] == 0)
			{
				emptyIndex = i;
				continue;
			}

			if (_ids[i] == id)
			{
				if (_delta >= _delays[i])
				{
					_ids[i] = 0;
					return true;
				}

				_delays[i] -= _delta;
				return false;
			}
		}

		if (emptyIndex == -1)
		{
			for(int i = 0; i < ATL_Delays_MaxItems; i++)
			{
				if (_ids[i] == 0)
				{
					emptyIndex = i;

					break;
				}
			}
		}

		_ids[emptyIndex] = id;
		_delays[emptyIndex] = milliseconds;

		return false;
	}

	static Time<resolution>& getTime() { return _time; }

private:
	static Time<resolution> _time;
	static unsigned int _delta;
	static unsigned int _ids[ATL_Delays_MaxItems];
	static unsigned int _delays[ATL_Delays_MaxItems];

	// NOTE: You will get a compile error on ATL_Delays_MaxItems.
	// use: '#define ATL_Delays_MaxItems [count]' (just before the include) 
	// for the max number of delay slots to create.
};

template<TimeResolution resolution> Time<resolution> Delays<resolution>::_time;
template<TimeResolution resolution> unsigned int Delays<resolution>::_delta = 0;
template<TimeResolution resolution> unsigned int Delays<resolution>::_ids[] = {};
template<TimeResolution resolution> unsigned int Delays<resolution>::_delays[] = {};

} // ATL

#endif //__DELAYS_H__