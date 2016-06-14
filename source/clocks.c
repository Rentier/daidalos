#include "clocks.h"

#include <xdc/runtime/System.h>

#include <ti/sysbios/knl/Semaphore.h>

#include "led.h"
#include "semaphores.h"

Void clock_mainloop_func(UArg arg0) {
	System_printf("Tick: clock_mainloop_func\n");

	Semaphore_post(semaphore_mainloop);
}

void clock_mainloop_start(void) {
	System_printf("Starting main loop\n");

	Clock_start(clock_mainloop);
}
