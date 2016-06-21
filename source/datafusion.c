#include "datafusion.h"

#include <stdint.h>
#include <math.h>
#include <string.h>

#include <ti/sysbios/gates/GateSwi.h>

#include <xdc/runtime/System.h>

#include "gates.h"
#include "globals.h"

void datafusion_init() {
	System_printf("Initializing data fusion\n");

	memset( &cpu_to_cla, 0, sizeof( cpu_to_cla_ram ) );
	memset( &cla_to_cpu, 0, sizeof( cla_to_cpu_ram ) );
}

void datafusion_fuse_pose(vec3f phi_old, vec3f w_old, vec3f acc, vec3f gyro) {
	vec3f phi, w;

	vec3f bias_acc = imu.bias_acc;
	vec3f bias_gyro = imu.bias_gyro;

	phi.x = atan2( (acc.y-bias_acc.y), (acc.z-bias_acc.z) );
	phi.y = atan2( (acc.x-bias_acc.x), sqrt( (acc.y-bias_acc.y) * (acc.y-bias_acc.y) + (acc.z-bias_acc.z) * (acc.z-bias_acc.z) ) );

	// Radians to degree
	phi.x *= 180 / M_PI;
	phi.y *= 180 / M_PI;

	// Subtract bias
	//TODO: name this coordinate system
	w.x =  (gyro.x - bias_gyro.x);
	w.y = -(gyro.y - bias_gyro.y);
	w.z = -(gyro.z - bias_gyro.z);

	float phi_rad   = phi_old.x * M_PI / 180;
	float theta_rad = phi_old.y * M_PI / 180;

	float sinphi   = sin(phi_rad);
	float cosphi   = cos(phi_rad);
	float tanphi   = tan(phi_rad);

	float sintheta = sin(theta_rad);
	float costheta = cos(theta_rad);
	float tantheta = tan(theta_rad);

	// Complementary filter for Euler angles, see e.g. http://www.pieter-jan.com/node/11
    phi.x = 0.995 * (phi_old.x + 0.0013157 * (w.x+ sinphi*tantheta*w.y + cosphi*tantheta*w.z ) + (w.x-w_old.x) * (0.0013157/2)) + 0.005 * phi.x;
    phi.y = 0.995 * (phi_old.y + 0.0013157 * (cosphi*w.y - sinphi*w.z )+ (w.y-w_old.y) * (0.0013157/2) ) + 0.005 * phi.y;
    phi.z = phi_old.z + 0.0013157 *(sinphi*w.y+cosphi*w.z)/costheta;

    // write back to global state vector
    uint16_t gateKey = GateSwi_enter(gate_swi_statevector);
	quadcopter.phi = phi;
	quadcopter.w = w;
    GateSwi_leave(gate_swi_statevector, gateKey);
}

void datafusion_fuse_position() {

}


