#ifndef __MIDIINPORT_H__
#define __MIDIINPORT_H__

#include "Midi.h"

#define USE_CALLBACKS           1           // Set this to 1 if you want to use callback handlers (to bind your functions to the library).
                                            // To use the callbacks, you need to have COMPILE_MIDI_IN set to 1

#define USE_1BYTE_PARSING       1           // Each call to MIDI.read will only parse one byte (might be faster).

#define USE_SERIAL_PORT         Serial      // Change the number (to Serial1 for example) if you want
                                            // to use a different serial port for MIDI I/O.

/*! The midimsg structure contains decoded data of a MIDI message read from the serial port with read() or thru(). \n */
struct midimsg {
	/*! The MIDI channel on which the message was recieved. \n Value goes from 1 to 16. */
	byte channel; 
	/*! The type of the message (see the define section for types reference) */
	kMIDIType type;
	/*! The first data byte.\n Value goes from 0 to 127.\n */
	byte data1;
	/*! The second data byte. If the message is only 2 bytes long, this one is null.\n Value goes from 0 to 127. */
	byte data2;
	/*! System Exclusive dedicated byte array. \n Array length is stocked on 16 bits, in data1 (LSB) and data2 (MSB) */
	byte sysex_array[MIDI_SYSEX_ARRAY_SIZE];
	/*! This boolean indicates if the message is valid or not. There is no channel consideration here, validity means the message respects the MIDI norm. */
	bool valid;
};


class MidiInPort
{
public:
	MidiInPort();
	void begin(const byte inChannel = 1);

	bool read();
	bool read(const byte Channel);
	
	// Getters
	kMIDIType getType() const;
	byte getChannel() const;
	byte getData1() const;
	byte getData2() const;
	const byte * getSysExArray() const;
	unsigned int getSysExArrayLength() const;
	bool check() const;
	
	byte getInputChannel() const 
    {
        return mInputChannel;
    }
	
	// Setters
	void setInputChannel(const byte Channel);
	
	/*! \brief Extract an enumerated MIDI type from a status byte.
	 
	 This is a utility static method, used internally, made public so you can handle kMIDITypes more easily.
	 */
	static inline const kMIDIType getTypeFromStatusByte(const byte inStatus) 
    {
		if ((inStatus < 0x80) 
			|| (inStatus == 0xF4) 
			|| (inStatus == 0xF5) 
			|| (inStatus == 0xF9) 
			|| (inStatus == 0xFD)) return InvalidType; // data bytes and undefined.
		if (inStatus < 0xF0) return (kMIDIType)(inStatus & 0xF0);	// Channel message, remove channel nibble.
		else return (kMIDIType)inStatus;
	}
	
	
#if USE_CALLBACKS
	
	// MJ: added a generic callback handler
	void setHandleMessage(void (*fptr)(kMIDIType type, byte channel, byte data1, byte data2)) { mMessageCallback = fptr; }

	void setHandleNoteOff(void (*fptr)(byte channel, byte note, byte velocity))				{ mNoteOffCallback = fptr; }
	void setHandleNoteOn(void (*fptr)(byte channel, byte note, byte velocity))				{ mNoteOnCallback = fptr; }
	void setHandleAfterTouchPoly(void (*fptr)(byte channel, byte note, byte pressure))		{ mAfterTouchPolyCallback = fptr; }
	void setHandleControlChange(void (*fptr)(byte channel, byte number, byte value))		{ mControlChangeCallback = fptr; }
	void setHandleProgramChange(void (*fptr)(byte channel, byte number))					{ mProgramChangeCallback = fptr; }
	void setHandleAfterTouchChannel(void (*fptr)(byte channel, byte pressure))				{ mAfterTouchChannelCallback = fptr; }
	void setHandlePitchBend(void (*fptr)(byte channel, int bend))							{ mPitchBendCallback = fptr; }
	void setHandleSystemExclusive(void (*fptr)(byte * array, byte size))					{ mSystemExclusiveCallback = fptr; }
	void setHandleTimeCodeQuarterFrame(void (*fptr)(byte data))								{ mTimeCodeQuarterFrameCallback = fptr; }
	void setHandleSongPosition(void (*fptr)(unsigned int beats))							{ mSongPositionCallback = fptr; }
	void setHandleSongSelect(void (*fptr)(byte songnumber))									{ mSongSelectCallback = fptr; }
	void setHandleTuneRequest(void (*fptr)(void))											{ mTuneRequestCallback = fptr; }
	void setHandleClock(void (*fptr)(void))													{ mClockCallback = fptr; }
	void setHandleStart(void (*fptr)(void))													{ mStartCallback = fptr; }
	void setHandleContinue(void (*fptr)(void))												{ mContinueCallback = fptr; }
	void setHandleStop(void (*fptr)(void))													{ mStopCallback = fptr; }
	void setHandleActiveSensing(void (*fptr)(void))											{ mActiveSensingCallback = fptr; }
	void setHandleSystemReset(void (*fptr)(void))											{ mSystemResetCallback = fptr; }
	
	void disconnectCallbackFromType(kMIDIType Type);
	
#endif // USE_CALLBACKS
	
	
private:

	bool input_filter(byte inChannel);
	bool parse(byte inChannel);
	void reset_input_attributes();
	
	// Attributes
	byte			mRunningStatus_RX;
	byte			mInputChannel;
	
	byte			mPendingMessage[MIDI_SYSEX_ARRAY_SIZE];
	unsigned int	mPendingMessageExpectedLenght;
	unsigned int	mPendingMessageIndex;					// Extended to unsigned int for larger sysex payloads.
	
	midimsg			mMessage;
	
#if USE_CALLBACKS
	
	void launchCallback();
	
	void (*mMessageCallback)(kMIDIType type, byte channel, byte data1, byte data2); // MJ: generic message callback
	void (*mNoteOffCallback)(byte channel, byte note, byte velocity);
	void (*mNoteOnCallback)(byte channel, byte note, byte velocity);
	void (*mAfterTouchPolyCallback)(byte channel, byte note, byte velocity);
	void (*mControlChangeCallback)(byte channel, byte, byte);
	void (*mProgramChangeCallback)(byte channel, byte);
	void (*mAfterTouchChannelCallback)(byte channel, byte);
	void (*mPitchBendCallback)(byte channel, int);
	void (*mSystemExclusiveCallback)(byte * array, byte size);
	void (*mTimeCodeQuarterFrameCallback)(byte data);
	void (*mSongPositionCallback)(unsigned int beats);
	void (*mSongSelectCallback)(byte songnumber);
	void (*mTuneRequestCallback)(void);
	void (*mClockCallback)(void);
	void (*mStartCallback)(void);
	void (*mContinueCallback)(void);
	void (*mStopCallback)(void);
	void (*mActiveSensingCallback)(void);
	void (*mSystemResetCallback)(void);
	
#endif // USE_CALLBACKS
	
};


#endif //__MIDIINPORT_H__
