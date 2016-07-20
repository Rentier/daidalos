#ifndef RMR_SWI_H_
#define RMR_SWI_H_

#include <ti/sysbios/knl/Swi.h>

extern Swi_Handle swi_update_state;

void swi_update_state_func(UArg *arg0, UArg *arg1);

#endif
