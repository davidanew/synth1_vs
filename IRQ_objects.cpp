#include "IRQ_objects.h"

volatile uint64_t IRQ_objects::sample_tick = 0;

IRQ_objects::IRQ_objects(IRQ_objects &source){
	//error on copy
	(void)source;
	while(1);//error on copy
}

IRQ_objects::IRQ_objects(){
	//error on object creation
	while(1);
}

