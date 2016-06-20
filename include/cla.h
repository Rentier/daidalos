#ifndef RMR_CLA_H_
#define RMR_CLA_H_

#include "vec3f.h"

typedef struct {
	vec3f w_gyro;
	vec3f a_acc;
	vec3f x_gps;
	float z_ultra;
} cpu_to_cla_ram;

typedef struct {
	vec3f w_gyro;
	vec3f a_acc;
	vec3f x_gps;
	float z_ultra;
} cla_to_cpu_ram;

#endif /* RMR_CLA_H_ */
