/* Values that are shared between all voices*/

#ifndef GLOBAL_PARAMETERS_H
#define GLOBAL_PARAMETERS_H 1

#include "Wave.h"

enum wave_type {square_wave, sine_wave};
struct Global_parameters {
	wave_type wave_1_type {square_wave};
	wave_type wave_2_type {square_wave};
	float ampl_1 {0.5};
	float ampl_2 {0.5};
	float sample_tick_freq {40000};
	uint64_t period_in_ticks {1000};
};

#endif
