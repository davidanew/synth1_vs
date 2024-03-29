#include "Wave.h"

//Assign memory and ptr to hold waveform data
void Wave::set_ptr(float* &data_ptr){
	try{		
//		if (data_ptr == nullptr)
	    data_ptr = new float[num_samples];
	}
	catch(...){
		while(1);
	}	
}

Wave::Wave(){
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

void Square::init_storage(){
	Square();
}

Square::Square() {
	//memory fill only done on first use
	//pointer is static
	if (data_ptr == nullptr)
	{
		Wave::set_ptr(data_ptr);
		fill_memory();
	}
}

float*  Square::data_ptr = nullptr;

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
	if (data_ptr == nullptr)
	{
		Wave::set_ptr(data_ptr);
		fill_memory();
	}
}

void Sine::init_storage() {
	Sine();
}


float*  Sine::data_ptr = nullptr;

void Sine::fill_memory(){
	uint32_t i {0};
	for(i=0 ; i < num_samples ; i++){
		float phase_radians = (float)i/(float)num_samples  * (float) 6.28318530718;
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

void Noise::fill_memory(){
}

float Noise::get_value(float phase_rel) const {
	(void) phase_rel;
	float x = (float) -1.0 + (float) 2.0 * (float)rand()/(float)(RAND_MAX);
	return x;
}



