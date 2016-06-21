#ifndef RMR_IMU_H_
#define RMR_IMU_H_

#include "vec3f.h"

typedef struct {
	vec3f bias_acc;
	vec3f bias_gyro;
} Imu;

void imu_init();

void imu_read();

#endif
