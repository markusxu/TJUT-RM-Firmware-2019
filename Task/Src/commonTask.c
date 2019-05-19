/****************************************************************************
 *  Copyright (C) 2019 TJUT-RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of�
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.� See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
/** @file commonTask.c
 *  @version 1.0
 *  @date May 2019
 *
 *  @brief communicate with computer task
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */

#include "commonTask.h"
#include "usart.h"
#include "bsp_uart.h"
#include "oled.h"
#include "display.h"
#include "key.h"
#include "referee.h"
#include "referee_info.h"
#include <stdlib.h>
#include <string.h>

extern osTimerId chassisTimerId;
extern osTimerId gimbalTimerId;
extern key_state_t *keyboard;
extern uint8_t reTxData[12];

uint8_t page;

/**
 * @brief task of unpacking referee system data
 * 
 * @param argument 
 */
void modeSwitch_Task(void const * argument)
{
	for(;;)
	{
		if(SWstate.value == KEY_HL_DN)
		{
				
		}
	}
}

/**
 * @brief task of unpacking referee system data
 * 
 * @param argument 
 */
void unpack_Task(void const * argument)
{
	for(;;)
	{
		refereeDataUnpack();
	}
}

/**
 * @brief task of display
 * 
 * @param argument 
 */
void display_Task(void const * argument)
{
	oled_clear(Pen_Clear);
	oled_refresh_gram();
	
	for(;;)
	{
		switch(bottom.countNUM)
		{
			case 1:
			{
				pageClean(page, 1);
				display_refereeSystem();
				break;
			}
				
			case 2:
			{
				pageClean(page, 2);
				display_moto6020();
				break;
			}
			
			case 3:
			{
				pageClean(page, 3);
				display_rc();
				break;
			}
		}
		oled_refresh_gram();
	}
}
