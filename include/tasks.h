#ifndef RMR_TASKS_H_
#define RMR_TASKS_H_

#include <ti/sysbios/knl/Task.h>

extern Task_Handle task_datafusion;
extern Task_Handle task_flush;
extern Task_Handle task_imu;
extern Task_Handle task_led;

void task_datafusion_func(UArg a0, UArg a1);
void task_flush_func(UArg a0, UArg a1);
void task_imu_func(UArg a0, UArg a1);
void task_led_func(UArg a0, UArg a1);

#endif /* RMR_TASKS_H_ */
