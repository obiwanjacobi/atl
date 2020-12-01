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

#ifndef __URM37V32_CONTROLLER_H__
#define __URM37V32_CONTROLLER_H__

namespace ATL {

    /** Implements the protocol to communicate with the URM37 v3.2, a sonic distance sensor (with temp).
     *  See also the URM37V32_Driver class.
     * More info: http://www.seeedstudio.com/depot/datasheet/URM3.2%20Mannual.pdf
     *  \tparam BaseT is used as a base class and implements:
     *  `void SendCommand(uint8_t, uint8_t, uint8_t)` (URM37V32_Driver)
     *  `int ReceiveResponse(uint8_t & , uint8_t & , uint8_t & )` (URM37V32_Driver)
     *  returns 0- no data available, 1- some data available waiting on more, 2- error in checksum, 3- success.
     */
    template<class BaseT>
    class URM37V32_Controller : public BaseT
    {
    
#define CMD_TEMPERATURE 0x11
#define CMD_DISTANCE 0x22
#define CMD_READ_EEPROM 0x33
#define CMD_WRITE_EEPROM 0x44

    public:
        // \todo refactor to use the driver enum.
        /** Lists the responses that can be received.
         */
        enum ReceiveResult
        {
            /** Nothing received or didn't make sense. */
            None,
            /** Response is still pending. */
            Pending,
            /** Response received but malformed. */
            ChecksumError,
            /** Response received correctly. */
            Success
        };

        // 
        /** Mode 2: Autonomous trigger mode.
         *  Under this mode, the sensor will make a sensor reading every 25ms and compare the reading with a
         *  threshold [..], if the reading is equal or
         *  smaller than the threshold, pin COMP/TRIG will have low output. In the meantime, pin PWM will output
         *  the distance reading, every 50us low level stands for 1cm, by counting the number of these pulses, the
         *  distance can be calculated. This mode can be simply used as an ON/OFF switch. 
         *  \param the threshold to test for.
         *  \return Returns true when successful.
         */
        bool SetAutonomousTriggerMode(uint16_t threshold)
        {
            if (!WriteEEPROM(0x02, 0xaa)) return false;
            if (!WriteEEPROM(0x00, (uint8_t )threshold)) return false;

            return WriteEEPROM(0x01, (uint8_t )(threshold >> 8));
        }

        /** Mode 3: PWM passive control mode.
         *  Under this mode, a low pull on pin COMP/TRIG will trigger a sensor reading. The width of the pulse is
         *  proportional to the servo rotating degree. After a successful sensor reading, Pin PWM will output pulses,
         *  every 50us represents 1cm. If the reading is invalid, a 50000us pulse will be returned. 
         *  \return Returns true when successful.
         */
        bool SetPassiveControlMode()
        {
            return WriteEEPROM(0x02, 0xbb);
        }

        /** Starts a distance measurement.
         *  Call `EndDistance()` next.
         */
        void BeginDistance()
        {
            BaseT::SendCommand(CMD_DISTANCE, 0x00, 0x00);
        }

        /** Starts a distance measurement.
         *  Call `EndDistance()` next.
         *  \param degrees: 0-270
         */
        void BeginDistance(uint16_t degrees)
        {
            BaseT::SendCommand(CMD_DISTANCE, map(degrees, 0, 270, 0, 46), 0x00);
        }

        /** Finalizes a distance measurement.
         *  \param outDistance receives the measured distance.
         *  \return Returns the result. If `Pending` is returned call this method again at a later time.
         */
        ReceiveResult EndDistance(uint16_t& outDistance)
        {
            uint8_t command;
            uint8_t data1;
            uint8_t data2;

            ReceiveResult retVal = (ReceiveResult)BaseT::ReceiveResponse(command, data1, data2);

            if (retVal == Success)
            {
                if (command == CMD_DISTANCE && data1 != 0xFF && data2 != 0xFF)
                {
                    outDistance = (data1 << 8) | data2;
                }
                else
                {
                    // invalid reading
                    retVal = None;
                }
            }

            return retVal;
        }

        /** Starts a temperature measurement.
         *  Call `EndTemperature()` next.
         */
        void BeginTemperature()
        {
            BaseT::SendCommand(CMD_TEMPERATURE, 0x00, 0x00);
        }

        /** Finalizes a temperature measurement.
         *  \param outTemperature receives the measured temperature.
         *  \return Returns the result. If `Pending` is returned call this method again at a later time.
         */
        ReceiveResult EndTemperature(int& outTemperature)
        {
            uint8_t command;
            uint8_t data1;
            uint8_t data2;

            ReceiveResult retVal = BaseT::ReceiveRespone(command, data1, data2);

            if (retVal == Success)
            {
                if (command == CMD_TEMPERATURE)
                {
                    outTemperature = ((data1 & 0x0F) << 8) | data2;

                    // below 0
                    if ((data1 & 0xF0) != 0)
                    {
                        outTemperature = -outTemperature;
                    }
                }
                else
                {
                    // invalid reading
                    retVal = None;
                }
            }

            return retVal;
        }

    private:
        bool WriteEEPROM(uint8_t data1, uint8_t data2)
        {
            BaseT::SendCommand(CMD_WRITE_EEPROM, data1, data2);

            uint8_t outCommand;
            uint8_t outData1;
            uint8_t outData2;

            // TODO: timeout?
            while(BaseT::ReceiveResponse(outCommand, outData1, outData2) != Success);

            // check echo response
            return (outCommand == 0x44 && outData1 == data1 && outData2 == data2);
        }

#ifndef Arduino_h
        // copied from arduino: WMath.cpp
        inline long map(long x, long in_min, long in_max, long out_min, long out_max)
        {
            return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
        }
#endif

    };

} // ATL

#endif //__URM37V32_CONTROLLER_H__