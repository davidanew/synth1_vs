#include "IRQ.h"

//On TIM2 IRQ update sample tick
void TIM2_IRQHandler_cpp(void){
	IRQ_objects::sample_tick++;
	HAL_TIM_IRQHandler(&(Tim::htim2));
}

//Actual handlers need to be in C

extern "C" {
	void SysTick_Handler(void)
	{
		HAL_IncTick();
	}
		
	void TIM2_IRQHandler(void)
	{
		TIM2_IRQHandler_cpp();
	}
}




