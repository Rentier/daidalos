#include "tasks.h"

#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include "cla.h"
#include "datafusion.h"
#include "globals.h"
#include "imu.h"
#include "led.h"
#include "semaphores.h"
#include "vec3f.h"

void task_datafusion_func(UArg a0, UArg a1) {
	System_printf("Starting data fusion task\n");

	CLA_configClaMemory();
	CLA_initCpu1Cla1();
	datafusion_init();
	/*
	 * Übergebe Bias informationen an CLA.
	 */
	bias_acc = imu.bias_acc;
	bias_gyro = imu.bias_gyro;

	while (1) {
		Semaphore_pend(semaphore_datafusion, BIOS_WAIT_FOREVER);
		System_printf("Data fusion:\n");
		datafusion_fuse_pose(cpu_to_cla.phi, cpu_to_cla.w, cpu_to_cla.raw_acc, cpu_to_cla.raw_gyro);

		vec3f_print(quadcopter.phi);
		vec3f_print(quadcopter.w);
	}
}
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

		System_printf("IMU:\n");
		vec3f_print(cpu_to_cla.raw_acc);
		vec3f_print(cpu_to_cla.raw_gyro);

		// Start the data fusion
		// TODO: Actual start CLA task
		Semaphore_post(semaphore_datafusion);
	}
}

void task_led_func(UArg a0, UArg a1) {
	System_printf("Starting LED task\n");
	led_init();

	while (1) {
		led_toggle();
		Task_sleep(1000);

}
