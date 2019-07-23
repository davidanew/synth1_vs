#include "Filter.h"
#include "math.h"

//See header for explanation

//Constructor only sets parameters
Filter::Filter(float cutoff, float theta){
	//const float term1 = (float)-2.0*pi*((float)cutoff/(float)sample_freq);
	//const float r = exp((float)-2.0*pi*((float)cutoff/(float)sample_freq));
	//volatile float r = pow((float)2.5,term1);
	const float r = exp((float)-2.0*pi*((float)cutoff/(float)sample_freq));
	b0 = (float)1.0-(float)2.0*r*(float)cos(theta)+(float)pow(r,(float)2.0);
	a1 = (float)2.0*r*cos(theta);
	a2 = - pow(r,(float)2.0);
}

Filter::Filter(){
	//default constructor uses default values which do no filtering
}

Filter::Filter(Filter &source){
	//error on copy
	(void)source;
	while(1);//error on copy
}

//Propogate values through filter and calculate output
float Filter::next_sample(float next_x){
	x0 = next_x;
	y2 = y1;
	y1 = y0;
	y0 = b0*x0 + a1*y1 + a2*y2;
	return y0;	
}


