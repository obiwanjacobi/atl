/*
 * Delay.h
 *
 * Created: 16-5-2015 12:52:27
 *  Author: Marc
 */


#ifndef DELAY_H_
#define DELAY_H_

template<const TimeResolution TimeRes>
class Delay
{
public:
    inline static void Delay(unsigned int timeout)
    {

    }
};

template<>
class Delay<Milliseconds>
{
public:
    inline static void Delay(unsigned int timeout)
    {
        _delay_ms(timeout);
    }
};

template<>
class Delay<Microseconds>
{
    public:
    inline static void Delay(unsigned int timeout)
    {
        _delay_us(timeout);
    }
};
#endif /* DELAY_H_ */