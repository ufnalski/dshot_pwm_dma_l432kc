/*
 * dshot150.h
 *
 *  Created on: Sep 1, 2023
 *      Author: user
 */

#ifndef INC_DSHOT150_H_
#define INC_DSHOT150_H_

#include "main.h"

// 80 MHz clock with prescaler 8-1 gives 0.1 us
#define DSHOT150_BIT_0  	22 // 1/3
#define DSHOT150_BIT_1 		44 // 2/3
#define DSHOT_TELEMETRY 	1
#define SPEED_MIN 			48  // 0-47 are reserved for codes
#define SPEED_MAX 			2047

typedef enum
{
	DSHOT_SPIN_DIRECTION_NORMAL = 0x00U, DSHOT_SPIN_DIRECTION_REVERSE = 0x01U
} DShot_SpinDirectionTypeDef;

typedef enum
{
	DSHOT_BLUE_LED = 0x00U, DSHOT_GREEN_LED = 0x01U, DSHOT_RED_LED = 0x01U
} DShot_LedColorTypeDef;

uint16_t dshot_prepare_packet(uint16_t _command);
void dshot_prepare_dmabuffer(uint8_t *_dshot_dmabuffer_ccr, uint16_t _value);
void dshot_send_ref_speed(uint16_t speed);
void dshot_arm_esc(void);
// void dshot_disarm_esc(void);
uint8_t check_dshot_ref_speed(uint16_t speed);
void dshot_set_spin_direction(DShot_SpinDirectionTypeDef spin_dir);
// void dshot_save_settings(void);
void dshot_led_on(DShot_LedColorTypeDef led_color);
void dshot_led_off(DShot_LedColorTypeDef led_color);

#endif /* INC_DSHOT150_H_ */
