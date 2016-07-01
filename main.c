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

	clock_mainloop_start();

	BIOS_start(); /* does not return */
	return (0);
}
