
// default mcu
#define __AVR_ATmega1284__

// assume 1MHz
#define F_CPU 1000000L
//#define F_CPU 20000000L

// imitate DoxyGen to get compatible definitions.
#define __DOXYGEN__

#ifdef __ATTR_PURE__
#undef __ATTR_PURE__
#endif
#define __ATTR_PURE__
