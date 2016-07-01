#ifndef RMR_IMU_H_
#define RMR_IMU_H_


#include "vec3f.h"
#include "stdint.h"
//#include "stdbool.h"

typedef struct {
	vec3f bias_acc;
	vec3f bias_gyro;
} Imu;
/*
 * Intialisation prototypes.
 */
void imu_init();
void imu_init_registers();
void imu_init_spia(uint16_t LSPCLK);
void init_spiagpio_hs();

/*
 *
 */
void imu_read();
char imu_read_byte(char reg);
void imu_read_bytes(char reg_start, char *dest, uint16_t cnt);
void imu_write_byte(char reg, char value);

unsigned short imu_free_cfgregs();
unsigned short imu_block_cfgregs();

void imu_spia_rx_isr();
unsigned short imu_test(void);


#endif
