/* Usart2 is connected to the virtual com port
 * So this class is used to send messages that can be 
 * seen on a PC terminal*/

#ifndef USART_2_VCOM_H
#define USART_2_VCOM_H 1

#include "stm32f4xx_hal.h"

class Usart_2_vcom {
	//Holds data for HAL
	static UART_HandleTypeDef huart2 ;
	public:
	static void init(void);
  static void transmit(uint8_t* buffer_ptr, uint16_t size);
	[[noreturn]] Usart_2_vcom(Usart_2_vcom &source);
	[[noreturn]] Usart_2_vcom();
};

#endif
