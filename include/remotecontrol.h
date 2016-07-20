#ifndef RMR_REMOTECONTROL_H_
#define RMR_REMOTECONTROL_H_

#include <stdint.h>

typedef enum {
	RC_NICK = 0,
	RC_ROLL = 1,
	RC_THRUST = 2,
	RC_YAW = 3,
	RC_ARM = 4,
	RC_HEIGHT_CONTROL = 5,
	RC_FL_MODE = 6
} rc_channel;

typedef struct RC_Buffer { uint16_t x[29]; } RC_Buffer;

#endif /* RMR_REMOTECONTROL_H_ */
