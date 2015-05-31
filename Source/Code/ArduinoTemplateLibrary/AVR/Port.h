/*
 * Register.h
 *
 * Created: 9-5-2015 14:42:19
 *  Author: Marc
 */


#ifndef PORT_H_
#define PORT_H_

//#include <sfr_defs.h>

namespace ATL
{

// TODO: make device specific
enum Ports //: uint8_t
{
#ifdef PORTA
    PortA = 0,
#endif //PORTA
#ifdef PORTB
	PortB = 1,
#endif //PORTB
#ifdef PORTC
	PortC = 2,
#endif //PORTC
#ifdef PORTD
	PortD = 3,
#endif //PORTC
#ifdef PORTE
	PortE = 4,
#endif //PORTE
#ifdef PORTF
	PortF = 5,
#endif //PORTF
};

enum PinIO //: uint8_t
{
    Input,
    Output
};

enum Pins //: uint8_t
{
    Pin0,
    Pin1,
    Pin2,
    Pin3,
    Pin4,
    Pin5,
    Pin6,
    Pin7
};

/*
 *
 */
template<const Ports PortId>
class Port
{
private:
    Port(){}

public:
    // Enables the internal pull-up for inputs.
    // Returns false when pin is not an input.
    inline static bool EnablePullup(Pins pin, bool enable = true)
    {
        uint8_t mask = PinToMask(pin);

        if ((PortRegDir() & mask) == Input)
        {
            PortRegOut() |= mask;
            return true;
        }

        return false;
    }

	inline static void SetDirection(Pins pin, PinIO io)
    {
        uint8_t mask = PinToMask(pin);

        if (io) PortRegDir() |= mask;
        else PortRegDir() &= ~mask;
    }

	inline static void SetDirection(PinIO io7, PinIO io6, PinIO io5, PinIO io4, PinIO io3, PinIO io2, PinIO io1, PinIO io0)
    {
        PortRegDir() = io7 << 7 | io6 << 6 | io5 << 5 | io4 << 4 | io3 << 3 | io2 << 2 | io1 << 1 | io0;
    }

    inline static void SetDirection(uint8_t allPinsIO)
    {
        PortRegDir() = allPinsIO;
    }

    inline static void Write(Pins pin, bool value)
    {
        uint8_t mask = PinToMask(pin);

        if (value) PortRegOut() |= mask;
        else PortRegOut() &= ~mask;
    }

    inline static bool Read(Pins pin)
    {
        return (PortRegIn() & PinToMask(pin)) > 0;
    }

    inline Ports getPort() const
    {
        return PortId;
    }

private:
    inline static volatile uint8_t& PortRegIn()
    {
        return _SFR_IO8(((uint8_t)PortId * 3));
    }

    inline static volatile uint8_t& PortRegDir()
    {
        return _SFR_IO8((((uint8_t)PortId * 3) + 0x01));
    }

    inline static volatile uint8_t& PortRegOut()
    {
        return _SFR_IO8((((uint8_t)PortId * 3) + 0x02));
    }

    inline static uint8_t PinToMask(Pins pin)
    {
        return 1 << (uint8_t)pin;
    }
};

} // ATL

#endif /* PORT_H_ */