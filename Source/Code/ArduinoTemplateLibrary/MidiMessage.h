#ifndef __MIDIMESSAGE_H__
#define __MIDIMESSAGE_H__

#include <string.h>
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

#define MASK_7BIT_LO	0x007F
#define MASK_7BIT_HI	0x3F80
#define MASK_DATABYTE	0x7F
#define MASK_CHANNEL	0x0F

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

	byte GetStatusByte()
	{
		if (!Midi::IsSystemMessage(MessageType))
		{
			return (MessageType | Channel);
		}

		return MessageType;
	}

	void SetStatusByte(byte statusByte)
	{
		MessageType = Midi::GetMessageType(statusByte);
		// reset state
		Bend = 0;
		Beats = 0;

		// if it is NOT a system message, set the channel
		if (!Midi::IsSystemMessage(MessageType))
		{
			Channel = (statusByte & MASK_CHANNEL);
		}
	}

	byte GetDataByte1()
	{
		byte value = 0;

		switch(MessageType)
		{
			case Midi::NoteOn:
			case Midi::NoteOff:
			case Midi::AfterTouchPoly:
			case Midi::ControlChange:
			case Midi::ProgramChange:
				// note or number, its the same
				value = Note;
				break;

			case Midi::AfterTouchChannel:
				return Pressure;
				break;

			case Midi::SongSelect:
			case Midi::TimeCodeQuarterFrame:
				// songNumber or data, its the same
				value = Data;
				break;
			
			case Midi::PitchBend:
				// lsb
				value = (Bend & MASK_7BIT_LO);
				break;

			case Midi::SongPosition:
				// lsb
				value = (Beats & MASK_7BIT_LO);
				break;
		}

		return (value & MASK_DATABYTE);
	}

	void SetDataByte1(byte dataByte)
	{
		switch(MessageType)
		{
			case Midi::NoteOn:
			case Midi::NoteOff:
			case Midi::AfterTouchPoly:
			case Midi::ControlChange:
			case Midi::ProgramChange:
				// note or number, its the same
				Note = dataByte;
				break;

			case Midi::AfterTouchChannel:
				Pressure = dataByte;
				break;

			case Midi::SongSelect:
			case Midi::TimeCodeQuarterFrame:
				// songNumber or data, its the same
				Data = dataByte;
				break;
			
			case Midi::PitchBend:
				// lsb
				Bend = dataByte;
				break;

			case Midi::SongPosition:
				// lsb
				Beats = dataByte;
				break;
		}
	}

	byte GetDataByte2()
	{
		byte value = 0;

		switch(MessageType)
		{
			case Midi::NoteOn:
			case Midi::NoteOff:
			case Midi::AfterTouchPoly:
			case Midi::ControlChange:
				// velocity, value or pressure, its the same
				value = Velocity;
				break;

			case Midi::PitchBend:
				// msb
				value = (Bend & MASK_7BIT_HI) >> 7;
				break;

			case Midi::SongPosition:
				// msb
				value = (Beats & MASK_7BIT_HI) >> 7;
				break;
		}

		return (value & MASK_DATABYTE);
	}

	void SetDataByte2(byte dataByte)
	{
		switch(MessageType)
		{
			case Midi::NoteOn:
			case Midi::NoteOff:
			case Midi::AfterTouchPoly:
			case Midi::ControlChange:
				// velocity, value or pressure, its the same
				Velocity = dataByte;
				break;

			case Midi::PitchBend:
				// msb
				Bend |= (dataByte << 7);
				break;

			case Midi::SongPosition:
				// msb
				Beats |= (dataByte << 7);
				break;
		}
	}

	void CopyTo(MidiMessage* target)
	{
		if (target == NULL) return;

		memcpy(target, this, sizeof(MidiMessage));
	}
};

#endif //__MIDIMESSAGE_H__