/*
 * cla.c
 *
 *  Created on: 28.06.2016
 *      Author: Tommy Schmidt
 */
#define CLA_SHARE
#include "cla.h"

#include "xdc/runtime/System.h"

#include "F2837xS_device.h"
#include "F2837xS_Cla_defines.h"
#include "globals.h"
#include "semaphores.h"

//#include "F28X7X_Cla_typedefs.h"
//#include "xdc/std.h"
//#include "stdint.h"

#pragma DATA_SECTION(cpu_to_cla,"CpuToCla1MsgRAM")
cpu_to_cla_ram cpu_to_cla;

#pragma DATA_SECTION(cla_to_cpu,"Cla1ToCpuMsgRAM")
cla_to_cpu_ram cla_to_cpu;

#pragma DATA_SECTION(bias_acc,"CLADataLS0");
#pragma DATA_SECTION(bias_gyro,"CLADataLS0");
vec3f bias_acc, bias_gyro;

extern uint32_t cla1funcs_run_start, cla1funcs_load_start, cla1funcs_load_size;
extern uint32_t cla1math_tables_run_start, cla1math_tables_load_start, cla1math_tables_load_size;
extern uint32_t cla1_const_run_start, cla1_const_load_start, cla1_const_load_size;

void CLA_configClaMemory(void) {
	EALLOW;

	CpuSysRegs.PCLKCR0.bit.CLA1 = 1;	// Starting CLA-Clock.
	if (CpuSysRegs.PCLKCR0.bit.CLA1 == 1)
		System_printf("CLA started!\n");
	else
		System_printf("CLA Clock not active!\n");

	//
	// Copy over program-code from FLASH to RAM
	//
	memcpy((uint32_t *)&cla1funcs_run_start, (uint32_t *)&cla1funcs_load_start,
				(uint32_t)&cla1funcs_load_size);

	/*
	 * Copy over tables from CLAmath.lib
	 */
	memcpy((uint32_t *)&cla1math_tables_run_start, (uint32_t *)&cla1math_tables_load_start,
				(uint32_t)&cla1math_tables_load_size);

	/*
	 * Copy over constants to data memory.
	 */
	memcpy((uint32_t *)&cla1_const_run_start, (uint32_t *)&cla1_const_load_start,
			(uint32_t)&cla1_const_load_size);


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
	Semaphore_post(semaphore_datafusion_finished);
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
