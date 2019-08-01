#include "Usart_1.h"

UART_HandleTypeDef Usart_1::huart1 = {};

//Initialisation code from cube mx
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

//This can be polled and when data is ready the call the receive function
//Becuase if you call the HAL function without data it will wait for the data and stall the whole program
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

//First step in midi read is to get the status byte
Midi_state Midi_in::state = {wait_status_byte};

Note_on_struct Midi_in::note_on_struct = {};
Controller_change_struct Midi_in::controller_change_struct = {};

//See https://www.songstuff.com/recording/article/midi_message_format/

//Waits for one byte from uart input (though this should only be called when data is ready
//handing done by sub procedure
void Midi_in::receive_byte_and_handle(std::function<void(Note_on_struct)> note_on_handler, std::function<void(Controller_change_struct)> controller_change_handler) {
	uint8_t buffer_arr[1] {0};
	receive(buffer_arr, 1);
	handle_midi_byte(buffer_arr[0], note_on_handler, controller_change_handler);
}

//Handle the recieved midi byte. FSM state is updated and appropriate midi data holding structs
//When the full message is recieved (3 bytes) then one of the supplied funtions is run
void Midi_in::handle_midi_byte(uint8_t midi_byte, std::function<void(Note_on_struct)> note_on_handler, std::function<void(Controller_change_struct)> controller_change_handler) {
	switch (state) {
	case (wait_status_byte): 
		if (is_status_byte(midi_byte))
			//Setting next state
			state = get_next_state_from_status_byte(midi_byte);
		else 
			//do nothing
			state = wait_status_byte;
		break;
	case (wait_note_number):
		//We can handle a new status message from any state 
		if (is_status_byte(midi_byte))
			state = get_next_state_from_status_byte(midi_byte);
		else 
			//If it isn't a stutus byte assume it is valid dats
			note_on_struct.note_number = midi_byte;
			state = wait_velocity;
		break;
	case (wait_controller_number):
		if (is_status_byte(midi_byte))
			state = get_next_state_from_status_byte(midi_byte);
		else 
			controller_change_struct.controller_number = midi_byte;
			state = wait_controller_data;
		break;
	case (wait_velocity):
		if (is_status_byte(midi_byte))
			state = get_next_state_from_status_byte(midi_byte);
		else {
			//The final part of the message for Note On
			note_on_struct.velocity = midi_byte;
			note_on_handler(note_on_struct);
			state = wait_status_byte;			
		}
		break;
	case (wait_controller_data):
		if (is_status_byte(midi_byte))
			state = get_next_state_from_status_byte(midi_byte);
		else {
			//The final part of the message for Controller Change
			controller_change_struct.controller_data = midi_byte;
			controller_change_handler(controller_change_struct);
			state = wait_status_byte;
		}
		break;
	default:
		state = wait_status_byte;
		break;
	}		
}

Midi_state Midi_in::get_next_state_from_status_byte(uint8_t midi_byte){
	if (is_status_byte(midi_byte)) {
		if((midi_byte & 0xF0)  == 0x90 ) return wait_note_number; //it was note on
		else if((midi_byte & 0xB0 ) == 0xB0) return wait_controller_number; //it was a controller change
		else return wait_status_byte; //unsupported status byte
	}
	else return wait_status_byte;
}

bool Midi_in::is_status_byte(uint8_t midi_byte) {
	return ((midi_byte & 1 << 7) == (1 << 7));
}