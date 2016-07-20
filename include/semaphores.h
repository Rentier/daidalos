#ifndef RMR_SEMAPHORES_H_
#define RMR_SEMAPHORES_H_

#include <ti/sysbios/knl/Semaphore.h>

extern Semaphore_Handle semaphore_mainloop;
extern Semaphore_Handle semaphore_datafusion_start;
extern Semaphore_Handle semaphore_datafusion_finished;
extern Semaphore_Handle semaphore_spia_done;


#endif /* RMR_SEMAPHORES_H_ */
