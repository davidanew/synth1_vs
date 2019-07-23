#include "Usart_2_vcom.h"

UART_HandleTypeDef Usart_2_vcom::huart2 = {};

void Usart_2_vcom::init(void)
{
  __HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct {};
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200 ;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		//Error_Handler();
		while(1);
	}
}

void Usart_2_vcom::transmit(uint8_t* buffer_ptr, uint16_t size) {
	HAL_UART_Transmit(&huart2, buffer_ptr, size, HAL_MAX_DELAY );
}

Usart_2_vcom::Usart_2_vcom(Usart_2_vcom &source){
	//error on copy
	(void)source;
	while(1);//error on copy
}

Usart_2_vcom::Usart_2_vcom(){
	//error on object creation
	while(1);
}
