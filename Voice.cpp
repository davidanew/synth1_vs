#include "Voice.h"


Voice::Voice(const Global_parameters& global_parameters, const uint32_t& freq, const float &velocity_arg)
	: global_parameters(global_parameters)
{
	//TODO: These frequencies need to be seperate or have offsets
	voice_parameters.freq_1 = freq;
	voice_parameters.freq_2 = freq;
	voice_parameters.velocity = velocity_arg;
	voice_parameters.phase_rel_per_tick_1 = voice_parameters.freq_1 / global_parameters.sample_tick_freq;
	voice_parameters.phase_rel_per_tick_2 = voice_parameters.freq_2 / global_parameters.sample_tick_freq;
	try {
		//TODO: These will also need to be set with dial
		//make sure deconstructed properly when changed
		//TODO: this will be passed in parameters
		//TODO: the waves need to be initialised
		//wave_1 = new Sine();
		//wave_2 = new Sine();		
		std::shared_ptr<Sine> wave_1_temp { new Sine() };
		std::shared_ptr<Sine> wave_2_temp { new Sine() };
		wave_1 = wave_1_temp;
		wave_2 = wave_2_temp;
	}
	catch (...) {
		while (1) ;
	}
}

//Voice::~Voice()
//{
//	//TODO maybe unique_ptr can do all this
//	//try when all this is working
//	delete wave_1;
//	delete wave_2;
//}
//Voice::Voice(const Voice &source)
//{
//	
//}
//Voice::Voice& operator=(const Voice& rhs)
//{
//}

float Voice::update_and_get_sample(const uint64_t sample_tick) {
	//coded to prevent costly int to float conversion and fmod
	//allows recovery from missed sample ticks
	if(voice_parameters.previous_sample_tick == 0) {
		//Set this so there is not a long delay due to the first sample
		voice_parameters.previous_sample_tick = sample_tick;
	}
	//Get to current sample tick,
	//updating phase each time
	//current phase being considered is held in
	//phase_rel_*
	while(sample_tick > voice_parameters.previous_sample_tick) {
		voice_parameters.phase_rel_1 += voice_parameters.phase_rel_per_tick_1;
		if (voice_parameters.phase_rel_1 > (float) 1.0) 
			voice_parameters.phase_rel_1 -= 1;
		voice_parameters.phase_rel_2 += voice_parameters.phase_rel_per_tick_2;
		if (voice_parameters.phase_rel_2 > (float) 1.0) 
			voice_parameters.phase_rel_2 -= 1;
		voice_parameters.previous_sample_tick += 1;
	}
	//Previous_sample_tick will now be set to the current sample tick
	//The function should not be called until the next tick, but it doesn't matter if
	//it is called earlier
	//Calculate the sample from the two waveforms and return value
	return (float)(wave_1->get_value(voice_parameters.phase_rel_1) * global_parameters.ampl_1 + 
					wave_2->get_value(voice_parameters.phase_rel_2) * global_parameters.ampl_2)
	                * voice_parameters.velocity;
}	
