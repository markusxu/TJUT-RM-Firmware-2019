/****************************************************************************
 *  Copyright (C) 2019 TJUT-RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
/** @file      sysInit.c
 *  @version   1.0
 *  @date      May 2019
 *
 *  @brief     Handle the referee heat data
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */
 
#include "sysInit.h"
#include "tim.h"
#include "gpio.h"
#include "bsp_uart.h"
#include "oled.h"
#include "key.h"

void systemInit(void)
{
	Dbus_USRT_Init();
	Referee_USRT_Init();
	PC_USRT_Init();
	
	oled_Init();
	oled_LOGO();
	
	IO_Init();
	key_Init();
	
	for(uint8_t i=0; i<8; i++)
	{
		GPIOG->ODR = GPIOG->ODR << 1;
		HAL_Delay(150);
	}
	
/*	
	for(;;){
		switch_scan();
		if(SWstate.value == KEY_OFF_UP){
			break;
		}
		TIM12->CCR1 = 250;
	}
	TIM12->CCR1 = 0;
*/
	
}

void IO_Init(void){
	
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_5, GPIO_PIN_SET);
	
	TIM12->CCR1 = 0;
}
