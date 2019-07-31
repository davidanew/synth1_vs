#ifndef USART_1_H
#define USART_1_H 1

#include "stm32f4xx_hal.h"
#include <functional>
#include "Shared_structs.h"

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

class Midi_in : public Usart_1 {
	static Midi_state state;
	static Note_on_struct note_on_struct;
	static Controller_change_struct controller_change_struct;
	//static uint8_t note_number;
	//static uint8_t velocity;
	//static uint8_t controller_number;
	//static uint8_t controller_data;
	static void handle_midi_byte(uint8_t , std::function<void(Note_on_struct)> , std::function<void(Controller_change_struct)> );
	static Midi_state get_next_state_from_status_byte(uint8_t);
	static bool is_status_byte(uint8_t);
public:
	static void receive_byte_and_handle(std::function<void(Note_on_struct)>, std::function<void(Controller_change_struct)>);
};

#endif
