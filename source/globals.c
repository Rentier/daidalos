#include "globals.h"

Imu imu;	// Calibration information of the inertail sensors.

quadcopter_t quadcopter;	// Global state vector of the system.

RC_Buffer rc_buffer;	// Buffer for recieving byte stream from graupner remote control
