#ifndef __MIDI_H__
#define __MIDI_H__

#include <Arduino.h>

#define MIDI_BAUDRATE			31250

#define MIDI_CHANNEL_OMNI		0
#define MIDI_CHANNEL_OFF		17			// and over

#define MIDI_SYSEX_ARRAY_SIZE	255			// Maximum size is 65535 bytes.


/*! Enumeration of MIDI types */
enum kMIDIType {
	NoteOff	              = 0x80,	///< Note Off
	NoteOn                = 0x90,	///< Note On
	AfterTouchPoly        = 0xA0,	///< Polyphonic AfterTouch
	ControlChange         = 0xB0,	///< Control Change / Channel Mode
	ProgramChange         = 0xC0,	///< Program Change
	AfterTouchChannel     = 0xD0,	///< Channel (monophonic) AfterTouch
	PitchBend             = 0xE0,	///< Pitch Bend
	SystemExclusive       = 0xF0,	///< System Exclusive
	TimeCodeQuarterFrame  = 0xF1,	///< System Common - MIDI Time Code Quarter Frame
	SongPosition          = 0xF2,	///< System Common - Song Position Pointer
	SongSelect            = 0xF3,	///< System Common - Song Select
	TuneRequest           = 0xF6,	///< System Common - Tune Request
	Clock                 = 0xF8,	///< System Real Time - Timing Clock
	Start                 = 0xFA,	///< System Real Time - Start
	Continue              = 0xFB,	///< System Real Time - Continue
	Stop                  = 0xFC,	///< System Real Time - Stop
	ActiveSensing         = 0xFE,	///< System Real Time - Active Sensing
	SystemReset           = 0xFF,	///< System Real Time - System Reset
	InvalidType           = 0x00    ///< For notifying errors
};

class Midi
{
public:
	enum MessageCategory
	{
		catNotSet,
		catNote,
		catAfterTouch,
		catControlChange,
		catProgramChange,
		catPitchBend,
		catSystemExclusive,
		catSystemCommon,
		catRealTime,
	};

	// All Midi message types.
	enum MessageTypes
	{
		InvalidType           = 0x00,   // For notifying errors
		NoteOff	              = 0x80,	// Note Off
		NoteOn                = 0x90,	// Note On
		AfterTouchPoly        = 0xA0,	// Polyphonic AfterTouch
		ControlChange         = 0xB0,	// Control Change / Channel Mode
		ProgramChange         = 0xC0,	// Program Change
		AfterTouchChannel     = 0xD0,	// Channel (monophonic) AfterTouch
		PitchBend             = 0xE0,	// Pitch Bend
		SystemExclusive       = 0xF0,	// System Exclusive
		TimeCodeQuarterFrame  = 0xF1,	// System Common - MIDI Time Code Quarter Frame
		SongPosition          = 0xF2,	// System Common - Song Position Pointer
		SongSelect            = 0xF3,	// System Common - Song Select
		TuneRequest           = 0xF6,	// System Common - Tune Request
		Clock                 = 0xF8,	// System Real Time - Timing Clock
		Start                 = 0xFA,	// System Real Time - Start
		Continue              = 0xFB,	// System Real Time - Continue
		Stop                  = 0xFC,	// System Real Time - Stop
		ActiveSensing         = 0xFE,	// System Real Time - Active Sensing
		SystemReset           = 0xFF,	// System Real Time - System Reset
	};

	// Returns true when the midiByte is a mid status byte.
	inline static bool IsStatus(byte midiByte)
	{
		return ((midiByte & 0x80) > 0);
	}

	// Returns the status portion of a midi status byte (stripping of channel)
	// or returns 0 (zero) if midiByte is not a midi status byte.
	inline static MessageTypes GetMessageType(byte midiByte)
	{
		if (IsStatus(midiByte))
		{
			byte status = (midiByte & 0xF0);

			if (status == 0xF0)
			{
				// system status message
				return (MessageTypes)midiByte;
			}

			return (MessageTypes)status;
		}

		return InvalidType;
	}

	// Returns the number of bytes the midi message consists of.
	// Returns 0 if statusByte is not a statusByte.
	// Returns -1 for SysEx messages, for there is no telling how big those messages are going to be.
	// Returns 1, 2 or 3 for normal midi messages.
	inline static byte GetMessageLength(byte statusByte)
	{
		switch (statusByte)
		{
			// 1 byte messages
			case Start:
			case Continue:
			case Stop:
			case Clock:
			case ActiveSensing:
			case SystemReset:
			case TuneRequest:
				return 1;
				//break;
			
			// 2 bytes messages
			case ProgramChange:
			case AfterTouchChannel:
			case TimeCodeQuarterFrame:
			case SongSelect:
				return 2;
				//break;
			
			// 3 bytes messages
			case NoteOn:
			case NoteOff:
			case ControlChange:
			case PitchBend:
			case AfterTouchPoly:
			case SongPosition:
				return 3;
				//break;
			
			// special sysex case
			case SystemExclusive:
				return -1;
				break;

			default:
				return 0;
				//break;
		}
	}

	inline static bool IsChannelMessage(byte statusByte)
	{
		switch (statusByte)
		{
			case NoteOn:
			case NoteOff:
			case ControlChange:
			case PitchBend:
			case AfterTouchPoly:
			case ProgramChange:
			case AfterTouchChannel:
				return true;

			default:
				return false;
		}
	}

	inline static bool IsRealTimeMessage(byte statusByte)
	{
		switch (statusByte)
		{
			case Start:
			case Continue:
			case Stop:
			case Clock:
			case ActiveSensing:
			case SystemReset:
			case TuneRequest:
				return true;

			default:
				return false;
		}
	}

	inline static bool IsSystemMessage(byte statusByte)
	{
		return (statusByte >= SystemExclusive);
	}

private:
	Midi() {}
};

#endif //__MIDI_H__
