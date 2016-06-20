#include "imu.h"

#include <xdc/runtime/System.h>

#include "globals.h"

void imu_init() {
	// Initialize SPI
	System_printf("Initializing IMU\n");

	imu.bias.x = 0;
	imu.bias.y = 0;
	imu.bias.z = 0;

	cpu_to_cla.w_gyro.x = 0;
	cpu_to_cla.w_gyro.y = 0;
	cpu_to_cla.w_gyro.z = 0;

	cpu_to_cla.a_acc.x = 0;
	cpu_to_cla.a_acc.y = 0;
	cpu_to_cla.a_acc.z = 0;
}

void imu_read() {
	// SPI Magic
	// Write into CLA buffer

	cpu_to_cla.a_acc = vec3f_sadd(cpu_to_cla.a_acc, 1);
	cpu_to_cla.w_gyro = vec3f_sadd(cpu_to_cla.w_gyro, 1);
}
