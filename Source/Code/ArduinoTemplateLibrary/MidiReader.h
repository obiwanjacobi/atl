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

#ifndef __MIDIREADER_H__
#define __MIDIREADER_H__

#include "MidiMessage.h"

namespace ATL {

    /** The MidiReader class reads raw bytes from an input stream and notifies when a complete MidiMessage is constructed.
     *  \tparam BaseT is used as a base class and implements:
     *  `uint16_t getLength()`
     *  `int16_t Read()`
     *  `void OnMessage(MidiMessage*)` Called when a MidiMessage is available.
     *  `void OnRealTime(Midi::MessageTypes)` Called when a real-time message is available.
     *  `void OnSysEx(BaseT*)` Called when a system exclusive message is available (not implemented yet!).
     */
    template<class BaseT>
    class MidiReader : public BaseT
    {
    public:
        /** Constructs the instance.
         */
        MidiReader() 
            : _runningStatus(0), _parseState(StatusByte), _endState(NotSet)
        { }

        /** Reads one byte from the buffer and returns.
         *  Call this method repeatedly from the main loop.
         *  Multiple events (notifications) may be fired. 
         *  Note that the MidiMessage used to notify complete message read, is reused for the next read-cycle
         *  - so it is ONLY valid during the notification call.
         *  \return Returns true when a byte was read.
         */
        inline bool Read()
        {
            const uint16_t availableBytes = BaseT::getLength();

            if (availableBytes > 0)
            {
                int16_t midiByte = BaseT::Read();

                if (midiByte != -1)
                {
                    return Dispatch((uint8_t)midiByte);
                }
            }

            return false;
        }

    private:
        MidiMessage _midiMsg;

        enum MidiParseState
        {
            NotSet,
            StatusByte,
            DataByte1,
            DataByte2,
            SOX,
            EOX,
        };

        // Running status is when the next midi message has the same status 
        // as the previous midi message. This way status byte do not have to
        // be repeated when they are the same, saving some bandwidth.
        uint8_t _runningStatus;

        // \todo both these fields can be merged to one. 
        //   Use a bit mask to check one or the other.

        // this is the type of midi byte that is expected next
        // although some midi messages can be interrupted by real-time messages.
        MidiParseState	_parseState;
        // this is the type of midi byte that signals the end of a logical
        // midi message. Only used for multi byte midi messages and sysex.
        MidiParseState	_endState;

        inline void CallOnMessage()
        {
            BaseT::OnMessage(&_midiMsg);
        }

        inline void CallOnRealtime(uint8_t midiStatus)
        {
            BaseT::OnRealtime((Midi::MessageTypes)midiStatus);
        }

        inline void CallOnSysEx()
        {
            // TODO: construct a sysex stream that still fires real-time callbacks
            BaseT::OnSysEx(this);
        }

        void ResetState()
        {
            _parseState = StatusByte;
            _endState = NotSet;
        }


        /*
            - get byte from buffer
            ? if expect status byte
            ? if check for running status
            - insert running status
            - process status byte
            - insert byte read
            ! else process status byte
            ! else
            ? if status byte
            - process status byte (must be real time -or eox?)
            - insert byte read
            */
        bool Dispatch(uint8_t midiByte)
        {
            bool success = false;

            Midi::MessageTypes status = Midi::GetMessageType(midiByte);

            if (_parseState == StatusByte)
            {
                // We expect a status byte, but read a non-status byte
                // But running status is valid, so we have the first two bytes.
                if (status == 0 && _runningStatus != 0)
                {
                    success = ProcessStatusByte(_runningStatus);

                    if (success)
                    {
                        success = ProcessDataByte(midiByte);
                    }
                }
                else if (status > 0)
                {
                    success = ProcessStatusByte(midiByte);
                }
                else
                {
                    // read/sync error
                }
            }
            else if (_parseState == SOX)
            {
                // TODO: sysex
            }
            else
            {
                // we expect a non-status data byte, but we read a status byte
                // it must be a real-time status byte or it is an error.
                if (status > 0)
                {
                    if (Midi::IsRealtimeMessage(status))
                    {
                        success = ProcessStatusByte(midiByte);
                    }
                    else
                    {
                        // read/sync error
                    }
                }
                else
                {
                    success = ProcessDataByte(midiByte);
                }
            }

            if (success &&
                _parseState == NotSet)
            {
                if (Midi::IsChannelMessage(_midiMsg.MessageType))
                {
                    _runningStatus = _midiMsg.MessageType | _midiMsg.Channel;
                }
                else
                {
                    _runningStatus = 0;
                }

                if (_endState != EOX)
                {
                    CallOnMessage();
                }

                ResetState();
            }

            return success;
        }


        bool ProcessStatusByte(uint8_t statusByte)
        {
            bool success = true;

            switch (Midi::GetMessageLength(statusByte))
            {
                // 1 byte messages
            case 1:
                CallOnRealtime(statusByte);
                break;

                // 2 bytes messages
            case 2:
                _midiMsg.SetStatusByte(statusByte);
                _parseState = DataByte1;
                _endState = DataByte1;
                break;

                // 3 bytes messages
            case 3:
                _midiMsg.SetStatusByte(statusByte);
                _parseState = DataByte1;
                _endState = DataByte2;
                break;

                // special sysex case
            case -1:
                _runningStatus = 0;
                _parseState = SOX;
                _endState = EOX;
                CallOnSysEx();
                break;

            default:
                _runningStatus = 0;
                ResetState();
                success = false;
                break;
            }

            return success;
        }


        bool ProcessDataByte(uint8_t midiByte)
        {
            bool success = true;

            switch(_parseState)
            {
            case DataByte1:
                _midiMsg.SetDataByte1(midiByte);
                _parseState = (_parseState != _endState) ? DataByte2 : NotSet;
                break;

            case DataByte2:
                _midiMsg.SetDataByte2(midiByte);
                _parseState = NotSet;
                break;

            default:
                success = false;
                break;
            }

            return success;
        }
    };

} // ATL

#endif //__MIDIREADER_H__