#ifndef RMR_TASKS_H_
#define RMR_TASKS_H_

#include <ti/sysbios/knl/Task.h>

extern Task_Handle task_flush;

void task_flush_func(UArg a0, UArg a1);

#endif /* RMR_TASKS_H_ */
