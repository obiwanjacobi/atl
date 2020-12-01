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

#ifndef __USARTCONFIG_H__
#define __USARTCONFIG_H__

#include <stdint.h>
#include <avr/io.h>
#include "../Bit.h"
#include "../Math.h"
#include "../EnumScope.h"

#ifndef F_CPU
#	error	"#define F_CPU with the clock speed of the MCU. For instance 160000000L for 16MHz."
#endif

namespace ATL {
namespace MCU {

/** Lists the mode the Usart can be used in.
 *  (Currently only the Async modes are implemented)
 */
BeginEnum(UsartModes)
{
    /** Not a mode. */
    Invalid,
    /** Normal Asynchronous mode. */
    Async,
    /** Double Speed Asynchronous mode. */
    AsyncDoubleSpeed,
    /** Master Synchronous (with clock output) mode. */
    SyncMaster,
    /** Slave Synchronous (with clock input) mode. */
    SyncSlave
}
EndEnum(UsartModes)

/** Indicates how many data bits are communicated.
 *  5-9 bits are supported (not including start, parity and stop bits).
 */
BeginEnum(UsartDataBits)
{
    /** 5 bits. */
    Bits5,
    /** 6 bits. */
    Bits6,
    /** 7 bits. */
    Bits7,
    /** 8 bits. */
    Bits8,
    /** 9 bits. */
    Bits9,
}
EndEnum(UsartDataBits)

/** Indicates if and how to use the parity bit.
 *  Parity counts the number of one's in the data bit.
 */
BeginEnum(UsartParity)
{
    /** No parity bit is used. */
    Off,
    /** Number of one's is even. */
    Even,
    /** Number of one's is odd. */
    Odd
}
EndEnum(UsartParity)

/** Indicates how many stop bits to use.
 *  A stop bit indicates the end of one transmitted data 'byte'.
 */
BeginEnum(UsartStopBits)
{
    /** One stop bit is used. */
    OneStopBit,
    /** Two stop bits are used. */
    TwoStopBits,
}
EndEnum(UsartStopBits)


/** The UsartConfig class manages the configuration values for setting up an Usart.
 *  The same UsartConfig instance can be used for multiple calls to Usart.OpenAsync/Sync.
 */
class UsartConfig
{
    #define MAX_UBBR 4096
    #define DIV_SYNC 2
    #define DIV_ASYNC2SPEED 8
    #define DIV_ASYNC 16
    
public:
    /** Constructs a new instance.
     *  Default: 8 data bits, no parity and one stop bit. 
     */
    UsartConfig()
        : _clockDivider(0), _ubrr(0), 
        _dataBits(UsartDataBits::Bits8), _parity(UsartParity::Off), _stopBits(UsartStopBits::OneStopBit)
    { }
    
    /** Initializes an Asynchronous mode using the baudRate.
     *  The configured baud rate can deviate from the specified baudRate.
     *  The method will choose between normal and double speed Async mode based on the smallest deviation of the baud rate.
     *  \param baudRate is the target baud rate to configure. Final configured value may deviate.
     *  \return Returns true when successful.
     */
    bool InitAsync(uint16_t baudRate)
    {
        int16_t ubrr8 = CalcUBRR(8, baudRate);
        int16_t ubrr16 = CalcUBRR(16, baudRate);

        // if one (or both) are invalid the other (or none) is correct
        if (!isValidUBRR(ubrr8) || !isValidUBRR(ubrr16))
        {
            if (isValidUBRR(ubrr16))
            {
                _clockDivider = DIV_ASYNC;
                _ubrr = ubrr16;
                return true;
            }

            if (isValidUBRR(ubrr8))
            {
                _clockDivider = DIV_ASYNC2SPEED;
                _ubrr = ubrr8;
                return true;
            }

            ClearBaudRate();
            return false;
        }

        // if both divider-rates are valid, pick the one with the lowest deviation
        int16_t delta8 = Math::Abs<int16_t>(baudRate - CalcBaudRate(DIV_ASYNC2SPEED, ubrr8));
        int16_t delta16 = Math::Abs<int16_t>(baudRate - CalcBaudRate(DIV_ASYNC, ubrr16));

        if (delta16 > delta8)
        {
            _clockDivider = DIV_ASYNC2SPEED;
            _ubrr = ubrr8;
            return true;
        }

        _clockDivider = DIV_ASYNC;
        _ubrr = ubrr16;
        return true;
    }
    
    //inline bool InitSyncSlave()
    //{
    //    // TODO
    //    ClearBaudRate();
    //    return false;
    //}
    
    /** Retrieves the configured baud rate.
     *  This value may deviate from the baudRate specified in the InitAsync method.
     *  \return Returns the baud rate.
     */
    inline uint16_t getBaudRate() const
    {
        if (_ubrr == 0 || _clockDivider == 0) return 0;
        return CalcBaudRate(_clockDivider, _ubrr);
    }
    
