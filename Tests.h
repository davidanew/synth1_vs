#include "Dac.h"
#include "Tim.h"
#include "Hal.h"
#include "IRQ_objects.h"
#include "Voice.h"
#include "Parameters.h"
#include "Filter.h"
#include "Hal.h"
#include "Usart_1.h"
#include "Usart_2_vcom.h"
#include "Clocks.h"

class Tests {
public:
	static void uart(void);
	static void uart_fast(void);
	static void original_main(void);
	[[noreturn]] Tests(Tests &source);
	[[noreturn]] Tests();

};
