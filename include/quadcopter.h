#ifndef RMR_QUADCOPTER_H_
#define RMR_QUADCOPTER_H_

#include <stdint.h>

#include "config.h"
#include "remotecontrol.h"
#include "quaternion.h"
#include "vec3f.h"

typedef struct {
	vec3f phi;	// Orientation in yaw, pitch, roll
	vec3f phid;	// dPhi/dt

	vec3f w;

	vec3f x;		// Position
	vec3f xd;		// Velocity
	vec3f xdd;	// Acceleration

	quaternion q;
	quaternion qd;

	uint16_t channels[NUM_CHANNELS];
} quadcopter_t ;

#endif /* RMR_QUADCOPTER_H_ */
