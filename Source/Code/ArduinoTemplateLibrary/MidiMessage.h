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

#ifndef __MIDIMESSAGE_H__
#define __MIDIMESSAGE_H__

#include <string.h>
#include "Midi.h"

namespace ATL {

#define MASK_7BIT_LO	0x007F
#define MASK_7BIT_HI	0x3F80
#define MASK_DATABYTE	0x7F
#define MASK_CHANNEL	0x0F

    /** A Midi message structure for all midi messages.
     *  NoteOff	              channel, note, velocity
     *  NoteOn                channel, note, velocity
     *  AfterTouchPoly        channel, note, pressure
     *  ControlChange         channel, number, value
     *  ProgramChange         channel, number
     *  AfterTouchChannel     channel, pressure
     *  PitchBend             channel, bend
     *  SystemExclusive       -
     *  TimeCodeQuarterFrame  data
     *  SongPosition          beats
     *  SongSelect            songNumber
     *  TuneRequest           -
     *  Clock                 -
     *  Start                 -
     *  Continue              -
     *  Stop                  -
     *  ActiveSensing         -
     *  SystemReset           -
     */
    struct MidiMessage
    {
        /** Constructs the instance.
         *  Zero's-out all vars.
         */
        MidiMessage() 
        {
            memset(this, 0, sizeof(MidiMessage));
        }

        /** The Midi message type */
        Midi::MessageTypes MessageType;

        union
        {
            struct // channel messages
            {
                /** The Midi Channel. */
                uint8_t Channel;

                union
                {
                    struct
                    {
                        union
                        {
                            /** Note number. */
                            uint8_t Note;
                            /** Program- and Control Change numbers. */
                            uint8_t Number;
                        };

                        union
                        {
                            /** Note volume. */
                            uint8_t Velocity;
                            /** Control Change values. */
                            uint8_t Value;
                            /** After touch. */
                            uint8_t Pressure;
                        };
                    };

                    /** Pitch bend. */
                    int Bend;
                };
            };

            /** Song position. */
            uint16_t Beats;
            /** Song select. */
            uint8_t SongNumber;
            /** Time code. */
            uint8_t Data;
        };

        /** filler to get to power of 2 struct size (8 bytes) */
        //uint8_t reserved[3];

        /** Retrieves the complete status-byte from the message.
         *  \return Returns the MessageType with possibly the Channel.
         */
        uint8_t GetStatusByte() const
        {
            if (Midi::IsSystemMessage(MessageType))
            {
                return MessageType;
            }
            
            return (MessageType | Channel);
        }

        /** Assigns the statusByte to the message instance.
         *  \param statusByte is the status to assign.
         */
        void SetStatusByte(uint8_t statusByte)
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

        /** Retrieves the first data byte from the midi message.
         *  \return Returns the data byte.
         */
        uint8_t GetDataByte1() const
        {
            uint8_t value = 0;

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
            default:
                break;
            }

            return (value & MASK_DATABYTE);
        }

        /** Assigns the first data byte to the midi message.
         *  \param dataByte is the data byte to assign.
         */
        void SetDataByte1(uint8_t dataByte)
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
            default:
                break;
            }
        }

        /** Retrieves the second data byte from the midi message.
         *  \return Returns the data byte.
         */
        uint8_t GetDataByte2() const
        {
            uint8_t value = 0;

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
            default:
                break;
            }

            return (value & MASK_DATABYTE);
        }

        /** Assigns the second data byte to the midi message.
         *  \param dataByte is the data byte to assign.
         */
        void SetDataByte2(uint8_t dataByte)
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
            default:
                break;
            }
        }

        /** Copies the content of this message to the target.
         *  Does nothing if the target is NULL.
         *  \param target is the pointer to the message that receives the data.
         */
        void CopyTo(MidiMessage* target) const
        {
            if (target == NULL) return;

            memcpy(target, this, sizeof(MidiMessage));
        }
    };

} // ATL

#endif //__MIDIMESSAGE_H__