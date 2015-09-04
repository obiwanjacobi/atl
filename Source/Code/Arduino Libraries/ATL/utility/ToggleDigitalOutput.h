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

#ifndef __TOGGLEDIGITALOUTPUT_H__
#define __TOGGLEDIGITALOUTPUT_H__

namespace ATL {
namespace IO {

/*
	Maintains state to toggle a digital output pin.
	Can also be used as BaseT for the TimeoutTask (implements OnTimeout).

	BaseT is used as a base class and implements:
		void [IO::DigitalOutputPin] Write(bool);
*/
template<class BaseT>
class ToggleDigitalOutput : public BaseT
{
protected:
	ToggleDigitalOutput(bool initialState = false)
		: _state(initialState)
	{}

	// toggles the state and outputs the pin.
	inline void Toggle()
	{
		_state = !_state;
		BaseT::Write(_state);
	}

protected:

	// Can be used as a BaseT for TimeoutTask.
	inline void OnTimeout()
	{
		Toggle();
	}

private:
	bool _state;
};

}} // ATL::IO

#endif //__TOGGLEDIGITALOUTPUT_H__