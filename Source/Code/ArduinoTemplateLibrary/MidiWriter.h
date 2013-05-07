#ifndef __MIDIWRITER_H__
#define __MIDIWRITER_H__

#include "Midi.h"

namespace ATL {
namespace Midi {

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

}} // ATL.Midi

#endif //__MIDIWRITER_H__