#include "StdAfx.h"
#include "Arduino.h"

// Faking time
static unsigned long g_ticks = 0;

unsigned long millis()
{
	g_ticks += 13;
	return g_ticks;
}

unsigned long micros()
{
	g_ticks += 133;
	return g_ticks;
}