/*
 *  ======== main.c ========
 */

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>

#include "led.h"
#include "quadcopter.h"

static quadcopter_t quadcopter;

/*
 *  ======== taskFxn ========
 */
Void taskFxn(UArg a0, UArg a1)
{
	while(1)
	{
    System_printf("enter taskFxn()\n");

    // micro seconds
    Task_sleep(1000);
    toggle_led();

    System_printf("exit taskFxn()\n");

    System_flush(); /* force SysMin output to console */
	}
}

/*
 *  ======== main ========
 */
Int main()
{ 
	init_led();
    Task_Handle task;
    Error_Block eb;

    System_printf("enter main()\n");

    Error_init(&eb);
    task = Task_create(taskFxn, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }

    BIOS_start();    /* does not return */
    return(0);
}
