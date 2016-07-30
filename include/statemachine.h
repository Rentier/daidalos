#ifndef RMR_STATEMACHINE_H_
#define RMR_STATEMACHINE_H_

typedef enum {
	BOOT,
	UNINIT,
	CALIBRATING,
	STANDBY,
	ACTIVE,
	POWEROFF,
	EMERGENCY,
	CRITICAL
} rmr_state;

typedef enum {
	PREFLIGHT, 			// Der Quadrokopter befindet sich im Boot-Vorgang
	AUTO_ARMED, 		// Der Autopilot fliegt den Quadrokopter
	AUTO_DISARMED, 		// Der Autopilot ist inaktiv
	MANUAL_ARMED, 		// Der Bediener steuert den Quadrotor
	MANUAL_DISARMED, 	// Der manuelle Betrieb ist inaktkiv
	STABILIZE_ARMED, 	// Der Quadrokopter hält die Position
	STABILIZE_DISARMED 	// Der Position-Halte-Modus ist inaktiv
} rmr_mode;

#endif /* RMR_STATEMACHINE_H_ */
