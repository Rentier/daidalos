#ifndef RMR_CLA_H_
#define RMR_CLA_H_

//#define __TMS320C28XX_CLA__

//
// Included Files
//
#include "F2837xS_Cla_defines.h"
//#include "F28X7X_Cla_typedefs.h"
#include <stdint.h>
#include "vec3f.h"
//#include "xdc/std.h"

typedef struct {
	vec3f phi;		// Old phi
	vec3f w;		// Old omega
	vec3f raw_gyro;	// Raw gyro
	vec3f raw_acc;	// Raw acceleration
	vec3f x_gps;
	float z_ultra;
} cpu_to_cla_ram;

typedef struct {
	uint32_t y_1;	// Thrust motor 1
	uint32_t y_2;	// Thrust motor 2
	uint32_t y_3;	// Thrust motor 3
	uint32_t y_4;	// Thrust motor 4
}cla_to_cpu_ram;


//*****************************************************************************
// function prototypes
//*****************************************************************************
// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them
// .global and the main CPU can make use of them.

//CLA C Tasks
__interrupt void Cla1Task1();
__interrupt void Cla1Task2();
__interrupt void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();




//
//Task 1 (C) Variables
//
#ifdef __cplusplus
#pragma DATA_SECTION("CpuToCla1MsgRAM")
extern int x;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
extern int y;
#else
#pragma DATA_SECTION(x,"CpuToCla1MsgRAM")
extern int x;
#pragma DATA_SECTION(y,"Cla1ToCpuMsgRAM")
extern int y;
#endif //__cplusplus

//
//Task 2 (C) Variables
//

//
//Task 3 (C) Variables
//

//
//Task 4 (C) Variables
//

//
//Task 5 (C) Variables
//

//
//Task 6 (C) Variables
//

//
//Task 7 (C) Variables
//

//
//Task 8 (C) Variables
//

#endif /* RMR_CLA_H_ */
