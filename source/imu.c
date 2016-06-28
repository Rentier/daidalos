#include "imu.h"

#include <string.h>

#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/System.h>
#include "semaphores.h"
#include "globals.h"

static Bool read; // Flag for signing a read command. FALSE is a write!

static char garbage; // Garbage area, neccessary for reading the RxBuffer to acknowledge Interrupt

static char *read_destination;
static uint16_t count_to_read, read_cycle;

static uint16_t data_tx; // String to be sent via SPI (Prepared to load into TxBuffer)

void imu_init() {
	// Initialize SPI
	System_printf("Initializing IMU\n");

	memset(&imu, 0, sizeof(Imu));

	imu_init_spia(50000);
	if (imu_test())
		System_printf("IMU - Test successfully finished.");
	else
		System_printf("IMU - Test failed!");


}


void imu_init_spia(uint16_t LSPCLK) {
	// Setup the Highspeed GPIO Pins (GPIO68-61)
	init_spiagpio_hs();

	// SPIASTE Pin has to be controled manually, for correct operation.
	EALLOW;
	/*
	 * To ensure correct performance the usual SPI sequence had to be split up. So the SPISTE line
	 * has to become emulated by the CPU. So reset them to GPIO function.
	 */

	CpuSysRegs.PCLKCR8.bit.SPI_A = 1;

	GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0; 	// Configure GPIO61 as GPIO for SPIASTE
	GpioCtrlRegs.GPBGMUX2.bit.GPIO61 = 0; 	// Configure GPIO61 as GPIO for SPIASTE
	GpioDataRegs.GPBDAT.bit.GPIO61 = 1;
	GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1;  	// SPIASTE is an output!
	EDIS;

	SpiaRegs.SPICCR.bit.SPISWRESET = 0; 	// Reset SPI for configuration

	SpiaRegs.SPICCR.bit.CLKPOLARITY = 1; 	// Send on falling SPICLK edge
	SpiaRegs.SPICCR.bit.HS_MODE = 1;	 	// Highspeedmode AN
	SpiaRegs.SPICCR.bit.SPICHAR = 0x7;	 	// Sende 8 bit je Trigger
	SpiaRegs.SPICCR.bit.SPILBK = 0;			// Loopback-Mode nur zu Testzwecken zu benutzen.

	SpiaRegs.SPICTL.bit.CLK_PHASE = 1;		// Individual setup for Send- /Recievestream (Tx:1/Rx:0)
	SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;	// F28377S is Master
	SpiaRegs.SPICTL.bit.OVERRUNINTENA = 0;	// Overrun Interrupt DISABLE
	SpiaRegs.SPICTL.bit.SPIINTENA = 1;		// Interrupt for Recieve and Transmitbuffer ENABLE
	SpiaRegs.SPICTL.bit.TALK = 1;			// Transmit ENABLE

	SpiaRegs.SPIBRR.bit.SPI_BIT_RATE = 0x05; // Baudrate on 10 Mhz ! (LSPCLK on 50Mhz --> SPI_BIT_RATE = 0x05 for 10 Mhz Communication)

	SpiaRegs.SPIPRI.bit.FREE = 1;			// Free running ENABLE
	SpiaRegs.SPIPRI.bit.SOFT = 0; 			// Does have no effect, if FREE-bit is 1!!!

	SpiaRegs.SPICCR.bit.SPISWRESET = 1;  	// Enable SPI after Configuration
}

/*
 * Setup the IMU Registers for operation.
 */
void imu_init_registers() {
	imu_free_cfgregs();

	imu_write_byte(0x10, 0x80); // Activate Accelerometer
	imu_write_byte(0x11, 0x80); // Activate Gyroskope

	imu_block_cfgregs();
}

void imu_read() {
	// SPI Magic
	// Write into CLA buffer

	cpu_to_cla.raw_acc = vec3f_sadd(cpu_to_cla.raw_acc, 1);
	cpu_to_cla.raw_gyro = vec3f_sadd(cpu_to_cla.raw_gyro, 1);
}

/*
 * Enable access to the embedded functions configuration registers from address 02h to 32h.
 * That option is neccessary to edit the named registers.
 */
Bool imu_free_cfgregs() {
	imu_write_byte(0x01, 0x80);
	if (imu_read_byte(0x01) != 128)
		return false;
	else
		return true;
	return imu_read_byte(0x01) == 128;
}

/*
 * Disable access to the embedded functions configuration registers from address 02h to 32h.
 * That option is neccessary for correct operation of the IMU.
 */
Bool imu_block_cfgregs() {
	imu_write_byte(0x01, 0x00);
	return imu_read_byte(0x01) == 0;
}

/// Initialize the perepherial registers (GPIO & SPI-A) for communication to IMU (Inertial Measurement Unit).
/// A maximum baudrate of 10 Mbps is reachable with the actually used LSM6DS33 - unit.
/// Caused by timing issues between master (F28377S) and slave (IMU), the clock phase is required to be shifted
/// during a recieve stream.
/// @param LSPCLK Integer value of "Low Speed Clock" in kHz.

