#include "stm32f4xx_hal.h"

#ifndef CLOCKS_H
#define CLOCKS_H 1

class Clocks {
public:
	static void SystemClock_Config(void);
	[[noreturn]] Clocks(Clocks &source);
	[[noreturn]] Clocks();
};

#endif

