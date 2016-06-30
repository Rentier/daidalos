#ifndef RMR_CLA_H_
#define RMR_CLA_H_

#include "vec3f.h"

typedef struct {
	vec3f phi;		// Old phi
	vec3f w;		// Old omega
	vec3f raw_gyro;	// Raw gyro
	vec3f raw_acc;	// Raw acceleration
	vec3f x_gps;
	float z_ultra;
} cpu_to_cla_ram;

#endif /* RMR_CLA_H_ */
