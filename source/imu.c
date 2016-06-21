#include "imu.h"

#include <string.h>

#include <xdc/runtime/System.h>

#include "globals.h"

void imu_init() {
	// Initialize SPI
	System_printf("Initializing IMU\n");

	memset( &imu, 0, sizeof( Imu ) );
}

void imu_read() {
	// SPI Magic
	// Write into CLA buffer

	cpu_to_cla.raw_acc = vec3f_sadd(cpu_to_cla.raw_acc, 1);
	cpu_to_cla.raw_gyro = vec3f_sadd(cpu_to_cla.raw_gyro, 1);
}
