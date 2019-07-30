#ifndef USART_1_H
#define USART_1_H 1

#include "stm32f4xx_hal.h"

class Usart_1 {
	static UART_HandleTypeDef huart1 ;
public:
	static void init (void);
	static void receive(uint8_t* buffer_ptr, uint16_t size);
	static bool is_data_ready();
	[[noreturn]] Usart_1(Usart_1 &source);
	[[noreturn]] Usart_1();
};


enum Midi_state { wait_status_byte, wait_note_number, wait_velocity, wait_controller_number, wait_controller_data };
//enum Status_message { note_on, control_change, unsuppoted_status_byte , not_status_byte };


class Midi_in : public Usart_1 {
	static Midi_state state;
	static void handle_midi_byte(uint8_t);
	static Midi_state get_next_state_from_status_byte(uint8_t);
	static bool is_status_byte(uint8_t);
public:
	static void receive_byte_and_handle(void);
};

#endif
