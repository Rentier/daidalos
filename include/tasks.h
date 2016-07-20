#ifndef RMR_TASKS_H_
#define RMR_TASKS_H_

#include <ti/sysbios/knl/Task.h>

extern Task_Handle task_cla;
extern Task_Handle task_control;
extern Task_Handle task_flush;
extern Task_Handle task_imu;
extern Task_Handle task_init_system;
extern Task_Handle task_led;
extern Task_Handle task_motor;
extern Task_Handle task_receive_msg;
extern Task_Handle task_remote;
extern Task_Handle task_transmit_msg;
extern Task_Handle task_ultrasonic;

void task_cla_func(UArg a0, UArg a1);
void task_control_func(UArg a0, UArg a1);
void task_flush_func(UArg a0, UArg a1);
void task_imu_func(UArg a0, UArg a1);
void task_imu_calibrate_func(UArg a0, UArg a1); // This task must be created manually in code.
void task_init_system_func(UArg a0, UArg a1);
void task_led_func(UArg a0, UArg a1);
void task_motor_func(UArg a0, UArg a1);
void task_receive_msg_func(UArg a0, UArg a1);
void task_remote_func(UArg a0, UArg a1);
void task_transmit_msg_func(UArg a0, UArg a1);
void task_ultrasonic_func(UArg a0, UArg a1);

#endif /* RMR_TASKS_H_ */
