#include "Voice.h"

Voice::Voice(const float sample_tick_freq, const Parameters &parameters_arg, uint32_t freq, const float &velocity_arg)
	: parameters(parameters_arg)
//TODO: These frequencies need to be seperate or have offsets
  , freq_1(freq)
  , freq_2(freq)
	, velocity(velocity_arg){
	phase_rel_per_tick_1 = freq_1/sample_tick_freq;
	phase_rel_per_tick_2 = freq_2/sample_tick_freq;
}

/*
Voice::Voice(Voice &source){
	//error on copy
	(void)source;
	while(1);//error on copy
}


//TODO: think about parameters de-init - should be ok not to handle here
Voice::~Voice(){
	//Not needed
	//Pointer to voices is handled in parameters
}
*/

//rename to get_sample
float Voice::get_value(const uint64_t sample_tick) {
	//coded to prevent costly int to float conversion and fmod
	//allows recovery from missed sample ticks
	if (previous_sample_tick == 0) {
		//Set this so there is not a long delay due to the first sample
		previous_sample_tick = sample_tick;
	}
	//Get to current sample tick,
	//updating phase each time
	//current phase being considered is held in
	//phase_rel_*
	while (sample_tick > previous_sample_tick){
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
	return (float) (parameters.wave_1->get_value(phase_rel_1) * parameters.ampl_1 + 
									parameters.wave_2->get_value(phase_rel_2) * parameters.ampl_2)
	                * velocity;
}	
