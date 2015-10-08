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

BeginEnum(UsartModes)
{
    Invalid,
    Async,
    AsyncDoubleSpeed,
    SyncMaster,
    SyncSlave
}
EndEnum(UsartModes)

BeginEnum(UsartDataBits)
{
    Bits5,
    Bits6,
    Bits7,
    Bits8,
    Bits9,
}
EndEnum(UsartDataBits)

BeginEnum(UsartParity)
{
    Off,
    Even,
    Odd
}
EndEnum(UsartParity)

BeginEnum(UsartStopBits)
{
    OneStopBit,
    TwoStopBits,
}
EndEnum(UsartStopBits)


class UsartConfig
{
    #define MAX_UBBR 4096
    #define DIV_SYNC 2
	#define DIV_ASYNC2SPEED 8
	#define DIV_ASYNC 16
	
public:
    UsartConfig()
        : _clockDivider(0), _ubrr(0), 
        _dataBits(UsartDataBits::Bits8), _parity(UsartParity::Off), _stopBits(UsartStopBits::OneStopBit)
    { }
    
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
    
    inline bool InitSyncSlave()
    {
        // TODO
        ClearBaudRate();
        return false;
    }
    
    inline uint16_t getBaudRate() const
    {
        if (_ubrr == 0 || _clockDivider == 0) return 0;
        return CalcBaudRate(_clockDivider, _ubrr);
    }
    
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
    
    inline void setDataBits(UsartDataBits numberOfDataBits)
    {
        _dataBits = numberOfDataBits;
    }
    
    inline UsartDataBits getDataBits() const
    {
        return _dataBits;
    }
    
    inline void setParity(UsartParity parity)
    {
        _parity = parity;
    }
    
    inline UsartParity getParity() const
    {
        return _parity;
    }
    
    inline void setStopBits(UsartStopBits stopBits)
    {
        _stopBits = stopBits;
    }
    
    inline UsartStopBits getStopBits() const
    {
        return _stopBits;
    }
    
//protected: - cant be-friend a template class (Usart)
    inline uint16_t getUBRR() const
    {
        return _ubrr;
    }
    
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
    
    inline uint8_t getUCSRB() const
    {
        uint8_t ucsrb = 0;
        
        if (_dataBits == UsartDataBits::Bits9)
        {
            Bit<UCSZ02>::Set(ucsrb);
        }
        
        return ucsrb;
    }
    
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