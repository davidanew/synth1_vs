/* Values that are shared between all voices*/

#ifndef PARAMETERS_H
#define PARAMETERS_H 1

#include "Wave.h"

struct Parameters {
  Wave* wave_1 {nullptr};
	Wave* wave_2 {nullptr};
  float ampl_1 {0.5};
	float ampl_2 {0.5};
	uint64_t period_in_ticks {1000};
	Parameters();
	Parameters(const Parameters &source);
	
};

#endif
