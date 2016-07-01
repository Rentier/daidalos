/*
 * cla.c
 *
 *  Created on: 28.06.2016
 *      Author: Tommy Schmidt
 */

#include "xdc/runtime/System.h"
#include "cla.h"
#include "F2837xS_device.h"
#include "F2837xS_Cla_defines.h"
#include "globals.h"
#include "semaphores.h"

//#include "F28X7X_Cla_typedefs.h"
//#include "xdc/std.h"
//#include "stdint.h"
//
// Function Prototypes
//

void cla1Isr1();
void cla1Isr2();
void cla1Isr3();
void cla1Isr4();
void cla1Isr5();
void cla1Isr6();
void cla1Isr7();
void cla1Isr8();


void CLA_configClaMemory(void) {
	extern uint32_t Cla1funcsRunStart, Cla1funcsLoadStart, Cla1funcsLoadSize;
	EALLOW;

	CpuSysRegs.PCLKCR0.bit.CLA1 = 1;	// Starting CLA-Clock.
	if (CpuSysRegs.PCLKCR0.bit.CLA1 == 1)
		System_printf("CLA sarted!\n");
	else
		System_printf("CLA Clock not active!\n");

	//
	// Copy over code from FLASH to RAM
	//
	memcpy((uint32_t *)&Cla1funcsRunStart, (uint32_t *)&Cla1funcsLoadStart,
			(uint32_t)&Cla1funcsLoadSize);

	System_printf("Cla1funcsRunStart: %x \tCla1funcsLoadStart: %x \tCla1funcsLoadSize: %x \n", Cla1funcsRunStart ,Cla1funcsLoadStart, Cla1funcsLoadSize);
	System_flush();
	//
	// Initialize and wait for CLA1ToCPUMsgRAM
	//
	MemCfgRegs.MSGxINIT.bit.INIT_CLA1TOCPU = 1;
	while (MemCfgRegs.MSGxINITDONE.bit.INITDONE_CLA1TOCPU != 1) {
	};

	//
	// Initialize and wait for CPUToCLA1MsgRAM
	//
	MemCfgRegs.MSGxINIT.bit.INIT_CPUTOCLA1 = 1;
	while (MemCfgRegs.MSGxINITDONE.bit.INITDONE_CPUTOCLA1 != 1) {
	};
	System_printf("Messageram initialized.\n");
	//
	// Select LS3RAM to be the programming space for the CLA
	// First configure the CLA to be the master for LS3 and then
	// set the space to be a program block
	//
	MemCfgRegs.LSxMSEL.bit.MSEL_LS3 = 1;
	MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS3 = 1;

	//
	// Next configure LS0RAM and LS1RAM as data spaces for the CLA
	// First configure the CLA to be the master for LS0(1) and then
	// set the spaces to be code blocks
	//
	MemCfgRegs.LSxMSEL.bit.MSEL_LS0 = 1;
	MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS0 = 0;

	MemCfgRegs.LSxMSEL.bit.MSEL_LS1 = 1;
	MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS1 = 0;

	EDIS;
}

//
// CLA_initCpu1Cla1 - Initialize CLA1 task vectors and end of task interrupts
//
void CLA_initCpu1Cla1(void) {
	//
	// Compute all CLA task vectors
	// On Type-1 CLAs the MVECT registers accept full 16-bit task addresses as
	// opposed to offsets used on older Type-0 CLAs
	//
	EALLOW;
	Cla1Regs.MVECT1 = (uint16_t) (&Cla1Task1);
	Cla1Regs.MVECT2 = (uint16_t) (&Cla1Task2);
	Cla1Regs.MVECT3 = (uint16_t) (&Cla1Task3);
	Cla1Regs.MVECT4 = (uint16_t) (&Cla1Task4);
	Cla1Regs.MVECT5 = (uint16_t) (&Cla1Task5);
	Cla1Regs.MVECT6 = (uint16_t) (&Cla1Task6);
	Cla1Regs.MVECT7 = (uint16_t) (&Cla1Task7);
	Cla1Regs.MVECT8 = (uint16_t) (&Cla1Task8);

	//
	// Enable the IACK instruction to start a task on CLA in software
	// for all  8 CLA tasks. Also, globally enable all 8 tasks (or a
	// subset of tasks) by writing to their respective bits in the
	// MIER register
	//
	Cla1Regs.MCTL.bit.IACKE = CLA_IACK_ENABLE;
	Cla1Regs.MIER.all = 0x00FF;


}

//*****************************************************************************
// ISR
//*****************************************************************************
 void cla1Isr1() {
	Semaphore_post(semaphore_datafusion);
}

 void cla1Isr2() {
	asm(" ESTOP0");

}

 void cla1Isr3() {
	asm(" ESTOP0");

}

 void cla1Isr4() {
	asm(" ESTOP0");
}

 void cla1Isr5() {
	asm(" ESTOP0");
}

void cla1Isr6() {
	asm(" ESTOP0");
}

void cla1Isr7() {
	asm(" ESTOP0");
}

void cla1Isr8() {
	asm(" ESTOP0");
}
