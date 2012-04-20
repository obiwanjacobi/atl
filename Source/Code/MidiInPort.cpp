#include "MidiInPort.h"

MidiInPort::MidiInPort()
{
#if USE_CALLBACKS
	
	// Initialise callbacks to NULL pointer
	mNoteOffCallback				= NULL;
	mNoteOnCallback					= NULL;
	mAfterTouchPolyCallback			= NULL;
	mControlChangeCallback			= NULL;
	mProgramChangeCallback			= NULL;
	mAfterTouchChannelCallback		= NULL;
	mPitchBendCallback				= NULL;
	mSystemExclusiveCallback		= NULL;
	mTimeCodeQuarterFrameCallback	= NULL;
	mSongPositionCallback			= NULL;
	mSongSelectCallback				= NULL;
	mTuneRequestCallback			= NULL;
	mClockCallback					= NULL;
	mStartCallback					= NULL;
	mContinueCallback				= NULL;
	mStopCallback					= NULL;
	mActiveSensingCallback			= NULL;
	mSystemResetCallback			= NULL;
	
#endif
}

/*! \brief Call the begin method in the setup() function of the Arduino.
 
 All parameters are set to their default values:
 - Input channel set to 1 if no value is specified
 - Full thru mirroring
 */
void MidiInPort::begin(const byte inChannel)
{
	
	// Initialise the Serial port
	USE_SERIAL_PORT.begin(MIDI_BAUDRATE);
		
	mInputChannel = inChannel;
	mRunningStatus_RX = InvalidType;
	mPendingMessageIndex = 0;
	mPendingMessageExpectedLenght = 0;
	
	mMessage.valid = false;
	mMessage.type = InvalidType;
	mMessage.channel = 0;
	mMessage.data1 = 0;
	mMessage.data2 = 0;
		
}

/*! \brief Read a MIDI message from the serial port using the main input channel (see setInputChannel() for reference).
 
 Returned value: true if any valid message has been stored in the structure, false if not.
 A valid message is a message that matches the input channel. \n\n
 If the Thru is enabled and the messages matches the filter, it is sent back on the MIDI output.
 */
bool MidiInPort::read()
{
	
	return read(mInputChannel);
	
}


/*! \brief Reading/thru-ing method, the same as read() with a given input channel to read on. */
bool MidiInPort::read(const byte inChannel)
{
	
	if (inChannel >= MIDI_CHANNEL_OFF) return false; // MIDI Input disabled.
	
	if (parse(inChannel)) {
		
		if (input_filter(inChannel)) {
			
//#if (COMPILE_MIDI_OUT && COMPILE_MIDI_THRU)
//			thru_filter(inChannel);
//#endif
			
#if USE_CALLBACKS
			launchCallback();
#endif
			
			return true;
		}
		
	}
	
	return false;
	
}


