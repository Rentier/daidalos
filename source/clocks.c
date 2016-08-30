#include "clocks.h"

#include <xdc/runtime/System.h>

#include <ti/sysbios/knl/Semaphore.h>

#include "led.h"
#include "semaphores.h"

Void clock_heartbeat_func(UArg arg0) {
	System_printf("Tick: clock_heartbeat_func\n");

	// TODO: Add hearbeat message to transmit queue
	Semaphore_post(semaphore_transmit_msg);
}

Void clock_mainloop_func(UArg arg0) {
	System_printf("Tick: clock_mainloop_func\n");

	Semaphore_post(semaphore_mainloop);
}

Void clock_ultrasonic_func(UArg arg0) {
	System_printf("Tick: clock_ultrasonic_func\n");

	Semaphore_post(semaphore_ultrasonic);
}

//

void clock_heartbeat_start(void) {
	System_printf("Starting heartbeat clock\n");

	Clock_start(clock_heartbeat);
}

void clock_mainloop_start(void) {
	System_printf("Starting main loop\n");

	Clock_start(clock_mainloop);
}

void clock_ultrasonic_start(void) {
	System_printf("Starting ultrasonic clock\n");

	Clock_start(clock_ultrasonic);
}

// todo: Function for adapting the ultrasonic clock.
