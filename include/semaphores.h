#ifndef RMR_SEMAPHORES_H_
#define RMR_SEMAPHORES_H_

#include <ti/sysbios/knl/Semaphore.h>

extern Semaphore_Handle semaphore_control;
extern Semaphore_Handle semaphore_control_cla_finished;
extern Semaphore_Handle semaphore_mainloop;
extern Semaphore_Handle semaphore_spia_done;
extern Semaphore_Handle semaphore_motor;
extern Semaphore_Handle semaphore_receive_msg;
extern Semaphore_Handle semaphore_remote;
extern Semaphore_Handle semaphore_transmit_msg;
extern Semaphore_Handle semaphore_ultrasonic;

#endif /* RMR_SEMAPHORES_H_ */