/*
 *Read one register (byte) out of the IMU.
 * @param reg Register to be read out of the IMU.
 * @return Value that is returned by IMU.
 */
char imu_read_byte(char reg) {
	char value;
	imu_read_bytes(reg, &value, 1);
	return value;
}

/*
 * Read multiple bytes out of the the IMU by just adding multiple counts of 8 to the regulary 16 cycles. Reading is a special
 * case wherein the setup between the first 8 transmit cycles and the following cnt times 8 reading registers has to be changed.
 * That the registers the IMU replys are incremented one by one, that setup has to be ensured on the IMU. Otherwise the same
 * register replys all the time.
 * @param reg_start Register where to start the read out.
 * @param *dest Pointer to the destination array with at least cnt elements.
 * @param cnt Number of Registers to read out.
 */
void imu_read_bytes(char reg_start, char *dest, uint16_t cnt) {
	read = true; // Flag for ISR.
	count_to_read = cnt;	// Initialize the count for the ISR-Routine
	read_destination = dest;	// Initialize the Pointer for the ISR-Routine.
	read_cycle = 0;	// Initialise the counter for ISR-Routine.

	/*
	 * The transmit part (the read command and which register to reply) needs to happen with active
	 * phase shifting appart to the CLK_POLARITY = 1. So the first 8 (1 + 7) SPICLK cycles are seperately
	 * from the cycles past, where the IMU replies.
	 */
	SpiaRegs.SPICCR.bit.SPICHAR = 0x7;
	SpiaRegs.SPICTL.bit.CLK_PHASE = 1;

	/*
	 * To read a value out of a register of the IMU the command has to have the following structure:
	 * Bit15 (MSB):		1				--> Read a Register out of the IMU (or IMU: "Do reply!")
	 * Bit14 - 8:		0x00 - 0x6B 	--> Registeraddress
	 * Bit7 - 0:		DummyData --> Data will be read from Rx-Stresn! Nothing is sent down.
	 */
	data_tx = ((0x0080 + reg_start) << 8) + 0x00FF;

	// Start communication by pulling SPIASTE down to 0 (Communication Enable)
	GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;

	// Fire SPIA by loading the transmit buffer.
	SpiaRegs.SPITXBUF = data_tx;

	// Wait now for the ISR signals back, that the communication is done.
	Semaphore_pend(semaphore_spia_done, BIOS_WAIT_FOREVER);

	//Finish the communication by pushing the SPIASTE back up to 1 (TRUE).
	GpioDataRegs.GPBSET.bit.GPIO61 = 1;

	return;
}

/*
 * Write a specified value into a register on the IMU. This one can be done with the same setup about
 * all of its 16 SPICLK cycles, because nothing has to be read back for the Rx Stream.
 * @param reg Register to write into the IMU.
 * @param value That's the value that will be written into the IMU-register.
 */
void imu_write_byte(char reg, char value) {
	// TODO: Check des Registers ob Wert zwischen 0x00 und 0x5F
	read = false;

	/*
	 * The transmit part (the write command, which register to overwrite and the value to do so)
	 * needs to happen with active phase shifting. Because no setup change is neccessary during this
	 * operation, all th 16 (1 + 7 + 8) SPICLK cycles are done with this setup.
	 */
	SpiaRegs.SPICTL.bit.CLK_PHASE = 1;
	SpiaRegs.SPICCR.bit.SPICHAR = 0xF;

	/*
	 * To write a value into a register of the IMU the command has to have the following structure:
	 * Bit15 (MSB):		0				--> Write a Register. (Do not reply to something!)
	 * Bit14 - 8:		0x00 - 0x5F 	--> Registeraddress
	 * Bit7 - 0:		0xYZ			--> Value to register above has to be written to.
	 */
	data_tx = (reg << 8) + value;

	// Start communication by pulling SPIASTE down to 0 (Communication Enable)
	GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;

	// Fire SPIA by loading the transmit buffer.
	SpiaRegs.SPITXBUF = data_tx;

	// Wait now for the ISR signals back, that the communication is done.
	Semaphore_pend(semaphore_spia_done, BIOS_WAIT_FOREVER);

	//Finish the communication by pushing the SPIASTE back up to 1 (TRUE).
	GpioDataRegs.GPBSET.bit.GPIO61 = 1;

	// End - SPI Magic
}

/*
 * The ISR needs to distinguish if it got an interrupt caused by a read_byte(s) or write_byte transmition.
 * That's necceassary becaus the phase to capture data has to be shifted during the read_byte - operation.
 * This knowledge was captured while a longterm Trial-an-Error-procedure!
 */
