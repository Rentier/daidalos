#include "clocks.h"

#include <xdc/runtime/System.h>

#include "led.h"

Void clock_mainloop_func(UArg arg0) {
	System_printf("enter clock_mainloop_func\n");

	toggle_led();

	System_printf("exit clock_mainloop_func\n");
}

void clock_mainloop_start(void) {
	System_printf("Starting main loop\n");

	Clock_start(clock_mainloop);
}
