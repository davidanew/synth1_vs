#include "Usart_1.h"

UART_HandleTypeDef Usart_1::huart1 = {};

void Usart_1::init(void)
{
	__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct {};
	GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 31250;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		while(1); //error
	}
}

void Usart_1::receive(uint8_t* buffer_ptr, uint16_t size) {
	HAL_UART_Receive(&huart1, buffer_ptr, size , HAL_MAX_DELAY) ;
}

bool Usart_1::is_data_ready(void){
	bool status;
	status = (((&huart1)->Instance->SR & UART_FLAG_RXNE) == UART_FLAG_RXNE);
	return status;
}

Usart_1::Usart_1(Usart_1 &source){
	//error on copy
	(void)source;
	while(1);//error on copy
}

Usart_1::Usart_1(){
	//error on object creation
	while(1);
}
