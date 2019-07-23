#include "Dac.h"

//Initailise DAC 
Dac::Dac(uint32_t channel_arg) {
	channel = channel_arg;
	DAC_ChannelConfTypeDef sConfig {};
	hdac.Instance = DAC;
	hdac.State = HAL_DAC_STATE_RESET;
  //Normally this is a call back, but this is not oo
	//So manually call member funtion here
	//Standard call back will do nothing
	HAL_DAC_MspInit(&hdac);				
	if (HAL_DAC_Init(&hdac) != HAL_OK)
	{
		while(1);
	}
	sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
	sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
	if (HAL_DAC_ConfigChannel(&hdac, &sConfig, channel) != HAL_OK)
	{
		while(1);
	}
	if (HAL_DAC_Start(&hdac , channel) != HAL_OK)
	{
		while(1);
	}
	init_done = true;
}	

Dac::Dac(Dac &source){
	//error on copy
	(void)source;
	while(1);//error on copy
}

//Output value to DAC with value 0->1
void Dac::set_value_rel(float value_rel){
	//if (value_rel <(float)-1.0 || value_rel > (float) 1.0) 
	//	while(1);
	if (value_rel > (float) 1.0)
		value_rel = 1.0;
	if (value_rel < (float) -1.0)
		value_rel = -1.0;
	uint32_t dac_value = (uint32_t) ((float) 0xFFF * value_rel );
	/*
	if (HAL_DAC_SetValue(&hdac, channel, DAC_ALIGN_12B_R, dac_value) != HAL_OK || init_done == false){
		while(1);
	}
	*/
	set_value(dac_value);
}

//Output value to dac with real value
void Dac::set_value(uint32_t value){
//	uint32_t dac_value = value;
	if (value > 0xFFF)
		while(1);
	if (HAL_DAC_SetValue(&hdac, channel, DAC_ALIGN_12B_R, value) != HAL_OK || init_done == false){
		while(1);
	}
}

void Dac::high(){
	if (HAL_DAC_SetValue(&hdac, channel, DAC_ALIGN_12B_R, 0xFFF) != HAL_OK || init_done == false){
		while(1);
	}
}

void Dac::low(){
	if (HAL_DAC_SetValue(&hdac, channel, DAC_ALIGN_12B_R, 0x000) != HAL_OK || init_done == false){
		while(1);
	}
}

//Read value that the DAC is currently outputting
uint32_t Dac::get_value(){
	return HAL_DAC_GetValue ( &hdac , channel);
}

//Standard init function as member function, not C call back
void Dac::HAL_DAC_MspInit(DAC_HandleTypeDef* hdac_arg)
{
	GPIO_InitTypeDef GPIO_InitStruct {}; //= {0};
	if(hdac_arg->Instance==DAC)
	{
		__HAL_RCC_DAC_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		
		if (this->channel == DAC_CHANNEL_1)
		  GPIO_InitStruct.Pin = GPIO_PIN_4;
		else if (this->channel == DAC_CHANNEL_2)
			GPIO_InitStruct.Pin = GPIO_PIN_5;
		else //error
			while(1);
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
}
