/*Controls sound for one keypress (and release)*/

#ifndef VOICE_H
#define VOICE_H 1

#include <memory>
#include "Global_parameters.h"
extern "C" {
	#include "stm32f4xx_hal.h"
}

//Each voice has 2 waveforms and associated parameters
class Voice {
	Global_parameters global_parameters;
	//Pointer to wave based objects
	//Dynamic ploymophism - actual waves will be Sine, Square etc
	std::shared_ptr<Wave> wave_1;
	std::shared_ptr<Wave> wave_2;
	//Frequencies for both voices
	float freq_1 {1000}	;
	float freq_2 {1000}	;
	//Shared velocity set by keypress
	float velocity {0}	;
	//Class needs to store previous sample tick value
	//The get sample funtion gets passed the current sample tick
	//So then the correct sample can be calculated
	uint64_t previous_sample_tick {0}	;
	//Used in sample calculation
	//Possibly these can be local to the method
	float phase_rel_1 {0}	;
	float phase_rel_2 {0}	;
	//How much the phase is updated per sample tick
	float phase_rel_per_tick_1 {0}	;
	float phase_rel_per_tick_2 {0}	;
public:		
	Voice(const Global_parameters&, const uint32_t&, const float&);
	Voice() = default;
	//automatic variables used for pointers, these three definitions left in for debugging
	~Voice() = default ;
    Voice(const Voice &source) = default;
	Voice& operator=(const Voice& rhs) = default;
	float update_and_get_sample(const uint64_t sample_tick);
};

#endif
