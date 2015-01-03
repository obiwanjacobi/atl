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

#ifndef __DELAYS_H__
#define __DELAYS_H__

#include "Time.h"

namespace ATL {

/*
	TimeT implements: unsigned int [Time]Update() - returns the delta-Time.
*/
template<class TimeT, const unsigned char maxItems>
class Delays
{
public:
	static unsigned int Update()
	{
		_delta = _time.Update();
		return _delta;
	}

	static bool IsWaiting(unsigned int id)
	{
		for (int i = 0; i < maxItems; i++)
		{
			if (_ids[i] == id)
			{
				return true;
			}
		}

		return false;
	}

	static void Abort(unsigned int id)
	{
		for (int i = 0; i < maxItems; i++)
		{
			if (_ids[i] == id)
			{
				_delays[i] = 0;
			}
		}
	}

	static bool Wait(unsigned int id, unsigned int time)
	{
		int emptyIndex = -1;

		for (int i = 0; i < maxItems; i++)
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
			for (int i = 0; i < maxItems; i++)
			{
				if (_ids[i] == 0)
				{
					emptyIndex = i;

					break;
				}
			}
		}

		_ids[emptyIndex] = id;
		_delays[emptyIndex] = time;

		return false;
	}

	static void Clear(unsigned int id)
	{
		for (int i = 0; i < maxItems; i++)
		{
			if (_ids[i] == id)
			{
				_ids[i] = 0;
			}
		}
	}

	static TimeT& getTime() { return _time; }

private:
	static TimeT _time;
	static unsigned int _delta;
	static unsigned int _ids[maxItems];
	static unsigned int _delays[maxItems];
};

template<class TimeT, const unsigned char maxItems> TimeT Delays<TimeT, maxItems>::_time;
template<class TimeT, const unsigned char maxItems> unsigned int Delays<TimeT, maxItems>::_delta = 0;
template<class TimeT, const unsigned char maxItems> unsigned int Delays<TimeT, maxItems>::_ids[] = {};
template<class TimeT, const unsigned char maxItems> unsigned int Delays<TimeT, maxItems>::_delays[] = {};

} // ATL

#endif //__DELAYS_H__