/*
USART1 is used for inputting the midi data
Usart_1 Class can be used for this
Midi_in is a derivitive of this class and is the class used by main()
 */

#ifndef USART_1_H
#define USART_1_H 1

#include "stm32f4xx_hal.h"
#include <functional>
#include "Shared_structs.h"

class Usart_1 {
	//Struct for use with HAL
	static UART_HandleTypeDef huart1 ;
public:
	static void init (void);
	static void receive(uint8_t* buffer_ptr, uint16_t size);
	static bool is_data_ready();
	[[noreturn]] Usart_1(Usart_1 &source);
	[[noreturn]] Usart_1();
};

//This is used for a finite state machine
enum Midi_state { wait_status_byte, wait_note_number, wait_velocity, wait_controller_number, wait_controller_data };

class Midi_in : public Usart_1 {
	//Current FSM state state
	static Midi_state state;
	//If a Note On midi byte is recieved then this struct is filled with the note data
	//It is sent to the approiate handler when filled
	static Note_on_struct note_on_struct;
	//As above but for a controller change
	static Controller_change_struct controller_change_struct;
	static void handle_midi_byte(uint8_t , std::function<void(Note_on_struct)> , std::function<void(Controller_change_struct)> );
	static Midi_state get_next_state_from_status_byte(uint8_t);
	static bool is_status_byte(uint8_t);
public:
	static void receive_byte_and_handle(std::function<void(Note_on_struct)>, std::function<void(Controller_change_struct)>);
};

#endif
