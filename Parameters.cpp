#include "Parameters.h"

Parameters::Parameters()
  //Type of wave for each oscillator
	:wave_1(nullptr),
	wave_2(nullptr),
	//Amplitude for each oscillator
	ampl_1(0.5),
	ampl_2(0.5),
  period_in_ticks(1000){	
}

//Copy constructor. Voice class uses this as it takes a local copy
Parameters::Parameters(const Parameters &source)
	:wave_1(source.wave_1),
	wave_2(source.wave_2),
	ampl_1(source.ampl_1),
	ampl_2(source.ampl_2),
  period_in_ticks(source.period_in_ticks){	
}
	

