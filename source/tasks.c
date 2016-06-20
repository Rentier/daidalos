#include "tasks.h"

#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>

#include "globals.h"
#include "imu.h"
#include "led.h"
#include "semaphores.h"
#include "vec3f.h"

void task_flush_func(UArg a0, UArg a1) {
	System_printf("Starting flush task\n");
	while (1) {
		System_flush();
		Task_sleep(100);
	}
}

void task_imu_func(UArg a0, UArg a1) {
	System_printf("Starting IMU task\n");
	imu_init();

	while (1) {
		Semaphore_pend(semaphore_mainloop, BIOS_WAIT_FOREVER);
		imu_read();

		vec3f_print(cpu_to_cla.w_gyro);
		vec3f_print(cpu_to_cla.a_acc);
	}
}

void task_led_func(UArg a0, UArg a1) {
	System_printf("Starting LED task\n");
	led_init();

	while (1) {
		System_printf("LED toggle\n");
		led_toggle();
		Task_sleep(1000);
	}
}
