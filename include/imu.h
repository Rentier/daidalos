#ifndef RMR_IMU_H_
#define RMR_IMU_H_

#include "vec3f.h"

typedef struct {
	vec3f bias;
} Imu;

void imu_init();

void imu_read();

#endif
