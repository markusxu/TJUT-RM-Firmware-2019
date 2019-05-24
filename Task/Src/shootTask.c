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
/** @file      shootTask.c
 *  @version   1.0
 *  @date      May 2019
 *
 *  @brief     Handle the referee heat data
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */
 
#include "shootTask.h"
#include "bsp_uart.h"
#include "referee_info.h"
#include "key.h"

extern referee_data_t reRxData;

uint8_t pokemode = 0;
uint16_t pokeSpeed = 0;

void shoot_Task(void const * argument)
{
	uint8_t coolingStatue = 0;
	
	/* Iintal Timer --------------------------------------------------------------*/
	uint32_t PreviousWakeTime = osKernelSysTick();
	
	for(;;)
	{
		osDelayUntil(&PreviousWakeTime,SHOOTTAKS_DELAY_TIMES);
    
    if(keyboard->F) pokemode = 1;
    if(keyboard->G) pokemode = 0;
		
		if(reRxData.robot_state.shooter_heat0_cooling_limit != 240 &&
       reRxData.robot_state.shooter_heat0_cooling_limit != 360 &&
       reRxData.robot_state.shooter_heat0_cooling_limit != 480) reRxData.robot_state.shooter_heat0_cooling_limit = 240;
		
		if(SWstate.sw_buff.R == 2 && SWstate.sw_buff.L != 2)
		{
			if(reRxData.power_heat_data.shooter_heat0 >= reRxData.robot_state.shooter_heat0_cooling_limit*0.8 || coolingStatue)
			{
				if(reRxData.power_heat_data.shooter_heat0 >= reRxData.robot_state.shooter_heat0_cooling_limit*0.95 || coolingStatue)
				{
					TIM2->CCR1 = 1400;
					TIM2->CCR2 = 1400;
					pokeSpeed = shootFequence(0);
					if(!coolingStatue) coolingStatue = 1;
				}
				else
				{
					TIM2->CCR1 = 1400;
					TIM2->CCR2 = 1400;
					pokeSpeed = shootFequence(2);
				}
			}
			else
			{
				TIM2->CCR1 = 1600;
				TIM2->CCR2 = 1600;
				pokeSpeed = shootFequence(4);
			}
		} 
    
		else if(SWstate.sw_buff.R == 2 && SWstate.sw_buff.L == 2)
    {
      if(pokemode/*rc.mouse.press_r*/)
      {
        
/******************************************************************
        if(reRxData.power_heat_data.shooter_heat0 >= reRxData.robot_state.shooter_heat0_cooling_limit*0.8 || coolingStatue)
        {


          else
          {
            TIM2->CCR1 = 1400;
            TIM2->CCR2 = 1400;
            if(rc.mouse.press_l)
              pokeSpeed = shootFequence(2);
          }
        }
*****************************************************************/
        
        if(reRxData.power_heat_data.shooter_heat0 >= reRxData.robot_state.shooter_heat0_cooling_limit*0.95 || coolingStatue)
        {
          TIM2->CCR1 = 1400;
          TIM2->CCR2 = 1400;
          pokeSpeed = shootFequence(0);
          if(!coolingStatue) coolingStatue = 1;
        }
        else
        {
          TIM2->CCR1 = 1600;//1400
          TIM2->CCR2 = 1600;//1400
          if(rc.mouse.press_l)
            pokeSpeed = shootFequence(3.8);
          else
            pokeSpeed = shootFequence(0);
        }
      }
      else
      {
        TIM2->CCR1 = 1000;
        TIM2->CCR2 = 1000;
        pokeSpeed = shootFequence(0);
      }
    }
    
    else
    {
			TIM2->CCR1 = 1000;
			TIM2->CCR2 = 1000;
			pokeSpeed = shootFequence(0);
		}
    
		if(coolingStatue && reRxData.power_heat_data.shooter_heat0 <= reRxData.robot_state.shooter_heat0_cooling_limit*0.8)
			coolingStatue = 0;
	}		
}

unsigned short int shootFequence(float Hz)
{
	return 308*Hz;
}