void imu_spia_rx_isr() {
	if (read) {
		if (read_cycle == 0) {// Read a register out of the IMU.

			/*The past transmition was "Read a Register" instruction (IMU has recieved
			 * the read command and the register where to start at).
			 * Put now DUMMY data into transmition-command and start the first
			 * real read transmition.*/
			garbage = SpiaRegs.SPIRXBUF; // Dummyread the Rx-Buffer to clear SPI INT_FLAG

			read_cycle = 1; // Init the read cycle to the first for the next interrupt sequence.

			SpiaRegs.SPICTL.bit.CLK_PHASE = 0; // Shift the sample phase on rising edge without delay to recieve data correctly

			SpiaRegs.SPITXBUF = 0xFFFF; // Fire the SPI again by reloading the Tx-Buffer by loading a dummy value into it.
			/*
			 * Important Notice: 	The dummy data to transmit during the IMU shall reply a register isn't as dummy as it seems.
			 * 						The SIMO (Tx-) stream must keep high level, that the IMU replies correctly!!!
			 */

		} else if (read_cycle < count_to_read) {
			/*
			 * The past read cycle (8 SPICLK periods) brought back the char-value of
			 * the selected (or an incremented) register.
			 * Pull data out of recieve buffer and start new read cycle.
			 */
			*(read_destination + read_cycle) = SpiaRegs.SPIRXBUF & 0x00FF;

			SpiaRegs.SPITXBUF = 0xFFFF;
			read_cycle++;
		} else {
			/*
			 * The past read cycle was the last read cycle. So pull the last data out of
			 * the recieve buffer and release the waiting "write_byte" function from waiting.
			 */
			*(read_destination + count_to_read - 1) = SpiaRegs.SPIRXBUF
					& 0x00FF;

			Semaphore_post(semaphore_spia_done);
		}
	} else { // Write a register into IMU.
		/*
		 * After a write_byte command to the IMU the waiting task/ function can be released.
		 * Nothing else to do.
		 */
		garbage = SpiaRegs.SPIRXBUF; // Dummyread the Rx-Buffer to clear SPI INT_FLAG
		Semaphore_post(semaphore_spia_done);
	}
}

/*
 * Read out the WHO_I_AM Register.
 * @return True if the IMU replied with 0x69 (105).
 */
Bool imu_test(void) {
	if (imu_read_byte(0x0F) != 0x69)
		return false;
	else
		return true;
}

/// Initialize the GPIO-Pins for High-Speed-Communication of the SPI-A peripherie.
/// GPIO58:	SPISIMO ... SlaveInMasterOut
/// GPIO59: SPISOMI ... SlaveOutMasterIn
/// GPIO60: SPICLK  ... Clock (asynchron), controlled by Master
/// GPIO61: SPISTE  ... Transmit Enable (=FALSE)
/// Edited by: Tommy Schmidt, 15.06.2016
void init_spiagpio_hs() {
	EALLOW;

	/* Enable internal pull-up for the selected pins */
	// Pull-ups can be enabled or disabled by the user.
	// This will enable the pullups for the specified pins.
	// Comment out other unwanted lines.
	GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0; // Enable pull-up on GPIO58 (SPISIMOA)
	GpioCtrlRegs.GPBPUD.bit.GPIO59 = 0; // Enable pull-up on GPIO59 (SPISOMIA)
	GpioCtrlRegs.GPBPUD.bit.GPIO60 = 0; // Enable pull-up on GPIO60 (SPICLKA)
	GpioCtrlRegs.GPBPUD.bit.GPIO61 = 0; // Enable pull-up on GPIO61 (SPISTEA)

	/* Set qualification for selected pins to asynch only */
	// This will select asynch (no qualification) for the selected pins.
	// Comment out other unwanted lines.
	GpioCtrlRegs.GPBQSEL2.bit.GPIO58 = 3; // Asynch input GPIO58 (SPISIMOA)
	GpioCtrlRegs.GPBQSEL2.bit.GPIO59 = 3; // Asynch input GPIO59 (SPISOMIA)
	GpioCtrlRegs.GPBQSEL2.bit.GPIO60 = 3; // Asynch input GPIO60 (SPICLKA)
	GpioCtrlRegs.GPBQSEL2.bit.GPIO61 = 3; // Asynch input GPIO61 (SPISTEA)

	/* Configure SPI-A pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be SPI functional pins.
	// Comment out other unwanted lines.
	GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 3; // Configure GPIO58 as SPISIMOA
	GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 3; // Configure GPIO59 as SPISOMIA
	GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 3; // Configure GPIO60 as SPICLKA
	GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 3; // Configure GPIO61 as SPISTEA

	GpioCtrlRegs.GPBGMUX2.bit.GPIO58 = 3; // Configure GPIO58 as SPISIMOA
	GpioCtrlRegs.GPBGMUX2.bit.GPIO59 = 3; // Configure GPIO59 as SPISOMIA
	GpioCtrlRegs.GPBGMUX2.bit.GPIO60 = 3; // Configure GPIO60 as SPICLKA
	GpioCtrlRegs.GPBGMUX2.bit.GPIO61 = 3; // Configure GPIO61 as SPISTEA

	/* Configure outputs as outputs and inputs as inputs*/
	GpioCtrlRegs.GPBDIR.bit.GPIO58 = 1; // Configure GPIO58 (SPISIMOA) as output
	GpioCtrlRegs.GPBDIR.bit.GPIO59 = 0; // Configure GPIO59 as SPISOMIA
	GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1; // Configure GPIO60 as SPICLKA
	GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1; // Configure GPIO61 as SPISTEA

	EDIS;
}
