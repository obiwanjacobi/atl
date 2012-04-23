#ifndef __MIDIMESSAGE_H__
#define __MIDIMESSAGE_H__

#include "Midi.h"

// Midi message struct for all midi messages
//  NoteOff	              channel, note, velocity
//	NoteOn                channel, note, velocity
//	AfterTouchPoly        channel, note, pressure
//	ControlChange         channel, number, value
//	ProgramChange         channel, number
//	AfterTouchChannel     channel, pressure
//	PitchBend             channel, bend
//	SystemExclusive       -
//	TimeCodeQuarterFrame  data
//	SongPosition          beats
//	SongSelect            songNumber
//	TuneRequest           -
//	Clock                 -
//	Start                 -
//	Continue              -
//	Stop                  -
//	ActiveSensing         -
//	SystemReset           -

struct MidiMessage
{
	// midi message type
	Midi.MessageTypes msgType;

	union
	{
		struct // channel messages
		{
			byte channel;

			union
			{
				struct
				{
					union
					{
						byte note;		// note number
						byte number;	// Program- and Control Change numbers
					};

					union
					{
						byte velocity;	// note
						byte value;		// Control Change values
						byte pressure;	// after touch
					};
				};

				int bend;	// pitch bend
			};
		};
			
		unsigned int beats;	// song position
		byte songNumber;	// song select
		byte data;			// time code
	};

	//byte reserved[3];		// filler to get to power of 2 struct size (8 bytes)

	void SetStatusByte(byte statusByte)
	{
		msgType = Midi.getMessageType(statusByte);
		// reset state
		bend = 0;
		beats = 0;

		// if it is NOT a system message, set the channel
		if (msgType < Midi.SystemExclusive)
		{
			channel = (statusByte & 0x0F);
		}
	}

	void SetDataByte1(byte dataByte)
	{
		switch(msgType)
		{
			case NoteOn:
			case NoteOff:
			case AfterTouchPoly:
			case ControlChange:
			case ProgramChange:
				// note or number, its the same
				note = dataByte;
				break;

			case AfterTouchChannel:
				pressure = dataByte;
				break;

			case SongSelect:
			case TimeCodeQuarterFrame:
				// songNumber or data, its the same
				data = dataByte;
				break;
			
			case PitchBend:
				// lsb
				bend = dataByte;
				break;

			case SongPosition:
				// lsb
				beats = dataByte;
				break;
		}
	}

	void SetDataByte2(byte dataByte)
	{
		switch(msgType)
		{
			case NoteOn:
			case NoteOff:
			case AfterTouchPoly:
			case ControlChange:
				// velocity, value or pressure, its the same
				note = dataByte;
				break;

			case PitchBend:
				// msb
				bend |= (dataByte << 7);
				break;

			case SongPosition:
				// msb
				beats |= (dataByte << 7);
				break;
		}
	}

	void SetNoteOff(byte channel, byte note, byte velocity)
	{
		msgType = Midi.NoteOff;
		channel = channel;
		note = note;
		velocity = velocity;
	}

	void SetNoteOn(byte channel, byte note, byte velocity)
	{
		msgType = Midi.NoteOn;
		channel = channel;
		note = note;
		velocity = velocity;
	}

	void SetAfterTouchPoly(byte channel, byte note, byte pressure)
	{
		msgType = Midi.AfterTouchPoly;
		channel = channel;
		note = note;
		pressure = pressure;
	}

	void SetControlChange(byte channel, byte number, byte value)
	{
		msgType = Midi.ControlChange;
		channel = channel;
		number = number;
		value = value;
	}

	// TODO: more helper setters
};

#endif //__MIDIMESSAGE_H__