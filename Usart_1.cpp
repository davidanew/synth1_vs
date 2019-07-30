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

Midi_state Midi_in::state = {wait_status_byte};

//TODO: maybe pass handler in here
void Midi_in::receive_byte_and_handle() {
	uint8_t buffer_arr[1] {0};
	receive(buffer_arr, 1);
	handle_midi_byte(buffer_arr[0]);
}

//enum Midi_state { wait_status_byte, wait_note_number, wait_velocity, wait_controller_number, wait_controller_data };

void Midi_in::handle_midi_byte(uint8_t midi_byte) {
	switch (state) {
	case (wait_status_byte): 
		if (is_status_byte(midi_byte))
			state = get_next_state_from_status_byte(midi_byte);
		else 
			state = wait_status_byte;
		break;
	case (wait_note_number):
		if (is_status_byte(midi_byte))
			state = get_next_state_from_status_byte(midi_byte);
		else 
			state = wait_velocity;
		break;
	case (wait_controller_number):
		if (is_status_byte(midi_byte))
			state = get_next_state_from_status_byte(midi_byte);
		else 
			state = wait_controller_data;
		break;
	case (wait_velocity):
		if (is_status_byte(midi_byte))
			state = get_next_state_from_status_byte(midi_byte);
		else 
			state = wait_status_byte;
			//handle note
		break;
	case (wait_controller_data):
		if (is_status_byte(midi_byte))
			state = get_next_state_from_status_byte(midi_byte);
		else 
			state = wait_status_byte;
			//handle controller data
		break;
	default:
		state = wait_status_byte;
		break;
	}		
}

//enum Status_message { note_on,  control_change, unsuppoted_status_byte , not_status_byte };

//See https://www.songstuff.com/recording/article/midi_message_format/
Midi_state Midi_in::get_next_state_from_status_byte(uint8_t midi_byte){
	if ((midi_byte & 1 << 7) == (1 << 7)) {
		//it is a status byte
		if((midi_byte & 9 << 4) == (9 << 4)) return wait_note_number; //it was note on
		else if((midi_byte & 0xB << 4) == (0xB << 4)) return wait_controller_number; //it controller change
		else return wait_status_byte; //unsupported status byte
	}
	else return wait_status_byte;
}

bool is_status_byte(uint8_t midi_byte) {
	return ((midi_byte & 1 << 7) == (1 << 7));
}