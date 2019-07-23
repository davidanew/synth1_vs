/*IIR filter that allows low pass and peaking*/

#ifndef FILTER_H
#define FILTER_H 1

class Filter {	
	//from http://www.eecs.umich.edu/courses/eecs206/archive/spring02/notes.dir/iir4.pdf
	/*
	x0 -- |b0> --+----------- y0
               |       |
               |       z^-1
               |       |
	             +-<a1|--|  y1
               |       |
               |       z^-1
               |       |
	             +-<a2|--|  y2
	*/
	
	//r real pole position on z plane
	//e.g. 0.85460 gives 1kHz cutoff
	//r =exp(-2*pi*(1000/40000))
	//H(Z) = b0/(1-a1*z^-1-a2*z^-2)
  //H(Z) = 1-2*r*cos(theta)+r^2 /(1 - 2*r*cos(theta)z^-1 + r^2z^-2)
	//Theta controls imaginary component of poles
	//theta = 0 gives real poles with standard low pass filter
	//Theta will be mapped to a knob as is too complex to calculate r and theta to get exacly the right response
	//see web site above for more details
	
	float x0 {0};
	float y0 {0};
	float y1 {0};
	float y2 {0};
	float a1 {0};
	float a2 {0};
	float b0 {1};
		
	//sample freq hard coded for now
	const float sample_freq {40000};
	const float pi {(float) 3.14159265359};
	
public:	
	Filter(float cutoff, float theta);
	Filter();
  [[noreturn]] Filter(Filter &source);
	float next_sample(float next_x);
};

#endif

/*

Matlab code for expermentation

t = linspace(-pi,pi,40000/1000);
x = sin(t);
y = filter (0.15, [1  -0.85], x);

%hold off
%plot (t,x)
%hold on
%plot (t,y)
%[h,w] = freqz(0.15, [1  -0.85], 1000, 'whole', 40000);
%plot ((h))
%[h,w] = freqz(0.15, [1  -0.85], 1000, 40000);
%hold off
%plot(10*log(abs(h)))
%hold on

%freqz(0.15, [1  -0.85], 1000, 40000);


% H(Z) = b0/(1-az^-1-az^-2)
% H(Z) = b0 / (1-2rcos(theta)z^-1+r^2z^-2


theta = 0;
r=0.855;

[h,w] = freqz(1-2*r*cos(theta)+r^2 , [1  -2*r*cos(theta) r^2], 1000, 40000);

plot(abs(h))
plot(mag2db(abs(h)))
plot(0:20:999*20, mag2db(abs(h)))

%plot(10 * log10 (abs(h)))
%plot(0:40:999*40, mag2db(abs(h)))

%theta = pi/20;
%theta = 0;
%r=0.85;

%freqz(1-2*r*cos(theta)+r^2, [1  -2*r*cos(theta) r^2], 1000, 40000);
r=exp(-2*pi*(1000/40000))

*/

