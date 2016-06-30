/*
 * cla.c
 *
 *  Created on: 28.06.2016
 *      Author: Tommy Schmidt
 */

#include "cla.h"
#include "F2837xS_device.h"
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

extern void CLA_configClaMemory(void);
extern void CLA_initCpu1Cla1(void);


void CLA_configClaMemory(void) {
	extern uint32_t Cla1funcsRunStart, Cla1funcsLoadStart, Cla1funcsLoadSize;
	EALLOW;

	CpuSysRegs.PCLKCR0.bit.CLA1 = 1;	// Starting CLA-Clock.
	if (CpuSysRegs.PCLKCR0.bit.CLA1 == 1)
		System_printf("CLA sarted!\n");
	else
		System_printf("CLA Clock not active!\n");
//#ifdef _FLASH
	//
	// Copy over code from FLASH to RAM
	//
	memcpy((uint32_t *)&Cla1funcsRunStart, (uint32_t *)&Cla1funcsLoadStart,
			(uint32_t)&Cla1funcsLoadSize);
//#endif //_FLASH
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
	System_printf("MessageRAM initialized.\n")
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
	System_printf("Memoryconfiguration finished!\n");
	System_flush();
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
	Cla1Regs.MCTL.bit.IACKE = 1;
	Cla1Regs.MIER.all = 0x00FF;

	//
	// Configure the vectors for the end-of-task interrupt for all
	// 8 tasks
	//
//	PieVectTable.CLA1_1_INT = &cla1Isr1;
//	PieVectTable.CLA1_2_INT = &cla1Isr2;
//	PieVectTable.CLA1_3_INT = &cla1Isr3;
//	PieVectTable.CLA1_4_INT = &cla1Isr4;
//	PieVectTable.CLA1_5_INT = &cla1Isr5;
//	PieVectTable.CLA1_6_INT = &cla1Isr6;
//	PieVectTable.CLA1_7_INT = &cla1Isr7;
//	PieVectTable.CLA1_8_INT = &cla1Isr8; All becomes managed by SYSBIOS!

	//
	// Enable CLA interrupts at the group and subgroup levels
	//
	//	PieCtrlRegs.PIEIER11.all = 0xFFFF;
	//	IER |= (M_INT11);
	System_printf("CLA-Initialization finished!\n");
	System_flush();
}

//*****************************************************************************
// ISR
//*****************************************************************************
 void cla1Isr1() {
	asm(" ESTOP0");
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
