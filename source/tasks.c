#include "tasks.h"

#include <xdc/runtime/System.h>

void task_flush_func(UArg a0, UArg a1) {
	System_printf("Starting task flush\n");
	while (1) {
		System_flush();
		Task_sleep(1000);
	}
}
