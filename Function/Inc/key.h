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
/** @file key.h
 *  @version 1.0
 *  @date May 2019
 *
 *  @brief display different type of data in OLED
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */
 
#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

typedef enum
{

	KEY_OFF_UP = 0x05,
	KEY_OFF_MD = 0x0D,
	KEY_OFF_DN = 0x09,
	
	KEY_CL_UP = 0x07,
	KEY_CL_MD = 0x0F,
	KEY_CL_DN = 0x0B,
	
	KEY_HL_UP = 0x06,
	KEY_HL_MD = 0x0E,
	KEY_HL_DN = 0x0A,
	
}SW_STATE;

typedef enum
{
	Buttom_UP    = 24,
	Buttom_DOWN  = 32,
	Buttom_LEFT  = 8,
	Buttom_RIGHT = 17,
	Buttom_MID   = 0,
	
}Buttom_STATE;

typedef enum
{
	 RISE_TRIGGER = 0U,
	 DROP_TRIGGER = 1U,
	
	 COUNT_UP    = 0U,
	 COUNT_DOWN  = 1U,
	
}Key_GetStatusInit_Parameters;

typedef __packed struct 
{
	uint16_t W:     1;
	uint16_t S:     1;
	uint16_t A:     1;
	uint16_t D:     1;
	uint16_t SHIFT: 1;
	uint16_t CTRL:  1;
	uint16_t Q:     1;
	uint16_t E:     1;
	uint16_t R:     1;
	uint16_t F:     1;
	uint16_t G:     1;
	uint16_t Z:     1;
	uint16_t X:     1;
	uint16_t C:     1;
	uint16_t V:     1;
	uint16_t B:     1;
} key_state_t;

typedef __packed struct 
{
		uint8_t L:2;
		uint8_t R:2;
		uint8_t Retain:4;
} switch_tatus_t;

typedef struct
{
	uint8_t triggerMode:1;
	uint8_t countMode:1;
	uint8_t vibration:1;
	
	uint32_t countMAX;
	uint32_t countMIN;

}Buttom_STATUS_Initial;


typedef struct  
{  
	Buttom_STATUS_Initial Init;
	
	uint8_t trigger;
	uint8_t cont   ;
 
	uint8_t trigger_times;
	
	uint8_t  bit; 
	uint32_t countNUM;
	
}Key_STATUS; 

typedef struct {
int a;
int b;
}STR3;

void key_scan(void);
void IOInit(void);
void switch_scan(void);
void buttom_scan(void);
void Key_GetStatus(Key_STATUS* buttom, uint8_t keystste);
static int Key_GetStatusInit(Key_STATUS* key_t, 
															uint8_t triggerMode,
															uint8_t countMode,
															uint8_t vibration,
															uint32_t countMIN,
															uint32_t countMAX);

extern Key_STATUS bottom;
extern Key_STATUS key_X;

#endif 
