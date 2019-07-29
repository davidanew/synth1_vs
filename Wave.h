/*Handles sythesiser waveforms, e.g. sine, square
Wavefroms are calculted and written to memory on initialisation*/ 

extern "C" {
	#include "stm32f4xx_hal.h"
}
#include <math.h>
#include <stdlib.h>

//Base class has all funtions but does not have a pointer to the wavefrom data
//This data needs to be static for each type of waveform
//So this pointer is sent back to base class functions

class Wave {
protected:
	const uint32_t num_samples {4000};
	virtual void fill_memory() =0;
	virtual float get_value_wptr(float* data_ptr, float phase_rel) const ;
	void set_ptr(float* &data_ptr);

public:
	Wave();
	[[noreturn]] Wave(Wave &wave);
	virtual float get_value(float phase_rel) const =0;
};

class Square : public Wave {
	void fill_memory();
	static float* data_ptr;
public:
	Square();	
	static void init_storage();

	float get_value(float phase_rel) const;
};

class Sine : public Wave{
	void fill_memory();
	static float* data_ptr;
public:
	Sine();	
	static void init_storage();
	float get_value(float phase_rel) const;
};

class Noise : public Wave{
	void fill_memory();
	static float* data_ptr;
public:
	Noise();	
	float get_value(float phase_rel) const;
};



