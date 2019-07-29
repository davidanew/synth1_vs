/*Controls sound for one keypress (and release)*/

#ifndef VOICE_H
#define VOICE_H 1

#include <memory>
#include "Global_parameters.h"
extern "C" {
	#include "stm32f4xx_hal.h"
}

class Voice {
	Global_parameters global_parameters;
	std::shared_ptr<Wave> wave_1;
	std::shared_ptr<Wave> wave_2;
	float freq_1 {1000}	;
	float freq_2 {1000}	;
	float velocity {0}	;
	uint64_t previous_sample_tick {0}	;
	float phase_rel_1 {0}	;
	float phase_rel_2 {0}	;
	float phase_rel_per_tick_1 {0}	;
	float phase_rel_per_tick_2 {0}	;
public:		
	Voice(const Global_parameters&, const uint32_t&, const float&);
	Voice() = default;
	~Voice() = default ;
    Voice(const Voice &source) = default;
	Voice& operator=(const Voice& rhs) = default;
	float update_and_get_sample(const uint64_t sample_tick);
};

#endif
