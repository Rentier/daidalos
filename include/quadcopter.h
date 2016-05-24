#ifndef RMR_QUADCOPTER_H_
#define RMR_QUADCOPTER_H_

#include "quaternion.h"
#include "vec3f.h"

typedef struct {
	vec3f_t phi;	// Orientation in yaw, pitch, roll
	vec3f_t phid;	// dPhi/dt

	vec3f_t w;

	vec3f_t x;		// Position
	vec3f_t xd;		// Velocity
	vec3f_t xdd;	// Acceleration

	quaternion_t q;
	quaternion_t qd;
} quadcopter_t ;

#endif /* RMR_QUADCOPTER_H_ */
