#ifndef RMR_DATAFUSION_H_
#define RMR_DATAFUSION_H_

#include "vec3f.h"

void datafusion_init();
void datafusion_fuse_pose_start();
void datafusion_fuse_pose_finished();
void datafusion_fuse_position_start();
void datafusion_fuse_position_after();

#endif
