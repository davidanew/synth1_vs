/*
Two sections, intialisation and run loop
run loop never exits:
	Handle midi
	Wait until sample tick and then output waveform
The sample tick is updated by TIM2 IRQ
*/

#include "main.h"

void output_sample (std::unordered_map<int, Voice>&, const uint64_t, Dac&, Filter&);
void handle_note_on(const Note_on_struct&, std::unordered_map<int, Voice>&, const Global_parameters&);

int main () {
	try
	{
		/************Tests here ******************/
		//Tests::uart();
		//Tests::uart_fast();
		//Tests::output_waveform();
		/**********End of tests *****************/	
		//Hal init always needs to be run
		Hal::init();
		//Move clock to full frequency
		Clocks::SystemClock_Config();
		//TIM2 used to to update sample clock
		Tim::init();
		//MIDI input
		Midi_in::init();
		//Dac 1 used for audio output
		//Note Dac can't be static as we are sharing the class
		Dac dac1(DAC_CHANNEL_1);
		//currently using dac channel 2 to measure run loop execution time
		Dac dac2_led(DAC_CHANNEL_2);
		//Stores last processed sample
		uint64_t sample_tick_local = 0;
		//All current voices
		std::unordered_map<int, Voice> voice_map;
		//Holds parameters that are common to all voices
		Global_parameters global_parameters;
		//TODO: Filter will need to be updated on dial change
		//what to start-up with, do we need a last state save?
		Filter filter {1000, (float)0.0};
		//TODO: Put these in a seperate function (Could be static in wave class)
		Sine::init_storage();
		Square::init_storage();
		//currently using dac channel 2 to measure run loop execution time
		dac2_led.low();
		//Set local tick value so there is not a large delta when the first
		//sample is processed
		sample_tick_local = IRQ_objects::sample_tick;
		/*main run loop, never exits*/
		while (1) {
			//TODO: Remove extra braces or move to another funtion
			{
				//On start of run loop check to see if there is midi data ready
				//If not then move straight on to voice output
				//TODO: Need to check the delay of this section 
				if (Midi_in::is_data_ready()) {
					//The recieve function also triggers the midi handling
					//The handlers are passed in as lambdas
					Midi_in::receive_byte_and_handle(
						[&](Note_on_struct note_on_struct) {
							handle_note_on(note_on_struct, voice_map, global_parameters);
						}, 
						[&](Controller_change_struct controller_change_struct) {
							//controller change code goes here
						});					
				}		
			}
			//wait for next sample tick
			while(IRQ_objects::sample_tick <= sample_tick_local) {} 
			//Indicates processing started
			dac2_led.high();
			//Reset variable for next sample
			sample_tick_local = IRQ_objects::sample_tick;	
			output_sample(voice_map, sample_tick_local, dac1, filter);
			//Indicates processing finished
			dac2_led.low();	
		}
	}
	catch (...) {
		while (1) ;
	}	
}

//Update voice map for "Note On" message 
void handle_note_on(const Note_on_struct& note_on_struct, std::unordered_map<int, Voice>& voice_map, const Global_parameters& global_parameters){
	if (note_on_struct.velocity == 0){
		//note on with zero velocity means key has been released
		voice_map.erase(1);
	} else 	{
		voice_map[1] = Voice(global_parameters, 1000, 1.0);
	}
} 
	
//This is run for every sample tick
//Outputs the sample based on voices in voice map and also uses the filter
void output_sample (std::unordered_map<int, Voice>& voice_map, const uint64_t sample_tick_local, Dac &dac1, Filter &filter)
{
	float total {0};
	//Loop though all voices and get the sample for the valid voices
	//Add these to total
	for (auto & pair : voice_map){
		//TODO: split this up to make types clearer
		total += (float) 1 * pair.second.update_and_get_sample(sample_tick_local);	
	}
	//_rel means value from 0 to 1
	const float total_rel = total * (float) 0.5 + (float) 0.5; 	
	//Calculate filtered value
	const float filtered_rel = filter.next_sample(total_rel);
	//Output the computed sample to DAC
	dac1.set_value_rel(filtered_rel);
}



