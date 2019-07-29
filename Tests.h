#include "Dac.h"
#include "Tim.h"
#include "Hal.h"
#include "IRQ_objects.h"
#include "Voice.h"
#include "Global_parameters.h"
#include "Filter.h"
#include "Hal.h"
#include "Usart_1.h"
#include "Usart_2_vcom.h"
#include "Clocks.h"
#include <unordered_map>


class Tests {
public:
	static void uart(void);
	static void uart_fast(void);
	static void output_waveform(void);
	[[noreturn]] Tests(Tests &source);
	[[noreturn]] Tests();

};

