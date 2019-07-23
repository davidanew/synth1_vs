/*This sets up and outputs values to the DAC*/

#ifndef DAC_H
#define DAC_H 1
extern "C" {
	#include "stm32f4xx_hal.h"
}

class Dac {
	//Used by Hal code
	DAC_HandleTypeDef hdac {};
	uint32_t channel = DAC_CHANNEL_1;
	bool init_done = false;

public:	
	Dac(uint32_t channel_arg); 
  [[noreturn]] Dac(Dac &source);
  void set_value_rel(float value_rel);
  void set_value(uint32_t value_rel);
	void high();
	void low();
	uint32_t get_value();
	void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac_arg);	
};

#endif

