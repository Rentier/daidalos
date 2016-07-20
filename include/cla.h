#ifndef RMR_CLA_H_
#define RMR_CLA_H_

#include "vec3f.h"
#include <stdint.h>


typedef struct {
	vec3f phi;		// Old phi
	vec3f w;		// Old omega
	vec3f raw_gyro;	// Raw gyro
	vec3f raw_acc;	// Raw acceleration
	vec3f x_gps;
	float z_ultra;
} cpu_to_cla_ram;

typedef struct {
	float y_1;	// Thrust motor 1
	float y_2;	// Thrust motor 2
	float y_3;	// Thrust motor 3
	float y_4;	// Thrust motor 4
	vec3f phi;	// Corrected Pose
	vec3f w;	// Corrected angular speed
}cla_to_cpu_ram;


//*****************************************************************************
// function prototypes
//*****************************************************************************
// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them
// .global and the main CPU can make use of them.
void CLA_configClaMemory(void);
void CLA_initCpu1Cla1(void);

void cla1Isr1(void);

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
extern vec3f bias_acc, bias_gyro;

extern cpu_to_cla_ram cpu_to_cla;

extern cla_to_cpu_ram cla_to_cpu;

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
