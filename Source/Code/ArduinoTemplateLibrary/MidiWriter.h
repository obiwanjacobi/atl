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

#ifndef __MIDIWRITER_H__
#define __MIDIWRITER_H__

#include "Midi.h"

namespace ATL {

/*
	BaseT is the base class that implements:
		void [IO.Stream.]Write(byte);
*/
template<class BaseT>
class MidiWriter : public BaseT
{
public:
	MidiWriter()
		: _runningStatus(0)
	{
	}

	void Write(MidiMessage* midiMsg)
	{
		int msgLength = Midi::GetMessageLength(midiMsg->MessageType);
		byte statusByte = midiMsg->GetStatusByte();

		if (Midi::IsChannelMessage(midiMsg->MessageType))
		{
			if (_runningStatus != statusByte)
			{
				_runningStatus = statusByte;
				BaseT::Write(statusByte);
			}
			else
			{
				// statusByte == _runningStatus
				// So no status byte is written.
			}
		}
		else
		{
			// System Common messages cancel the running status
			if (Midi::IsSystemCommonMessage(midiMsg->MessageType))
			{
				_runningStatus = 0;
			}

			BaseT::Write(statusByte);
		}

		if (msgLength > 1)
		{
			BaseT::Write(midiMsg->GetDataByte1());
		}

		if (msgLength > 2)
		{
			BaseT::Write(midiMsg->GetDataByte2());
		}
	}

	void Write(Midi::MessageTypes msgType)
	{
		BaseT::Write((byte)msgType);
	}

private:
	byte _runningStatus;
};

} // ATL

#endif //__MIDIWRITER_H__