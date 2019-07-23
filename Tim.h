/*This sets up the TIM2 timer*/

#ifndef TIM_H
#define TIM_H 1

extern "C" {
	#include "stm32f4xx_hal.h"
}

class Tim {
public:
	static TIM_HandleTypeDef htim2;
  [[noreturn]] Tim(Tim &source);
	static void init(void);
	static void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base);
	static uint64_t sample_tick_us();
};

#endif
