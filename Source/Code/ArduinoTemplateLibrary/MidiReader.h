#ifndef __MIDIREADER_H__
#define __MIDIREADER_H__

// BaseT is a MidiInputStream derived custom class 
// that implements the getLength, Read, OnMessage, OnRealTime and OnSysEx methods
template<class BaseT>
class MidiReader : BaseT
{
public:
	MidiReader()
	{
		_runningStatus = 0;
		ResetState();
	}

	// reads one byte from the buffer and returns.
	// Multiple events may be fired.
	bool MidiReader::Read()
	{
		const uint16_t availableBytes = getLength();

		if (availableBytes > 0)
		{
			const byte midiByte = (byte)base.Read();

			return Dispatch(midiByte);
		}

		return false;
	}

private:
	MidiMessage _midiMsg;

	enum MidiParseState
	{
		NotSet,
		StatusByte,
		DataByte1,
		DataByte2,
		SOX,
		EOX,
	};

	// Running status is when the next midi message has the same status 
	// as the previous midi message. This way status byte do not have to
	// be repeated when they are the same, saving some bandwidth.
	byte			_runningStatus;
	// this is the type of midi byte that is expected next
	// although some midi messages can be interupted by realtime messages.
	MidiParseState	_parseState;
	// this is the type of midi byte that signals the end of a logical
	// midi message. Only used for multi byte midi messages and sysex.
	MidiParseState	_endState;

	inline void CallOnMessage()
	{
		OnMessage(_midiMsg);
	}

	inline void CallOnRealtime(kMIDIType midiStatus)
	{
		OnRealtime(midiStatus);
	}

	inline void CallOnSysEx()
	{
		// TODO: construct a sysex stream that still fires realtime callbacks
		OnSysEx(this);
	}

	void ResetState()
	{
		_parseState = StatusByte;
		_endState = NotSet;
	}

	

	/*
		- get byte from buffer
		? if expect status byte
			? if check for running status
				- insert running status
				- process status byte
				- insert byte read
			! else process status byte
		! else
		? if status byte
			- proces status byte (must be real time -or eox?)
		- insert byte read
	*/
	bool MidiReader::Dispatch(byte midiByte)
	{
		bool success = false;

		byte status = getStatus(midiByte);

		if (_parseState == StatusByte)
		{
			// We expect a status byte, but read a non-status byte
			// But running status is valid, so we have the first two bytes.
			if (status == 0 && _runningStatus != 0)
			{
				success = ProcessStatusByte(_runningStatus);

				if (success)
				{
					success = ProcessDataByte(midiByte);
				}
			}
			else if (status > 0)
			{
				success = ProcessStatusByte(midiByte);
			}
			else
			{
				// read/sync error
			}
		}
		else if (_parseState == SOX)
		{
			// TODO: sysex
		}
		else
		{
			// we expect a non-status data byte, but we read a status byte
			// it must be a real-time status byte or it is an error.
			if (status > 0)
			{
				if (Midi.isRealTimeMessage(status))
				{
					success = ProcessStatusByte(midiByte);
				}
				else
				{
					// read/sync error
				}
			}
			else
			{
				success = ProcessDataByte(midiByte);
			}
		}

		if (success &&
			_parseState == _endState)
		{
			if (Midi.IsChannelMessage(_midiMsg.MessageType))
			{
				_runningStatus = _midiMsg.MessageType;
			}
			else
			{
				_runningStatus = InvalidType;
			}

			if (_endState != EOX)
			{
			    CallOnMessage();
			}
		}

		return success;
	}


	bool ProcessStatusByte(byte statusByte)
	{
		bool success = true;

		switch (Midi.getMessageLength(statusByte))
		{
			// 1 byte messages
			case 1:
				CallOnRealTime(statusByte);
				break;
			
			// 2 bytes messages
			case 2:
				_midiMsg.SetStatusByte(statusByte);
				_parseState = DataByte1;
				_endState = DataByte1;
				break;
			
			// 3 bytes messages
			case 3:
				_midiMsg.SetStatusByte(statusByte);
				_parseState = DataByte1;
				_endState = DataByte2;
				break;
			
			// special sysex case
			case -1:
				_runningStatus = InvalidType;
				_parseState = SOX;
				_endState = EOX;
				CallOnSysEx();
				break;

			default:
				_runningStatus = InvalidType;
				ResetState();
				success = false;
				break;
		}

		return success;
	}


	bool ProcessDataByte(byte midiByte)
	{
		bool success = true;

		switch(_parseState)
		{
		case DataByte1:
			_midiMsg.setDataByte1(midiByte);
			_parseState = (_parseState != _endState) ? MidiDataByte2 : NotSet;
			break;
		
		case DataByte2:
			_midiMsg.setDataByte2(midiByte);
			_parseState = NotSet;
			break;

		default:
			success = false;
			break;
		}

		return success;
	}
};

#endif //__MIDIREADER_H__