    /** Retrieves the configured mode.
     *  (Currently only Async modes are implemented).
     *  \return Returns Invalid if the InitAsync method was not called.
     */
    inline UsartModes getMode() const
    {
        switch(_clockDivider)
        {
            case 16:
                return UsartModes::Async;
            case 8:
                return UsartModes::AsyncDoubleSpeed;
            case 2:
                return UsartModes::SyncMaster;
            case 0:
                return UsartModes::SyncSlave;
            default:
                break;
        }
        
        return UsartModes::Invalid;
    }
    
    /** Configures the number of data bits.
     *  \param numberOfDataBits is the value to configure.
     */
    inline void setDataBits(UsartDataBits numberOfDataBits)
    {
        _dataBits = numberOfDataBits;
    }
    
    /** Retrieves the configured number of data bits.
     *  \return Returns the configured value.
     */
    inline UsartDataBits getDataBits() const
    {
        return _dataBits;
    }
    
    /** Configures the parity.
     *  \param parity is the value to configure.
     */
    inline void setParity(UsartParity parity)
    {
        _parity = parity;
    }
    
    /** Retrieves the configured parity.
    *  \return Returns the configured value.
    */
    inline UsartParity getParity() const
    {
        return _parity;
    }
    
    /** Configures the number of stop bits.
     *  \param stopBits is the value to configure.
     */
    inline void setStopBits(UsartStopBits stopBits)
    {
        _stopBits = stopBits;
    }
    
    /** Retrieves the configured number of stop bits.
    *  \return Returns the configured value.
    */
    inline UsartStopBits getStopBits() const
    {
        return _stopBits;
    }
    
//protected: - cant be-friend a template class (Usart)

    /** Retrieves the register value.
     *  Used by the Usart class to Open the device.
     */
    inline uint16_t getUBRR() const
    {
        return _ubrr;
    }
    
    /** Retrieves the register value.
     *  Used by the Usart class to Open the device.
     */
    inline uint8_t getUCSRA() const
    {
        uint8_t ucsra = 0;
        
        if (_clockDivider == DIV_ASYNC2SPEED)
        {
            // double speed flag
            Bit<U2X0>::Set(ucsra);
        }
        
        return ucsra;
    }
    
    /** Retrieves the register value.
     *  Used by the Usart class to Open the device.
     */
    inline uint8_t getUCSRB() const
    {
        uint8_t ucsrb = 0;
        
        if (_dataBits == UsartDataBits::Bits9)
        {
            Bit<UCSZ02>::Set(ucsrb);
        }
        
        return ucsrb;
    }
    
    /** Retrieves the register value.
     *  Used by the Usart class to Open the device.
     */
    inline uint8_t getUCSRC() const
    {
        uint8_t ucsrc = 0;
        
        // UMSEL0:1
        if (_clockDivider < DIV_ASYNC2SPEED)
        {
            // sync mode
            Bit<UMSEL00>::Set(ucsrc);
        }
        
        // UPM0:1
        if (_parity != UsartParity::Off)
        {
            if (_parity == UsartParity::Even)
                Bit<UPM00>::Set(ucsrc);
            
            Bit<UPM01>::Set(ucsrc);
        }
        
        // USBS
        if (_stopBits == UsartStopBits::TwoStopBits)
        {
            Bit<USBS0>::Set(ucsrc);
        }
        
        // UCSZ0:1
        if (_dataBits < UsartDataBits::Bits9)
        {
            ucsrc |= (_dataBits.value << UCSZ00);
        }
        else
        {
            // Bits9 = UCSZ00=1, UCSZ01=1
            Bit<UCSZ00>::Set(ucsrc);
        }
        
        // UCPOL (sync clock polarity)
        
        return ucsrc;
    }

    
private:
    uint8_t	_clockDivider;
    uint16_t _ubrr;
    UsartDataBits _dataBits;
    UsartParity _parity;
    UsartStopBits _stopBits;
    
    // TODO: ((F_CPU + UART_BAUD_RATE * 8L) / (UART_BAUD_RATE * 16L) - 1)
    // ubrr = (fOsc / ([16,8,2] * baudRate)) - 1
    inline static int16_t CalcUBRR(uint8_t clockDivider, uint16_t baudRate)
    {
        return (int16_t)((F_CPU / ((int32_t)clockDivider * (int32_t)baudRate)) - 1);
    }

    // baudRate = fOsc / ([16,8,2] * (ubrr + 1))
    inline static int16_t CalcBaudRate(uint8_t clockDivider, uint16_t ubrr)
    {
        return (int16_t)(F_CPU / ((int32_t)clockDivider * (int32_t)(ubrr + 1)));
    }

    inline static bool isValidUBRR(int16_t ubrr)
    {
        return (ubrr < MAX_UBBR && ubrr >= 0);
    }

    inline void ClearBaudRate()
    {
        _clockDivider = 0;
        _ubrr = 0;
    }
};

}} // ATL::MCU

#endif /* __USARTCONFIG_H__ */