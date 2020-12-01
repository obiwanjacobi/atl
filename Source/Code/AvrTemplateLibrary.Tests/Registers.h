#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include <string.h>
#include <stdint.h>


// Fakes register memory of AVR MCUs
class Registers
{
    #define MAX_MEMSPACE 255

public:
    inline static void Clear()
    {
        memset(_memSpace, 0, MAX_MEMSPACE);
    }

    inline static volatile uint16_t& At16(uint8_t memAddress)
    {
        return *((uint16_t*)&_memSpace[memAddress]);
    }

    inline static volatile uint8_t& At8(uint8_t memAddress)
    {
        return _memSpace[memAddress];
    }

private:
    Registers()
    { }

    static uint8_t _memSpace[MAX_MEMSPACE];
};

#endif //__REGISTERS_H__