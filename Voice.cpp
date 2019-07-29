#include "Voice.h"

Voice::Voice(const Global_parameters& global_parameters, const uint32_t& freq, const float &velocity)
	: global_parameters(global_parameters), freq_1 (freq), freq_2 (freq), velocity(velocity)
{
	//TODO: These frequencies need to be seperate or have offsets

	phase_rel_per_tick_1 = freq_1 / global_parameters.sample_tick_freq;
	phase_rel_per_tick_2 = freq_2 / global_parameters.sample_tick_freq;
	try {
		//TODO: These will also need to be set with dial

		switch(global_parameters.wave_1_type) {
		case sine_wave :
			wave_1 = std::shared_ptr<Wave> { new Sine() };
			break;       
		default:
			wave_1 = std::shared_ptr<Wave> { new Square() };
			break;
		}
		switch(global_parameters.wave_2_type) {
		case sine_wave :
			wave_2 = std::shared_ptr<Wave> { new Sine() };
			break;       
		default:
			wave_2 = std::shared_ptr<Wave> { new Square() };
			break;
		}
	}
	catch (...) {
		while (1) ;
	}
}

float Voice::update_and_get_sample(const uint64_t sample_tick) {
	//coded to prevent costly int to float conversion and fmod
	//allows recovery from missed sample ticks
	if(previous_sample_tick == 0) {
		//Set this so there is not a long delay due to the first sample
		previous_sample_tick = sample_tick;
	}
	//Get to current sample tick,
	//updating phase each time
	//current phase being considered is held in
	//phase_rel_*
	while(sample_tick > previous_sample_tick) {
		phase_rel_1 += phase_rel_per_tick_1;
		if (phase_rel_1 > (float) 1.0) 
			phase_rel_1 -= 1;
		phase_rel_2 += phase_rel_per_tick_2;
		if (phase_rel_2 > (float) 1.0) 
			phase_rel_2 -= 1;
		previous_sample_tick += 1;
	}
	//Previous_sample_tick will now be set to the current sample tick
	//The function should not be called until the next tick, but it doesn't matter if
	//it is called earlier
	//Calculate the sample from the two waveforms and return value
	return (float)(wave_1->get_value(phase_rel_1) * global_parameters.ampl_1 + 
					wave_2->get_value(phase_rel_2) * global_parameters.ampl_2)
	                * velocity;
}	
