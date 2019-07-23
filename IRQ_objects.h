/* allow communication between main thread and IRQ handlers */

#ifndef IRQ_OBJECTS_H
#define IRQ_OBJECTS_H 1

#include "Dac.h"

//This needs to be global to allow communication between main thread and IRQ handlers
struct IRQ_objects {
	[[noreturn]] IRQ_objects(IRQ_objects &source);
	[[noreturn]] IRQ_objects();
	volatile static uint64_t sample_tick;
};

#endif