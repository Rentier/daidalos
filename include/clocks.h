#ifndef RMR_CLOCKS_H_
#define RMR_CLOCKS_H_

#include <xdc/std.h>

#include <ti/sysbios/knl/Clock.h>

extern Clock_Handle clock_mainloop;

void clock_mainloop_func(UArg arg0);

void clock_mainloop_start(void);

#endif /* RMR_CLOCKS_H_ */
