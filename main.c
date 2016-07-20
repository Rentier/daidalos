/*
 *  ======== main.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include "quadcopter.h"

#include "globals.h"

Int main() {
	System_printf("Starting...\n");



	BIOS_start(); /* does not return */
	return (0);
}
