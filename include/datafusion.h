#ifndef RMR_DATAFUSION_H_
#define RMR_DATAFUSION_H_

#include "vec3f.h"

void datafusion_init();
void datafusion_fuse_pose(vec3f gyro, vec3f acc);
void datafusion_fuse_position();

#endif
