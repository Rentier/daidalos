/*
 *  ======== main.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include "clocks.h"
#include "quadcopter.h"

#define GLOBAL
#include "globals.h"

Int main() {
	System_printf("Starting...\n");

	// TODO: Start clocks after init task is finished.
	clock_heartbeat_start();
	clock_mainloop_start();
	clock_ultrasonic_start();

	BIOS_start(); /* does not return */
	return (0);
}
