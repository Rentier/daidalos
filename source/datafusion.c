#include "datafusion.h"

#include "F2837xS_Cla_defines.h"

#include <stdint.h>
#include <math.h>
#include <string.h>

#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/System.h>

#include "gates.h"
#include "globals.h"
#include "cla.h"

void datafusion_init() {
	System_printf("Initializing data fusion\n");

	memset(&cpu_to_cla, 0, sizeof(cpu_to_cla_ram));
	memset(&cla_to_cpu, 0, sizeof(cla_to_cpu_ram));
	memset(&bias_acc, 0, sizeof(vec3f));
	memset(&bias_gyro, 0, sizeof(vec3f));
}

void datafusion_fuse_pose_start() {
	Cla1ForceTask1();
}


void datafusion_fuse_pose_finished(){
	System_printf("Datafusion POSE finished succesfully!\n");

	// write back to global state vector
	uint16_t gateKey = GateSwi_enter(gate_swi_statevector);
	quadcopter.phi = cla_to_cpu.phi;
	quadcopter.w = cla_to_cpu.w;
	GateSwi_leave(gate_swi_statevector, gateKey);
}

void datafusion_fuse_position_start() {

}

void datafusion_fuse_position_finished(){

}
