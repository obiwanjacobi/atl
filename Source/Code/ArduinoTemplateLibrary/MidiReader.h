#ifndef __MIDIREADER_H__
#define __MIDIREADER_H__

namespace ATL {
namespace Midi {

/*
	BaseT is used as a base class and implements:
		unsigned int [IO.Stream.]getLength();
		int [IO.InputStream.]Read();
		void [Midi.MidiReader.]OnMessage(MidiMessage*);
		void [Midi.MidiReader.]OnRealTime(Midi::MessageTypes);
		void [Midi.MidiReader.]OnSysEx(BaseT*);
*/
template<class BaseT>
class MidiReader : public BaseT
{
public:
	MidiReader()
	{
		_runningStatus = 0;
		ResetState();
	}

	// reads one byte from the buffer and returns.
	// Multiple events may be fired.
	bool Read()
	{
		const uint16_t availableBytes = BaseT::getLength();

		if (availableBytes > 0)
		{
			int midiByte = BaseT::Read();

			if (midiByte != -1)
			{
				return Dispatch((byte)midiByte);
			}
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
	byte _runningStatus;
	
	// TODO: both these fields can be merged to one. 
	//   Use a bitmask to check one or the other.

	// this is the type of midi byte that is expected next
	// although some midi messages can be interupted by realtime messages.
	MidiParseState	_parseState;
	// this is the type of midi byte that signals the end of a logical
	// midi message. Only used for multi byte midi messages and sysex.
	MidiParseState	_endState;

	inline void CallOnMessage()
	{
		BaseT::OnMessage(&_midiMsg);
	}

	inline void CallOnRealtime(byte midiStatus)
	{
		BaseT::OnRealtime((Midi::MessageTypes)midiStatus);
	}

	inline void CallOnSysEx()
	{
		// TODO: construct a sysex stream that still fires realtime callbacks
		BaseT::OnSysEx(this);
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
	bool Dispatch(byte midiByte)
	{
		bool success = false;

		Midi::MessageTypes status = Midi::GetMessageType(midiByte);

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
				if (Midi::IsRealtimeMessage(status))
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
			_parseState == NotSet)
		{
			if (Midi::IsChannelMessage(_midiMsg.MessageType))
			{
				_runningStatus = _midiMsg.MessageType | _midiMsg.Channel;
			}
			else
			{
				_runningStatus = 0;
			}

			if (_endState != EOX)
			{
			    CallOnMessage();
			}

			ResetState();
		}

		return success;
	}


	bool ProcessStatusByte(byte statusByte)
	{
		bool success = true;

		switch (Midi::GetMessageLength(statusByte))
		{
			// 1 byte messages
			case 1:
				CallOnRealtime(statusByte);
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
				_runningStatus = 0;
				_parseState = SOX;
				_endState = EOX;
				CallOnSysEx();
				break;

			default:
				_runningStatus = 0;
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
			_midiMsg.SetDataByte1(midiByte);
			_parseState = (_parseState != _endState) ? DataByte2 : NotSet;
			break;
		
		case DataByte2:
			_midiMsg.SetDataByte2(midiByte);
			_parseState = NotSet;
			break;

		default:
			success = false;
			break;
		}

		return success;
	}
};

}} // ATL.Midi

#endif //__MIDIREADER_H__