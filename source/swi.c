#include "swi.h"

#include "cla.h"
#include "datafusion.h"
#include "semaphores.h"

void swi_update_state_func(UArg *arg0, UArg *arg1) {
	// Update global state vector.
	datafusion_fuse_pose_finished();

	// Start control task
	Semaphore_post(semaphore_control);
}
