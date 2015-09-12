/*  
	Arduino Template Library http://atl.codeplex.com
	Written by Marc Jacobi
	Copyright 2012-2015 All Rights Reserved

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __MIDI_H__
#define __MIDI_H__

#include <stdint.h>

namespace ATL {

#define MIDI_BAUDRATE			31250

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
		catRealtime,
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
	inline static bool IsStatus(uint8_t midiByte)
	{
		return ((midiByte & 0x80) > 0);
	}

	// Returns the status portion of a midi status uint8_t (stripping of channel)
	// or returns 0 (zero) if midiByte is not a midi status byte.
	inline static MessageTypes GetMessageType(uint8_t midiByte)
	{
		if (IsStatus(midiByte))
		{
			uint8_t status = (midiByte & 0xF0);

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
	inline static uint8_t GetMessageLength(uint8_t statusByte)
	{
		switch (GetMessageType(statusByte))
		{
			// 1 uint8_t messages
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

	inline static bool IsChannelMessage(uint8_t statusByte)
	{
		return (statusByte >= NoteOff && statusByte <= PitchBend);
	}

	inline static bool IsRealtimeMessage(uint8_t statusByte)
	{
		return (statusByte >= Clock && statusByte <= SystemReset);
	}

	inline static bool IsSystemCommonMessage(uint8_t statusByte)
	{
		return (statusByte >= SystemExclusive && statusByte <= 0xF7);
	}

	// Both System Common as well as Realtime
	inline static bool IsSystemMessage(uint8_t statusByte)
	{
		return (statusByte >= SystemExclusive && statusByte <= SystemReset);
	}

private:
	Midi() {}
};

} // ATL

#endif //__MIDI_H__
