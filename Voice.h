/*Controls sound for one keypress (and release)*/

#ifndef VOICE_H
#define VOICE_H 1

#include "Parameters.h"

extern "C" {
	#include "stm32f4xx_hal.h"
}

class Voice {
	Parameters parameters;
	float freq_1 {1000};
	float freq_2 {1000};
	float velocity {0};
	//float period_1_in_ticks {1000000};
	//float period_2_in_ticks {1000000};	
	uint64_t previous_sample_tick {0};
	float phase_rel_1 {0};
	float phase_rel_2 {0};
	float phase_rel_per_tick_1 {0};
	float phase_rel_per_tick_2 {0};
	
public:		
	Voice(const float sample_tick_freq, const Parameters &parameters_arg, uint32_t freq, const float &velocity_arg);
	Voice() = default;
    Voice(const Voice &source) = default;
	~Voice() = default;
	float get_value(const uint64_t sample_tick);
//TODO: delete if not needed
	bool operator<(const Voice& rhs) {return true;}
	bool operator==(const Voice& rhs) { return true; }


};

#endif
