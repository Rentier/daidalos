#ifndef RMR_CLOCKS_H_
#define RMR_CLOCKS_H_

#include <xdc/std.h>

#include <ti/sysbios/knl/Clock.h>

extern Clock_Handle clock_heartbeat;
extern Clock_Handle clock_mainloop;
extern Clock_Handle clock_ultrasonic;

void clock_heartbeat_func(UArg arg0);
void clock_mainloop_func(UArg arg0);
void clock_ultrasonic_func(UArg arg0);

void clock_heartbeat_start(void);
void clock_mainloop_start(void);
void clock_ultrasonic_start(void);

#endif /* RMR_CLOCKS_H_ */
