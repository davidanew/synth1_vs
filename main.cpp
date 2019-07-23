/*
Two sections, intialisation and run loop
run loop never exits and execution of each pass is delayed until the next sample tick
The sample tick is updated by TIM2 IRQ
The sample is output at the end of the run loop
This could cause some jitter should be too small to
be audible
*/

#include "main.h"

//One voice for each key press
//TODO: move voice bank to cpp vector and put this in main
const uint32_t num_voices {16};

void output_sample (std::unordered_map<int, Voice>& voice_map, const uint64_t sample_tick_local, Dac &dac1, Filter &filter);

int main () {
	try
	{
	
		/************Tests here ******************/
		//Tests::uart();
		//Tests::uart_fast();
		//Tests::original_main();
		/**********End of tests *****************/
	
		//Hal init always needs to be run
		Hal::init();
		//TIM2 used to to update sample clock
		Tim::init();
		//MIDI input
		Usart_1::init();
		//Dac 1 used for audio output
		//Note Dac can't be static as we are sharing the class
		Dac dac1(DAC_CHANNEL_1);
		//currently using dac channel 2 to measure run loop execution time
		Dac dac2_led(DAC_CHANNEL_2);
		//Stores last processed sample
		uint64_t sample_tick_local = 0;
		//All current voices, uses dynamic binding
		//Voice* voice_array[num_voices] = {nullptr};
		std::unordered_map<int, Voice> voice_map;
		//Holds parameters that are common to all voices
		Parameters parameters;
		//TODO: Filter will need to be updated on dial change
		//what to stat-up with, do we need a last state save?
		Filter filter {1000, (float)0.0}
		;
		//Move clock to full frequency
		Clocks::SystemClock_Config();
	
		try {
			//TODO: These will also need to be set with dial
			//make sure deconstructed properly when changed
			parameters.wave_1 = new Sine();
			parameters.wave_2 = new Sine();		
			//voice_array[0] = new Voice(40000,parameters, 1000, 1.0);
		}
		catch (...) {
			while (1) ;
		}	
		//currently using dac channel 2 to measure run loop execution time
		dac2_led.low();
		//Set local tick value so there is not a large delta when the first
		//sample is processed
		sample_tick_local = IRQ_objects::sample_tick;
		/*main run loop, never exits*/
		while (1) {
			{
				//handle midi
				if (Usart_1::is_data_ready()) {

					if (voice_map.find(1) == voice_map.end()) {
						voice_map[1] = Voice(40000, parameters, 1000, 1.0);
						//voice_map.emplace(40000,parameters, 1000, 1.0)
					}

				}		
			}
			//wait for next sample tick
			while(IRQ_objects::sample_tick <= sample_tick_local) {} 
			//Indicates processing started
			dac2_led.high();
			//Reset variable for next sample
			sample_tick_local = IRQ_objects::sample_tick;	
			output_sample(voice_map, sample_tick_local, dac1, filter);		
			dac2_led.low();	
		}
	}
	catch (...) {
		while (1) ;
	}	
	
	
}



//TODO: put in side effect warning
void output_sample (std::unordered_map<int, Voice>& voice_map, const uint64_t sample_tick_local, Dac &dac1, Filter &filter)
{
	//uint32_t i {0};
	float total {0};
	//Loop though all voices and get the sample for the valid voices
	//Add to total output value
	//
	//for (i=0 ; i<num_voices ; i++){
	//	if (voice_array[i] != nullptr) {
	//		total += (float) 1 * voice_array[i]->get_value(sample_tick_local);
	//	}
	//}
	
	for (auto & pair : voice_map){
		total += (float) 1 * pair.second.get_value(sample_tick_local);	
	}
	
	//std::unordered_map<int, Voice>::iterator my_iter = voice_map.begin();

	//_rel means value from 0 to 1
	const float total_rel = total * (float) 0.5 + (float) 0.5; 	
	const float filtered_rel = filter.next_sample(total_rel);
	//Output the computed sample to DAC
	dac1.set_value_rel(filtered_rel);
}
