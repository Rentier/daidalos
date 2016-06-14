#include "led.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <file.h>

#include "F28x_Project.h"

void led_init() {
	GPIO_EnableUnbondedIOPullups();

	//Initialize GPIOs for the LEDs and turn them off
	EALLOW;
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO13 = 1;
	GpioDataRegs.GPADAT.bit.GPIO12 = 1;
	GpioDataRegs.GPADAT.bit.GPIO13 = 1;
	EDIS;

	// Enable global Interrupts and higher priority real-time debug events:
	EINT;
	// Enable Global interrupt INTM
	ERTM;
	// Enable Global realtime interrupt DBGM

	//Twiddle LEDs
	GpioDataRegs.GPADAT.bit.GPIO12 = 0;
	GpioDataRegs.GPADAT.bit.GPIO13 = 1;
}

void led_toggle() {
	GpioDataRegs.GPADAT.bit.GPIO12 = !GpioDataRegs.GPADAT.bit.GPIO12;
	GpioDataRegs.GPADAT.bit.GPIO13 = !GpioDataRegs.GPADAT.bit.GPIO13;
}

