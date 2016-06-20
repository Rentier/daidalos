#ifndef RMR_GLOBALS_H_
#define RMR_GLOBALS_H_

#include "cla.h"
#include "imu.h"
#include "quadcopter.h"

extern cpu_to_cla_ram cpu_to_cla;
extern cla_to_cpu_ram cla_to_cpu;

extern Imu imu;

extern quadcopter_t quadcopter;

#endif /* RMR_GLOBALS_H_ */
