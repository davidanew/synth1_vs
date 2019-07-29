#include "Tests.h"

//TODO: need to try quick read

void Tests::uart(void) {
  //testing code
	Hal::init();
	//MIDI input
	Usart_1::init();
	//Virtual com port
	Usart_2_vcom::init();
	//Buffer used for recieve and transmit
	uint8_t buffer_arr[1] = {'X'};
	//Output midi to com port
	while (1){
		Usart_1::receive(buffer_arr, sizeof(buffer_arr));
		Usart_2_vcom::transmit(buffer_arr, sizeof(buffer_arr));
	}
}

void Tests::uart_fast(void) {
  //testing code
	Hal::init();
	//MIDI input
	Usart_1::init();
	//Virtual com port
	Usart_2_vcom::init();
	//Buffer used for recieve and transmit
	uint8_t buffer_arr[1] = {'X'};
	//Output midi to com port
	while (1){
		while (!Usart_1::is_data_ready());
		Usart_1::receive(buffer_arr, sizeof(buffer_arr));
		Usart_2_vcom::transmit(buffer_arr, sizeof(buffer_arr));
	}
}


void Tests::output_waveform() {
	Hal::init();
	Tim::init();
	Dac dac1(DAC_CHANNEL_1);
	uint64_t sample_tick_local = 0;
	std::unordered_map<int, Voice> voice_map;
	Global_parameters global_parameters;
	//Filter filter {1000,(float)0.0};
	Clocks::SystemClock_Config();
	try{
		voice_map[1] = Voice(global_parameters, 1000, 1.0);
	}
	catch(...){
		while(1);
	}	
	sample_tick_local = IRQ_objects::sample_tick;
	while(1){
		while (IRQ_objects::sample_tick <= sample_tick_local);
		sample_tick_local = IRQ_objects::sample_tick;
		float total {0};
		for(auto & pair : voice_map) {
			total += (float) 1 * pair.second.update_and_get_sample(sample_tick_local);	
		}
		const float total_rel = total * (float) 0.5 + (float) 0.5; 	
		//const float filtered_rel = filter.next_sample(total_rel);
		dac1.set_value_rel(total_rel);
	}
}

Tests::Tests(Tests &source){
	(void)source;
	while(1);//error on copy
}

Tests::Tests(){
	//error on object creation
	while(1);
}


