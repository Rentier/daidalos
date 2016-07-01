#ifndef RMR_GLOBALS_H_
#define RMR_GLOBALS_H_

#include "cla.h"
#include "imu.h"
#include "quadcopter.h"


#ifdef GLOBAL
    #define EXTERN
#else
    #define EXTERN extern
#endif

#pragma DATA_SECTION(cpu_to_cla,"CpuToCla1MsgRAM")
EXTERN cpu_to_cla_ram cpu_to_cla;
#pragma DATA_SECTION(cla_to_cpu,"Cla1ToCpuMsgRAM")
EXTERN cla_to_cpu_ram cla_to_cpu;

EXTERN Imu imu;

EXTERN quadcopter_t quadcopter;

#endif /* RMR_GLOBALS_H_ */
