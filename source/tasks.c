#include "tasks.h"

#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>

#include "F28x_Project.h"

#include "cla.h"
#include "clocks.h"
#include "datafusion.h"
#include "events.h"
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
	Event_post(event_init_system, Event_Init_Cla);
}

void task_control_func(UArg a0, UArg a1){
	System_printf("Task control init.\n");
	// todo: Initialize the control algorithm.

	Event_post(event_init_system, Event_Init_Control);
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
	// Initialize SPI module and set up the IMU. Calling it twice does no harm,
		// but ensures a working interface.
	imu_init();

	// Get calibration data from previous calibration.
	imu_bias_from_flash(&imu);

	Event_post(event_init_system, Event_Init_Imu);
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

void task_imu_calibrate_func(UArg a0, UArg a1) {
	System_printf("Starting IMU calibration task.\n");
	// Initialize SPI module and set up the IMU. Calling it twice does no harm,
	// but ensures a working interface.
	imu_init();

	// todo: Check statemachine. Allow only if MAV is not flying!
	imu_calibrate(&imu);

	// Archive calibration data in flash for quick restore and persistence.
	imu_bias_to_flash(&imu);
}

void task_init_system_func(UArg a0, UArg a1) {
	/* The following setup of event has to be posted, to unpend the event.
	 *
	 */
	System_printf("Waiting for initialization.\n");
	Event_pend(event_init_system, events_and_init_system, Event_Id_NONE, BIOS_WAIT_FOREVER);
	System_printf("Initialization completed.\n");

	/* todo: If the system does not reboot after a watchdog reset start the calibration now
	 * 			and wait until it's done. The watchdog has a register with that information.
	 * 			ATTENTION: until the bias information aren't saved on flash, the calibration
	 * 			has to be done, otherwise no bias informations are avialable.
	 */

	clock_heartbeat_start();
	clock_mainloop_start();
	clock_ultrasonic_start();
	// todo: start watchdog here.
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
	Event_post(event_init_system, Event_Init_Motor);
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

	Event_post(event_init_system, Event_Init_Remote);
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
	Event_post(event_init_system, Event_Init_Message);
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

	Event_post(event_init_system, Event_Init_Ultrasonic);
	while (1) {
		Semaphore_pend(semaphore_ultrasonic, BIOS_WAIT_FOREVER);

		/*
		 * TODO: Read from ultrasonic, trigger new read cycle. Provide measured data to datafusion POSITION.
		 * 		 Follow instructions to avoid data race/ conflict:
		 *			...als erstes den CLA-Task Datenfusion POSTION im MIER-Register
		 *			des CLA deaktiviert wird. (Hat keinen Einfluss für den
		 *			Fall der Task läuft bereits). Dann wird 3 Zyklen gewartet
		 *			(Solange bräuchte ein soeben gestarteter CLA Task, um die
		 *			Messdaten aus dem Message-RAM zu lesen), danach wird
		 *			den Message-RAM mit den neuen Messdaten beschrieben,
		 *			anschließend wird den CLA-Task an selber Stelle reaktiviert
		 *			[4, S.723] (Sollte der Task in der Zeit an einer anderen Stelle
		 *			im Programm gestartet worden sein, so wird er nach der
		 *			Reaktivierung unbeeinflusst ausgeführt).
		 *
		 */

		System_printf("Task ultrasonic runs.");
	}
}

