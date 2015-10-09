//#include "Registers.h"
class Registers;

// default mcu
#define __AVR_ATmega328P__

// assume 1MHz
#define F_CPU 1000000L

// imitate DoxyGen to get compatible definitions.
#define __DOXYGEN__

#ifdef __ATTR_PURE__
#undef __ATTR_PURE__
#endif
#define __ATTR_PURE__

#ifdef __ATTR_CONST__
#undef __ATTR_CONST__
#endif
#define __ATTR_CONST__

// take out original sfr_defs.h header file
#define _AVR_SFR_DEFS_H_

#ifndef __SFR_OFFSET
#  if __AVR_ARCH__ >= 100
#    define __SFR_OFFSET 0x00
#  else
#    define __SFR_OFFSET 0x20
#  endif
#endif

#define _SFR_MEM16(memaddr) Registers::At16(memaddr)
#define _SFR_MEM8(memaddr) Registers::At8(memaddr)
#define _SFR_IO8(memaddr) Registers::At8((memaddr) + __SFR_OFFSET)