// Private method: MIDI parser
bool MidiInPort::parse(byte inChannel)
{ 
	
	const int bytes_available = USE_SERIAL_PORT.available();
	
	if (bytes_available <= 0) {
		// No data available.
		return false;
	}
	
	// If the buffer is full -> Don't Panic! Call the Vogons to destroy it.
	// MJ: Changed condition from == to >=
	if (bytes_available >= 128) {
		USE_SERIAL_PORT.flush();
	}	
	else {
		
		/* Parsing algorithm:
		 Get a byte from the serial buffer.
		 * If there is no pending message to be recomposed, start a new one.
		 - Find type and channel (if pertinent)
		 - Look for other bytes in buffer, call parser recursively, until the message is assembled or the buffer is empty.
		 * Else, add the extracted byte to the pending message, and check validity. When the message is done, store it.
		 */
		
		
		const byte extracted = USE_SERIAL_PORT.read();
		
		if (mPendingMessageIndex == 0) { // Start a new pending message
			mPendingMessage[0] = extracted;
			
			// Check for running status first
			switch (getTypeFromStatusByte(mRunningStatus_RX)) {
					// Only these types allow Running Status:
				case NoteOff:
				case NoteOn:
				case AfterTouchPoly:
				case ControlChange:
				case ProgramChange:
				case AfterTouchChannel:
				case PitchBend:	
					
					// If the status byte is not received, prepend it to the pending message
					if (extracted < 0x80) {
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
			
			
			switch (getTypeFromStatusByte(mPendingMessage[0])) {
					
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
		else { 
			
			// First, test if this is a status byte
			if (extracted >= 0x80) {
				
				// Reception of status bytes in the middle of an uncompleted message
				// are allowed only for interleaved Real Time message or EOX
				switch (extracted) {
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
						if (getTypeFromStatusByte(mPendingMessage[0]) == SystemExclusive) {
							
							// Store System Exclusive array in midimsg structure
							for (byte i=0;i<MIDI_SYSEX_ARRAY_SIZE;i++) {
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
						else {
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
			if (mPendingMessageIndex >= (mPendingMessageExpectedLenght-1)) {
				
				// "FML" case: fall down here with an overflown SysEx..
				// This means we received the last possible data byte that can fit the buffer.
				// If this happens, try increasing MIDI_SYSEX_ARRAY_SIZE.
				if (getTypeFromStatusByte(mPendingMessage[0]) == SystemExclusive) {
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
				switch (mMessage.type) {
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


// Private method: check if the received message is on the listened channel
bool MidiInPort::input_filter(byte inChannel)
{
	
	
	// This method handles recognition of channel (to know if the message is destinated to the Arduino)
	
	
	if (mMessage.type == InvalidType) return false;
	
	
	// First, check if the received message is Channel
	if (mMessage.type >= NoteOff && mMessage.type <= PitchBend) {
		
		// Then we need to know if we listen to it
		if ((mMessage.channel == mInputChannel) || (mInputChannel == MIDI_CHANNEL_OMNI)) {
			return true;
			
		}
		else {
			// We don't listen to this channel
			return false;
		}
		
	}
	else {
		
		// System messages are always received
		return true;
	}
	
}


// Private method: reset input attributes
void MidiInPort::reset_input_attributes()
{
	
	mPendingMessageIndex = 0;
	mPendingMessageExpectedLenght = 0;
	mRunningStatus_RX = InvalidType;
	
}


// Getters
/*! \brief Get the last received message's type
 
 Returns an enumerated type. @see kMIDIType
 */
kMIDIType MidiInPort::getType() const
{
	
	return mMessage.type;

}


/*! \brief Get the channel of the message stored in the structure.
 
 Channel range is 1 to 16. For non-channel messages, this will return 0.
 */
byte MidiInPort::getChannel() const
{
	
	return mMessage.channel;

}


/*! \brief Get the first data byte of the last received message. */
byte MidiInPort::getData1() const
{
	
	return mMessage.data1;

}


/*! \brief Get the second data byte of the last received message. */
byte MidiInPort::getData2() const
{ 
	
	return mMessage.data2;

}


/*! \brief Get the System Exclusive byte array. 
 
 @see getSysExArrayLength to get the array's length in bytes.
 */
const byte * MidiInPort::getSysExArray() const
{ 
	
	return mMessage.sysex_array;

}

/*! \brief Get the lenght of the System Exclusive array.
 
 It is coded using data1 as LSB and data2 as MSB.
 \return The array's length, in bytes.
 */
unsigned int MidiInPort::getSysExArrayLength() const
{
	
	unsigned int coded_size = ((unsigned int)(mMessage.data2) << 8) | mMessage.data1;
	
	return (coded_size > MIDI_SYSEX_ARRAY_SIZE) ? MIDI_SYSEX_ARRAY_SIZE : coded_size;
	
}


/*! \brief Check if a valid message is stored in the structure. */
bool MidiInPort::check() const
{ 
	
	return mMessage.valid;

}


// Setters
/*! \brief Set the value for the input MIDI channel 
 \param Channel the channel value. Valid values are 1 to 16, 
 MIDI_CHANNEL_OMNI if you want to listen to all channels, and MIDI_CHANNEL_OFF to disable MIDI input.
 */
void MidiInPort::setInputChannel(const byte Channel)
{ 
	
	mInputChannel = Channel;
	
}


#if USE_CALLBACKS

/*! \brief Detach an external function from the given type.
 
 Use this method to cancel the effects of setHandle********.
 \param Type		The type of message to unbind. When a message of this type is received, no function will be called.
 */
void MidiInPort::disconnectCallbackFromType(kMIDIType Type)
{
	
	switch (Type) {
		case NoteOff:               mNoteOffCallback = NULL;                break;
		case NoteOn:                mNoteOnCallback = NULL;                 break;
		case AfterTouchPoly:        mAfterTouchPolyCallback = NULL;         break;
		case ControlChange:         mControlChangeCallback = NULL;          break;
		case ProgramChange:         mProgramChangeCallback = NULL;          break;
		case AfterTouchChannel:     mAfterTouchChannelCallback = NULL;      break;
		case PitchBend:             mPitchBendCallback = NULL;              break;
		case SystemExclusive:       mSystemExclusiveCallback = NULL;        break;
		case TimeCodeQuarterFrame:  mTimeCodeQuarterFrameCallback = NULL;   break;
		case SongPosition:          mSongPositionCallback = NULL;           break;
		case SongSelect:            mSongSelectCallback = NULL;             break;
		case TuneRequest:           mTuneRequestCallback = NULL;            break;
		case Clock:                 mClockCallback = NULL;                  break;
		case Start:                 mStartCallback = NULL;                  break;
		case Continue:              mContinueCallback = NULL;               break;
		case Stop:                  mStopCallback = NULL;                   break;
		case ActiveSensing:         mActiveSensingCallback = NULL;          break;
		case SystemReset:           mSystemResetCallback = NULL;            break;
		default:					mMessageCallback = NULL;				break;
	}
	
}


// Private - launch callback function based on received type.
void MidiInPort::launchCallback()
{
	// MJ: call generic message handler
	if (mMessageCallback != NULL) mMessageCallback(mMessage.type, mMessage.channel, mMessage.data1, mMessage.data2);

	// The order is mixed to allow frequent messages to trigger their callback faster.
	
	switch (mMessage.type) {
			// Notes
		case NoteOff:				if (mNoteOffCallback != NULL)				mNoteOffCallback(mMessage.channel,mMessage.data1,mMessage.data2);	break;
		case NoteOn:				if (mNoteOnCallback != NULL)				mNoteOnCallback(mMessage.channel,mMessage.data1,mMessage.data2);	break;
			
			// Real-time messages
		case Clock:					if (mClockCallback != NULL)					mClockCallback();			break;			
		case Start:					if (mStartCallback != NULL)					mStartCallback();			break;
		case Continue:				if (mContinueCallback != NULL)				mContinueCallback();		break;
		case Stop:					if (mStopCallback != NULL)					mStopCallback();			break;
		case ActiveSensing:			if (mActiveSensingCallback != NULL)			mActiveSensingCallback();	break;
			
			// Continuous controllers
		case ControlChange:			if (mControlChangeCallback != NULL)			mControlChangeCallback(mMessage.channel,mMessage.data1,mMessage.data2);	break;
		case PitchBend:				if (mPitchBendCallback != NULL)				mPitchBendCallback(mMessage.channel,(int)((mMessage.data1 & 0x7F) | ((mMessage.data2 & 0x7F)<< 7)) - 8192);	break; // TODO: check this
		case AfterTouchPoly:		if (mAfterTouchPolyCallback != NULL)		mAfterTouchPolyCallback(mMessage.channel,mMessage.data1,mMessage.data2);	break;
		case AfterTouchChannel:		if (mAfterTouchChannelCallback != NULL)		mAfterTouchChannelCallback(mMessage.channel,mMessage.data1);	break;
			
		case ProgramChange:			if (mProgramChangeCallback != NULL)			mProgramChangeCallback(mMessage.channel,mMessage.data1);	break;
		case SystemExclusive:		if (mSystemExclusiveCallback != NULL)		mSystemExclusiveCallback(mMessage.sysex_array,mMessage.data1);	break;
			
			// Occasional messages
		case TimeCodeQuarterFrame:	if (mTimeCodeQuarterFrameCallback != NULL)	mTimeCodeQuarterFrameCallback(mMessage.data1);	break;
		case SongPosition:			if (mSongPositionCallback != NULL)			mSongPositionCallback((mMessage.data1 & 0x7F) | ((mMessage.data2 & 0x7F)<< 7));	break;
		case SongSelect:			if (mSongSelectCallback != NULL)			mSongSelectCallback(mMessage.data1);	break;
		case TuneRequest:			if (mTuneRequestCallback != NULL)			mTuneRequestCallback();	break;
			
		case SystemReset:			if (mSystemResetCallback != NULL)			mSystemResetCallback();	break;
		case InvalidType:
		default:
			break;
	}
	
}


#endif // USE_CALLBACKS
