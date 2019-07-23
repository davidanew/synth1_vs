#include "Wave.h"

//Assign memory and ptr to hold waveform data
void Wave::set_ptr(float* &data_ptr){
	try{		
		if (data_ptr == nullptr)
	    data_ptr = new float[num_samples];
	}
	catch(...){
		while(1);
	}	
}

Wave::Wave(){
}
//Not deallocating waveforms as they are always needed
Wave::~Wave(){
}

Wave::Wave(Wave &source){//error on copy
	(void)source;
	while(1);
}

//Set the sample from memory based on the phase value (range 0 to 1)
float Wave::get_value_wptr(float* data_ptr, float phase_rel) const {
	uint32_t location = uint32_t (phase_rel * (float) (num_samples-1));
	if (location < num_samples){
		return data_ptr[location];
	}
	else //error
		while(1);
}

Square::Square(){
	Wave::set_ptr(data_ptr);
	fill_memory();
}

float*  Square::data_ptr = nullptr;
Square::~Square(){
}

//Fill memory with square waves
void Square::fill_memory(){
	uint32_t i {0};
	for(i=0 ; i < (num_samples/2) ; i++){
		data_ptr[i] = 1.0;	
	}
	for(i=num_samples/2 ; i < num_samples ; i++){
		data_ptr[i] = -1.0;	
	}	
}

//Get sample using base funtion
float Square::get_value(float phase_rel) const {
		return Wave::get_value_wptr(data_ptr,phase_rel);
}

Sine::Sine(){
	Wave::set_ptr(data_ptr);
	fill_memory();
}

float*  Sine::data_ptr = nullptr;

Sine::~Sine(){
}

void Sine::fill_memory(){
	uint32_t i {0};
	for(i=0 ; i < num_samples ; i++){
		float phase_radians = (float)i/(float)num_samples  * (float) 6.28318530718;
		//uint32_t value = (uint32_t) ((float)0xFFF*(0.5+0.5*sin(phase_radians)));
		float value = (float) sin(phase_radians);
		data_ptr[i] = value;	
	}
}


float Sine::get_value(float phase_rel) const {
	return Wave::get_value_wptr(data_ptr,phase_rel);
}

Noise::Noise(){
}

float*  Noise::data_ptr = nullptr;

Noise::~Noise(){
}

void Noise::fill_memory(){
}

float Noise::get_value(float phase_rel) const {
	(void) phase_rel;
	float x = (float) -1.0 + (float) 2.0 * (float)rand()/(float)(RAND_MAX);
	return x;
}



