/* Values that are shared between all voices*/

#ifndef GLOBAL_PARAMETERS_H
#define GLOBAL_PARAMETERS_H 1

#include "Wave.h"

enum wave_type {square_wave, sine_wave};
struct Global_parameters {
//	Wave* wave_1 {nullptr}	;
//	Wave* wave_2 {nullptr}	;
	wave_type wave_1 {sine_wave};
	wave_type wave_2 {sine_wave};
	float ampl_1 {0.5};
	float ampl_2 {0.5};
	float sample_tick_freq {40000};
	uint64_t period_in_ticks {1000};
//	Parameters() = default;
//	Parameters(const Parameters &source) = default;
//	Parameters& operator=(const Parameters &rhs) {
//		wave_1 = rhs.wave_1;
//		wave_2 = rhs.wave_2;
//		ampl_1 = rhs.ampl_1;
//		ampl_2 = rhs.ampl_2;
//		period_in_ticks = rhs.period_in_ticks;
//		return *this;
//	};
};

#endif
