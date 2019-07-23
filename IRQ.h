/*Interrupt handlers*/

extern "C" {
	#include "stm32f4xx_hal.h"
}

#include "Dac.h"
#include "Tim.h"
#include "IRQ_objects.h"

void TIM2_IRQHandler_cpp(void);

extern "C" {
	void SysTick_Handler(void);
	void TIM2_IRQHandler(void);
}

