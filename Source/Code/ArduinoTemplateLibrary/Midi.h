/*
Arduino Template Library https://github.com/obiwanjacobi/atl
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
#include "EnumScope.h"

namespace ATL {

/** The MIDI communication speed. */
#define MIDI_BAUDRATE			31250

    /** The Midi static class contains some base definitions and functions.
     *  The class is static and cannot be instantiated.
     */
    class Midi
    {
    public:
        /** The MIDI communication speed. */
        static const uint16_t BaudRate = 31250;

        /** The categories the Midi messages belong to.
         */
        BeginEnum(MessageCategory)
        {
            /** Category not set. */
            NotSet,
            /** Note information. */
            Note,
            /** After touch information. */
            AfterTouch,
            /** Control information. */
            ControlChange,
            /** Preset (program) information. */
            ProgramChange,
            /** Pitch bend information. */
            PitchBend,
            /** System specific information. */
            SystemExclusive,
            /** System common information. */
            SystemCommon,
            /** Real-time information. */
            Realtime,
        }
        EndEnum(MessageCategory)

        /** All Midi message types. */
        enum MessageTypes
        {
            /** For notifying errors */
            InvalidType           = 0x00,
            /** Note Off */
            NoteOff	              = 0x80,
            /** Note On */
            NoteOn                = 0x90,
            /** Polyphonic AfterTouch */
            AfterTouchPoly        = 0xA0,
            /** Control Change / Channel Mode */
            ControlChange         = 0xB0,
            /** Program Change */
            ProgramChange         = 0xC0,
            /** Channel (monophonic) AfterTouch */
            AfterTouchChannel     = 0xD0,
            /** Pitch Bend */
            PitchBend             = 0xE0,
            /** System Exclusive */
            SystemExclusive       = 0xF0,
            /** System Common - MIDI Time Code Quarter Frame */
            TimeCodeQuarterFrame  = 0xF1,
            /** System Common - Song Position Pointer */
            SongPosition          = 0xF2,
            /** System Common - Song Select */
            SongSelect            = 0xF3,
            /** System Common - Tune Request */
            TuneRequest           = 0xF6,
            /** System Real Time - Timing Clock */
            Clock                 = 0xF8,
            /** System Real Time - Start */
            Start                 = 0xFA,
            /** System Real Time - Continue */
            Continue              = 0xFB,
            /** System Real Time - Stop */
            Stop                  = 0xFC,
            /** System Real Time - Active Sensing */
            ActiveSensing         = 0xFE,
            /** System Real Time - System Reset */
            SystemReset           = 0xFF,
        };

        /** Determines if the midiByte is a status-byte.
         *  \return Returns true when the midiByte is a mid status byte.
         */
        inline static bool IsStatus(uint8_t midiByte)
        {
            return ((midiByte & 0x80) > 0);
        }

        /** Extracts the type of message from the midiByte.
         *  \return Returns the status portion of a midi status uint8_t (stripping of channel)
         *  or returns 0 (zero) / `InvalidType` if midiByte is not a midi status byte.
         */
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

        /** Determines the message length in bytes for the midi message based on a statusByte.
         *  \return Returns 0 if statusByte is not a statusByte.
         *  Returns -1 for SysEx messages, for there is no telling how big those messages are going to be.
         *  Returns 1, 2 or 3 for normal midi messages. This includes the status-byte itself.
         */
        inline static int8_t GetMessageLength(uint8_t statusByte)
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

                // 2 bytes messages
            case ProgramChange:
            case AfterTouchChannel:
            case TimeCodeQuarterFrame:
            case SongSelect:
                return 2;

                // 3 bytes messages
            case NoteOn:
            case NoteOff:
            case ControlChange:
            case PitchBend:
            case AfterTouchPoly:
            case SongPosition:
                return 3;

                // special sysex case
            case SystemExclusive:
                return -1;

            default:
                return 0;
            }
        }

        /** Determines if the statusByte is a channel message.
         *  \param statusByte is the status-byte to test.
         *  \return Returns true if the statusByte is channel message.
         */
        inline static bool IsChannelMessage(uint8_t statusByte)
        {
            return (statusByte >= NoteOff && statusByte <= PitchBend);
        }

        /** Determines if the statusByte is a real-time message.
         *  \param statusByte is the status-byte to test.
         *  \return Returns true if the statusByte is real-time message.
         */
        inline static bool IsRealtimeMessage(uint8_t statusByte)
        {
            return (statusByte >= Clock && statusByte <= SystemReset);
        }

        /** Determines if the statusByte is a system common message.
         *  \param statusByte is the status-byte to test.
         *  \return Returns true if the statusByte is system common message.
         */
        inline static bool IsSystemCommonMessage(uint8_t statusByte)
        {
            return (statusByte >= SystemExclusive && statusByte <= 0xF7);
        }

        /** Determines if the statusByte is a system (real-time & common) message.
        *  \param statusByte is the status-byte to test.
        *  \return Returns true if the statusByte is system message.
        */
        inline static bool IsSystemMessage(uint8_t statusByte)
        {
            return (statusByte >= SystemExclusive && statusByte <= SystemReset);
        }

    private:
        Midi() {}
    };

} // ATL

#endif //__MIDI_H__
