#ifndef __MIDIWRITER_H__
#define __MIDIWRITER_H__

#include "Midi.h"

// BaseT implements void Write(byte)
template<class BaseT>
class MidiWriter : public BaseT
{
public:
	MidiWriter()
	{
		_runningStatus = 0;
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

private:
	byte _runningStatus;
};

#endif //__MIDIWRITER_H__