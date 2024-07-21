/*
 * dshot150.c
 *
 *  Created on: Sep 1, 2023
 *      Author: user
 */

#include "dshot150.h"
#include "tim.h"

uint8_t dshot_dmabuffer_ccr[20];
uint8_t dshot_dmabuffer_arr[20];

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM1)
	{
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			HAL_GPIO_TogglePin(LOGIC_ANALYZER_GPIO_Port, LOGIC_ANALYZER_Pin);
			HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
		}
	}
}

// https://github.com/mokhwasomssi/stm32_hal_dshot
uint16_t dshot_prepare_packet(uint16_t value)
{
	uint16_t packet;

	packet = (value << 1) | (DSHOT_TELEMETRY ? 1 : 0);

	// compute checksum
	uint8_t csum = 0;
	uint16_t csum_data = packet;

	for (uint8_t i = 0; i < 3; i++)
	{
		csum ^= csum_data; // xor data by nibbles
		csum_data >>= 4;
	}

	csum &= 0xf;

	packet = (packet << 4) | csum;

	return packet; //^0x0110; // this is not CRC!
}

void dshot_prepare_dmabuffer(uint8_t *_dshot_dmabuffer_ccr,
		uint8_t *_dshot_dmabuffer_arr, uint16_t _value)
{
	uint16_t packet;
	packet = dshot_prepare_packet(_value);

	for (int i = 0; i < 16; i++)
	{
		_dshot_dmabuffer_ccr[i] =
				(packet & 0x8000) ? DSHOT150_BIT_1 : DSHOT150_BIT_0;
		_dshot_dmabuffer_arr[i] = DSHOT150_TIM_ARR;
		packet <<= 1;
	}
	_dshot_dmabuffer_ccr[16] = 0;
	_dshot_dmabuffer_arr[16] = DSHOT150_TIM_ARR;
	_dshot_dmabuffer_ccr[17] = 0;
	_dshot_dmabuffer_arr[17] = DSHOT150_TIM_ARR;
	_dshot_dmabuffer_ccr[18] = 0;
	_dshot_dmabuffer_arr[18] = DSHOT150_TIM_ARR;
	_dshot_dmabuffer_ccr[19] = 0;
	_dshot_dmabuffer_arr[19] = DSHOT150_TIM_ARR;
}

void dshot_arm_esc(void)
{
	dshot_prepare_dmabuffer(dshot_dmabuffer_ccr, dshot_dmabuffer_arr, 0);

	for (int i = 0; i < 1000; i++)
	{
		HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1,
				(uint32_t*) dshot_dmabuffer_ccr, 20);
		HAL_Delay(3);
	}
}

void dshot_send_ref_speed(uint16_t _motor_speed)
{
	dshot_prepare_dmabuffer(dshot_dmabuffer_ccr, dshot_dmabuffer_arr,
			_motor_speed);
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1,
			(uint32_t*) dshot_dmabuffer_ccr, 20);
}

uint8_t check_dshot_ref_speed(uint16_t speed)
{
	if ((speed < 48) || (speed > 2047))
		return 1;
	else
		return 0;
}
