#ifndef RMR_IMU_H_
#define RMR_IMU_H_

#include "xdc/std.h"
#include "F2837xS_device.h"
#include "vec3f.h"

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

Bool imu_free_cfgregs();
Bool imu_block_cfgregs();

void imu_spia_rx_isr();
Bool imu_test(void);


#endif
