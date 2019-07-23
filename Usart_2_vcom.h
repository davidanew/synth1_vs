#ifndef USART_2_VCOM_H
#define USART_2_VCOM_H 1

#include "stm32f4xx_hal.h"

class Usart_2_vcom {
	static UART_HandleTypeDef huart2 ;
	public:
	static void init(void);
  static void transmit(uint8_t* buffer_ptr, uint16_t size);
	[[noreturn]] Usart_2_vcom(Usart_2_vcom &source);
	[[noreturn]] Usart_2_vcom();
};

#endif
