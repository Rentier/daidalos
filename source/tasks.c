#include "tasks.h"

#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>

#include "F28x_Project.h"

#include "cla.h"
#include "datafusion.h"
#include "globals.h"
#include "imu.h"
#include "led.h"
#include "queue.h"
#include "semaphores.h"
#include "vec3f.h"

void task_cla_func(UArg a0, UArg a1) {
	System_printf("Starting data fusion task\n");

	CLA_configClaMemory();
	CLA_initCpu1Cla1();
	datafusion_init();
	/*
	 * Transfer bias-data to CLA-memory
	 * todo: put bias information transfer to imu calibration task!
	 */
	bias_acc = imu.bias_acc;
	bias_gyro = imu.bias_gyro;

	/*
	 * This task just initializes the CLA related stuff.
	 */
}

void task_control_func(UArg a0, UArg a1){
	System_printf("Task control init.\n");
	// todo: Initialize the control algorithm.

	while (1) {
		Semaphore_pend(semaphore_control, BIOS_WAIT_FOREVER);
		// todo: Run the control algorithm.
		System_printf("Task control loop run.\n");
		/*
		 *  If there is a CLA involved, it has to be started here and its Hwi needs to post a
		 *  semaphore and this task has to pend on it.
		 *
		 *   Semaphore_pend(semaphore_control_cla_finished, BIOS_WAIT_FOREVER);
		 */

		Semaphore_post(semaphore_motor);
		// Let task_motor run immediately, before buffering.
		Task_yield();

		// todo: Store control results in diagnose buffer. Check if buffer is full.
	}
}

void task_flush_func(UArg a0, UArg a1) {
	System_printf("Starting flush task\n");
	while (1) {
		System_flush();
		Task_sleep(100);
	}
}

void task_imu_func(UArg a0, UArg a1) {
	System_printf("Starting IMU task\n");
	// Initialize SPI module and set up the IMU.
	imu_init();

	// Get calibration data from previous calibration.
	imu_bias_from_flash(&imu);

	while (1) {
		Semaphore_pend(semaphore_mainloop, BIOS_WAIT_FOREVER);
		// Call
		imu_read(&cpu_to_cla.raw_acc, &cpu_to_cla.raw_gyro);

		// Start CLA for datafusion async.
		datafusion_fuse_pose_start();

		System_printf("IMU:\n");
		vec3f_print(cpu_to_cla.raw_acc);
		vec3f_print(cpu_to_cla.raw_gyro);

		// todo: Store IMU raw data in diagnose buffer. Check if buffer is full.
	}
}

void task_led_func(UArg a0, UArg a1) {
	System_printf("Starting LED task\n");
	led_init();

	while (1) {
		led_toggle();
		Task_sleep(1000);
	}
}

void task_motor_func(UArg a0, UArg a1) {
	System_printf("Task motor init.\n");
	/*
	 * todo: Initialize PWM - Die Ausgabe der von den Regelungs-Routinen berechneten
	 * Stellgrößen erfolgt ebenfalls in einem Task. In dessen Initialisierungsphase bereitet
	 * er die PWM-Ausgänge (EPWM7AEPWM8B, GPIO12-15) vor, initialisiert die zwei ePWMKanäle
	 * (EPWM7, EPWM8)
	 */
	while (1) {
		Semaphore_pend(semaphore_motor, BIOS_WAIT_FOREVER);
		System_printf("Task motor runs.");
		// todo: Calculate the duty cycle based on control results. Set PWM accordingly.

		// todo: Store duty cycles in diagnose buffer. Check if buffer is full.

		// todo: Timestamp for benchmark.

		// todo: Deal with watchdog by calling: ServiceDog().

	}
}

void task_receive_msg_func(UArg a0, UArg a1) {
	System_printf("Task receive init.\n");

	// No initialization required. Look at task_transmit_msg_func for init.
	while (1) {
		Semaphore_pend(semaphore_receive_msg, BIOS_WAIT_FOREVER);
		// todo: Process messages recieved from the queue, which gets populated by hwi_uart_rx_msg.
		while (!Queue_empty(queue_receive_msg)) {
			// todo: Pop message and consume it.
			// http://bit.ly/2a0sZQQ

			System_printf("Receive XBEE msg.\n");
		}
	}
}

void task_remote_func(UArg a0, UArg a1) {
	System_printf("Task remote init.\n");
	// TODO: Initialize UART for remote control

	while (1) {
		Semaphore_pend(semaphore_remote, BIOS_WAIT_FOREVER);

		/* TODO: Read from global rc_buffer, compute CRC and parse if valid package.
		 * Set channels in global state vector
		 */

		System_printf("Task remote runs.");
	}
}

void task_transmit_msg_func(UArg a0, UArg a1) {
	System_printf("Task transmit init.\n");

	// Initialize has to happen in transmit, because the reciever on ground does never
	// know if the quadrotor is active. So the first messaging come from this transmit task.
	/*
	 * todo: Initialize the xbee wireless communication module via UART module.
	 * The latter has to become initialized as well.
	 */
	while (1) {
		Semaphore_pend(semaphore_transmit_msg, BIOS_WAIT_FOREVER);
		// After one transmission got triggered, the queue becomes processed completely.
		while (!Queue_empty(queue_transmit_msg)) {
			// todo: Transmit the most recent per message in Queue by MAVMessage ID.
			// http://bit.ly/2a0sZQQ

			System_printf("Send XBEE msg.\n");
		}
	}
}

void task_ultrasonic_func(UArg a0, UArg a1) {
	System_printf("Task ultrasonic init.\n");
	// TODO: Initialize I2C for ultrasonic

	while (1) {
		Semaphore_pend(semaphore_ultrasonic, BIOS_WAIT_FOREVER);

		/* TODO: Read from ultrasonic, wait until reading is complete
		 * Update the global state vector
		 */

		System_printf("Task ultrasonic runs.");
	}
}

