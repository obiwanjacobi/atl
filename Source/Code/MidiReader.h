#ifndef __MIDIREADER_H__
#define __MIDIREADER_H__

// BaseT is a MidiInputStream derived custom class 
// that implements the OnMessage, OnRealTime and OnSysEx methods
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
	// Multiple callbacks/events may be fired.
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
	bool MidiReader::Dispatch(const byte midiByte)
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

		return success;
	}


	bool ProcessStatusByte(const byte statusByte)
	{
		bool success = true;

		switch (Midi.getMessageLength(statusByte))
		{
			// 1 byte messages
			case 1:
				CallOnRealTime(statusByte);
				ResetState();
				break;
			
			// 2 bytes messages
			case 2:
				_midiMsg.setStatusByte(statusByte);
				_parseState = DataByte1;
				_endState = DataByte1;
				break;
			
			// 3 bytes messages
			case 3:
				_midiMsg.setStatusByte(statusByte);
				_parseState = DataByte1;
				_endState = DataByte2;
				break;
			
			// special sysex case
			case -1:
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


	bool ProcessDataByte(const byte midiByte)
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

	


	bool MidiInPort::parse(byte inChannel)
	{ 
		//const int bytes_available = USE_SERIAL_PORT.available();
		const int bytes_available = getLength();

		if (bytes_available <= 0)
		{
			// No data available.
			return false;
		}
	
		// If the buffer is full -> Don't Panic! Call the Vogons to destroy it.
		// MJ: Changed condition from == to >=
		if (bytes_available >= 128)
		{
			//USE_SERIAL_PORT.flush();	// MJ: isn't this for writing into buffers??
			Clear();
		}	
		else
		{
			/* Parsing algorithm:
			 Get a byte from the serial buffer.
			 * If there is no pending message to be recomposed, start a new one.
			 - Find type and channel (if pertinent)
			 - Look for other bytes in buffer, call parser recursively, until the message is assembled or the buffer is empty.
			 * Else, add the extracted byte to the pending message, and check validity. When the message is done, store it.
			 */
		
			

			//const byte extracted = USE_SERIAL_PORT.read();
			
		
			if (mPendingMessageIndex == 0)
			{ // Start a new pending message
				mPendingMessage[0] = extracted;
			
				// Check for running status first
				switch (getTypeFromStatusByte(mRunningStatus_RX))
				{
						// Only these types allow Running Status:
					case NoteOff:
					case NoteOn:
					case AfterTouchPoly:
					case ControlChange:
					case ProgramChange:
					case AfterTouchChannel:
					case PitchBend:	
					
						// If the status byte is not received, prepend it to the pending message
						if (extracted < 0x80)
						{
							mPendingMessage[0] = mRunningStatus_RX;
							mPendingMessage[1] = extracted;
							mPendingMessageIndex = 1;
						}
						// Else: well, we received another status byte, so the running status does not apply here.
						// It will be updated upon completion of this message.
					
						break;
					
					default:
						// No running status
						break;
				}
			
			
				switch (getTypeFromStatusByte(mPendingMessage[0]))
				{
					
						// 1 byte messages
					case Start:
					case Continue:
					case Stop:
					case Clock:
					case ActiveSensing:
					case SystemReset:
					case TuneRequest:
						// Handle the message type directly here.
						mMessage.type = getTypeFromStatusByte(mPendingMessage[0]);
						mMessage.channel = 0;
						mMessage.data1 = 0;
						mMessage.data2 = 0;
						mMessage.valid = true;
					
						// \fix Running Status broken when receiving Clock messages.
						// Do not reset all input attributes, Running Status must remain unchanged.
						//reset_input_attributes(); 
					
						// We still need to reset these
						mPendingMessageIndex = 0;
						mPendingMessageExpectedLenght = 0;
					
						return true;
						break;
					
						// 2 bytes messages
					case ProgramChange:
					case AfterTouchChannel:
					case TimeCodeQuarterFrame:
					case SongSelect:
						mPendingMessageExpectedLenght = 2;
						break;
					
						// 3 bytes messages
					case NoteOn:
					case NoteOff:
					case ControlChange:
					case PitchBend:
					case AfterTouchPoly:
					case SongPosition:
						mPendingMessageExpectedLenght = 3;
						break;
					
					case SystemExclusive:
						mPendingMessageExpectedLenght = MIDI_SYSEX_ARRAY_SIZE; // As the message can be any lenght between 3 and MIDI_SYSEX_ARRAY_SIZE bytes
						mRunningStatus_RX = InvalidType;
						break;
					
					case InvalidType:
					default:
						// This is obviously wrong. Let's get the hell out'a here.
						reset_input_attributes();
						return false;
						break;
				}
			
				// Then update the index of the pending message.
				mPendingMessageIndex++;
			
	#if USE_1BYTE_PARSING
				// Message is not complete.
				return false;
	#else
				// Call the parser recursively
				// to parse the rest of the message.
				return parse(inChannel);
	#endif
			
			}
			else
			{ 
			
				// First, test if this is a status byte
				if (extracted >= 0x80)
				{
				
					// Reception of status bytes in the middle of an uncompleted message
					// are allowed only for interleaved Real Time message or EOX
					switch (extracted)
					{
						case Clock:
						case Start:
						case Continue:
						case Stop:
						case ActiveSensing:
						case SystemReset:
						
							/*
							 This is tricky. Here we will have to extract the one-byte message,
							 pass it to the structure for being read outside the MIDI class,
							 and recompose the message it was interleaved into.
						 
							 Oh, and without killing the running status.. 
						 
							 This is done by leaving the pending message as is, it will be completed on next calls.
							 */
						
							mMessage.type = (kMIDIType)extracted;
							mMessage.data1 = 0;
							mMessage.data2 = 0;
							mMessage.channel = 0;
							mMessage.valid = true;
							return true;
						
							break;
						
							// End of Exclusive
						case 0xF7:
							if (getTypeFromStatusByte(mPendingMessage[0]) == SystemExclusive)
							{
							
								// Store System Exclusive array in midimsg structure
								for (byte i=0;i<MIDI_SYSEX_ARRAY_SIZE;i++)
								{
									mMessage.sysex_array[i] = mPendingMessage[i];
								}
							
								mMessage.type = SystemExclusive;

								// Get length
								mMessage.data1 = (mPendingMessageIndex+1) & 0xFF;	
								mMessage.data2 = (mPendingMessageIndex+1) >> 8;
							
								mMessage.channel = 0;
								mMessage.valid = true;
							
								reset_input_attributes();
							
								return true;
							}
							else
							{
								// Well well well.. error.
								reset_input_attributes();
								return false;
							}
						
							break;
						default:
							break;
					}
				}
			
			
				// Add extracted data byte to pending message
				mPendingMessage[mPendingMessageIndex] = extracted;
			
			
				// Now we are going to check if we have reached the end of the message
				if (mPendingMessageIndex >= (mPendingMessageExpectedLenght-1))
				{
				
					// "FML" case: fall down here with an overflown SysEx..
					// This means we received the last possible data byte that can fit the buffer.
					// If this happens, try increasing MIDI_SYSEX_ARRAY_SIZE.
					if (getTypeFromStatusByte(mPendingMessage[0]) == SystemExclusive)
					{
						reset_input_attributes();
						return false;
					}
				
				
					mMessage.type = getTypeFromStatusByte(mPendingMessage[0]);
					mMessage.channel = (mPendingMessage[0] & 0x0F)+1; // Don't check if it is a Channel Message
				
					mMessage.data1 = mPendingMessage[1];
				
					// Save data2 only if applicable
					if (mPendingMessageExpectedLenght == 3)	mMessage.data2 = mPendingMessage[2];
					else mMessage.data2 = 0;
				
					// Reset local variables
					mPendingMessageIndex = 0;
					mPendingMessageExpectedLenght = 0;
				
					mMessage.valid = true;
				
					// Activate running status (if enabled for the received type)
					switch (mMessage.type)
					{
						case NoteOff:
						case NoteOn:
						case AfterTouchPoly:
						case ControlChange:
						case ProgramChange:
						case AfterTouchChannel:
						case PitchBend:	
							// Running status enabled: store it from received message
							mRunningStatus_RX = mPendingMessage[0];
							break;
						
						default:
							// No running status
							mRunningStatus_RX = InvalidType;
							break;
					}
					return true;
				}
				else {
					// Then update the index of the pending message.
					mPendingMessageIndex++;
				
	#if USE_1BYTE_PARSING
					// Message is not complete.
					return false;
	#else
					// Call the parser recursively
					// to parse the rest of the message.
					return parse(inChannel);
	#endif
				
				}
			
			}
		
		}
	
		// What are our chances to fall here?
		return false;
	}
};

#endif //__MIDIREADER_H__