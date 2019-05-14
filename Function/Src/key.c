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
/** @file key.c
 *  @version 1.0
 *  @date May 2019
 *
 *  @brief display different type of data in OLED
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */
 
#include "key.h"
#include "adc.h"
#include "tim.h"
#include "bsp_uart.h"
#include "oled.h"
#include "USER_DEFINITION.h"
#include <stdlib.h>
#include <string.h>

//union KEY_Reg keyboard;
union SW_Reg SWstate;
extern rc_info_t rc;
key_state_t *keyboard ;

Key_STATUS bottom;
Key_STATUS key_X;
Key_STATUS key_R;

uint16_t kk;

void key_scan(void)
{
	memcpy(keyboard, &rc.key, 2);
	
	switch_scan();
	Key_GetStatus(&key_X, keyboard->X);
	Key_GetStatus(&key_R, keyboard->R);
	
	kk = HAL_ADC_GetValue(&hadc1)/100;
	Key_GetStatus(&bottom, (kk<35&&kk>30)?(1):(0));
}

void IOInit(void){
	
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_5, GPIO_PIN_SET);
	
	keyboard = (key_state_t *)malloc(sizeof(key_state_t));
	
	Key_GetStatusInit(&bottom, RISE_TRIGGER, COUNT_UP, ENABLE, 1, 3);
	Key_GetStatusInit(&key_X,  RISE_TRIGGER, COUNT_UP, ENABLE, 0, 0);
	Key_GetStatusInit(&key_R,  RISE_TRIGGER, COUNT_UP, ENABLE, 0, 0);
	
	oled_clear(Pen_Clear);
	oled_LOGO();
	oled_refresh_gram();
	
//	for(;;){
//		switch_scan();
//		if(SWstate.value == KEY_OFF_UP){
//			break;
//		}
//		TIM12->CCR1 = 250;
//	}
			
	TIM12->CCR1 = 0;
}

void switch_scan(void)
{
	SWstate.sw_buff.L=rc.sw1;
	SWstate.sw_buff.R=rc.sw2;
}

void buttom_scan(void)
{
	HAL_ADC_Start(&hadc1);
		
}

static int Key_GetStatusInit(Key_STATUS* key_t, 
															uint8_t triggerMode,
															uint8_t countMode,
															uint8_t vibration,
															uint32_t countMIN,
															uint32_t countMAX)
{
	key_t->Init.triggerMode = triggerMode;
	key_t->Init.countMode   = countMode;
	key_t->Init.vibration   = vibration;
	key_t->Init.countMIN    = countMIN;
	key_t->Init.countMAX    = countMAX;
	
	key_t->countNUM = countMode?countMAX:countMIN;
	
	if(countMIN >= countMAX)
	{ 
		key_t->Init.countMIN  = 0;
		key_t->Init.countMAX  = 0;
		return HAL_ERROR;
	} 
	else
	{
		return HAL_OK;
	}
}

void Key_GetStatus(Key_STATUS* key, uint8_t keystste)
{
	HAL_ADC_Start(&hadc1);
	uint8_t Read_Data = 0;  
	if(keystste)  
			Read_Data = 0x01;  
	else  
			Read_Data = 0x00;  

	key->trigger = Read_Data & (Read_Data ^ key->cont);  
	key->cont = Read_Data;  
	
	if(key->trigger)
	{  
		if(key->Init.triggerMode == 0)
		{
			if(key->trigger_times != 0xFF)
			{    
				key->trigger_times = 0xFF; 
				key->bit = 1-key->bit; 
				if(key->Init.countMode == 0)
				{
					key->countNUM++;
					if(key->countNUM > key->Init.countMAX)
					{
						key->countNUM = (key->Init.vibration == 0)?(key->Init.countMAX):(key->Init.countMIN);
					}
				} else{
					key->countNUM--;
					if(key->countNUM < key->Init.countMIN)
					{
						key->countNUM = (key->Init.vibration == 0)?(key->Init.countMIN):(key->Init.countMAX);
					}
				}
			}  
		} else{
			if(key->trigger_times == 0xFF)
			{    
				key->bit = 1-key->bit;
				if(key->Init.countMode == 0)
				{
					key->countNUM++;
					if(key->countNUM > key->Init.countMAX)
					{
						key->countNUM = (key->Init.vibration == 0)?(key->Init.countMAX):(key->Init.countMIN);
					}
				} else{
					key->countNUM--;
					if(key->countNUM < key->Init.countMIN)
					{
						key->countNUM = (key->Init.vibration == 0)?(key->Init.countMIN):(key->Init.countMAX);
					}
				}				
			} 
			if(key->trigger_times != 0xFF)
			{     
				key->trigger_times = 0xFF; 
			}  
		}	
  }
  else if(key->cont == 0)  
  {    
		key->trigger_times = 0x00;  
  }  
	osDelay(10);
}
