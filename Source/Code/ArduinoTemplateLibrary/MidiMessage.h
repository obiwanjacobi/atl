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
	Midi::MessageTypes MessageType;

	union
	{
		struct // channel messages
		{
			byte Channel;

			union
			{
				struct
				{
					union
					{
						byte Note;		// note number
						byte Number;	// Program- and Control Change numbers
					};

					union
					{
						byte Velocity;	// note
						byte Value;		// Control Change values
						byte Pressure;	// after touch
					};
				};

				int Bend;	// pitch bend
			};
		};
			
		unsigned int Beats;	// song position
		byte SongNumber;	// song select
		byte Data;			// time code
	};

	//byte reserved[3];		// filler to get to power of 2 struct size (8 bytes)

	void SetStatusByte(byte statusByte)
	{
		MessageType = Midi::GetMessageType(statusByte);
		// reset state
		Bend = 0;
		Beats = 0;

		// if it is NOT a system message, set the channel
		if (MessageType < Midi::SystemExclusive)
		{
			Channel = (statusByte & 0x0F);
		}
	}

	void SetDataByte1(byte dataByte)
	{
		switch(MessageType)
		{
			case NoteOn:
			case NoteOff:
			case AfterTouchPoly:
			case ControlChange:
			case ProgramChange:
				// note or number, its the same
				Note = dataByte;
				break;

			case AfterTouchChannel:
				Pressure = dataByte;
				break;

			case SongSelect:
			case TimeCodeQuarterFrame:
				// songNumber or data, its the same
				Data = dataByte;
				break;
			
			case PitchBend:
				// lsb
				Bend = dataByte;
				break;

			case SongPosition:
				// lsb
				Beats = dataByte;
				break;
		}
	}

	void SetDataByte2(byte dataByte)
	{
		switch(MessageType)
		{
			case NoteOn:
			case NoteOff:
			case AfterTouchPoly:
			case ControlChange:
				// velocity, value or pressure, its the same
				Velocity = dataByte;
				break;

			case PitchBend:
				// msb
				Bend |= (dataByte << 7);
				break;

			case SongPosition:
				// msb
				Beats |= (dataByte << 7);
				break;
		}
	}

	void SetNoteOff(byte channel, byte note, byte velocity)
	{
		MessageType = Midi::NoteOff;
		Channel = channel;
		Note = note;
		Velocity = velocity;
	}

	void SetNoteOn(byte channel, byte note, byte velocity)
	{
		MessageType = Midi::NoteOn;
		Channel = channel;
		Note = note;
		Velocity = velocity;
	}

	void SetAfterTouchPoly(byte channel, byte note, byte pressure)
	{
		MessageType = Midi::AfterTouchPoly;
		Channel = channel;
		Note = note;
		Pressure = pressure;
	}

	void SetControlChange(byte channel, byte number, byte value)
	{
		MessageType = Midi::ControlChange;
		Channel = channel;
		Number = number;
		Value = value;
	}

	// TODO: more helper setters
};

#endif //__MIDIMESSAGE_H__