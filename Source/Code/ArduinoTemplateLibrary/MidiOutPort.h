#ifndef __MIDIOUTPORT_H__
#define __MIDIOUTPORT_H__

#include "Midi.h"

#define USE_RUNNING_STATUS		1			// Running status enables short messages when sending multiple values
                                            // of the same type and channel.
                                            // Set to 0 if you have troubles with controlling you hardware.

class MidiOutPort
{
public:	
	MidiOutPort(Stream* output)
	{
		_output = output;
#if USE_RUNNING_STATUS
		mRunningStatus_TX = InvalidType;
#endif // USE_RUNNING_STATUS
	}

	void sendNoteOn(byte NoteNumber,byte Velocity,byte Channel);
	void sendNoteOff(byte NoteNumber,byte Velocity,byte Channel);
	void sendProgramChange(byte ProgramNumber,byte Channel);
	void sendControlChange(byte ControlNumber, byte ControlValue,byte Channel);
	void sendPitchBend(int PitchValue,byte Channel);
	void sendPitchBend(unsigned int PitchValue,byte Channel);
	void sendPitchBend(double PitchValue,byte Channel);
	void sendPolyPressure(byte NoteNumber,byte Pressure,byte Channel);
	void sendAfterTouch(byte Pressure,byte Channel);
	void sendSysEx(int length, const byte *const array,bool ArrayContainsBoundaries = false);	
	void sendTimeCodeQuarterFrame(byte TypeNibble, byte ValuesNibble);
	void sendTimeCodeQuarterFrame(byte data);
	void sendSongPosition(unsigned int Beats);
	void sendSongSelect(byte SongNumber);
	void sendTuneRequest();
	void sendRealTime(kMIDIType Type);
	
	void send(kMIDIType type, byte param1, byte param2, byte channel);

private:
	const byte genstatus(const kMIDIType inType,const byte inChannel) const;

	// Attributes
#if USE_RUNNING_STATUS
	byte			mRunningStatus_TX;
#endif // USE_RUNNING_STATUS

	Stream* _output;
};


#endif //__MIDIOUTPORT_H__
