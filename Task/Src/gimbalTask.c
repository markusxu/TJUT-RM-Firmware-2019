/****************************************************************************
 *  Copyright (C) 2019 TJUT-RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of?
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.? See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
/** @file gimbalTask.c
 *  @version 1.0
 *  @date May 2019
 *
 *  @brief communicate with computer task
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */
 
#include "gimbalTask.h"
#include "can.h"
#include "tim.h"
#include "bsp_can.h"
#include "bsp_uart.h"
#include "pid.h"
#include "key.h"
#include "USER_DEFINITION.h"
#include <math.h>

extern rc_info_t rc;
extern uint16_t pokeSpeed;

int16_t mouse_move_angle;
uint8_t mouse_click_shoot;

void Gimbal_Task(void const * argument)
{
	GimbalInit();
	
	/* Iintal Timer --------------------------------------------------------------*/
	uint32_t PreviousWakeTime = osKernelSysTick();
	
	for(;;)
	{
		osDelayUntil(&PreviousWakeTime,GIMBALTAKS_DELAY_TIMES);
		
		Angle_transimit();
		
		switch (SWstate.value)
		{
			case KEY_OFF_UP:
//				Set_Gimbal_Current(0, 450, pokeSpeed);
				break;
			case KEY_CL_UP:
			case KEY_HL_UP:
				Set_Gimbal_Current(0, 0, pokeSpeed);
				LASER_OFF;
				break;
			
			case KEY_OFF_MD:
			case KEY_CL_MD:
			case KEY_HL_MD:
				Set_Gimbal_Current(rc.sw*2, -rc.ch4, pokeSpeed);
				TIM2->CCR3 = 950;
				LASER_OFF;
				break;
			
			case KEY_OFF_DN:
			case KEY_CL_DN:
				Set_Gimbal_Current(rc.sw*2, -rc.ch4, pokeSpeed);
				TIM2->CCR3 = 1600;
				LASER_ON;
				break;
			
			case KEY_HL_DN:
			{
        if(keyboard->E)
          TIM2->CCR3 = 950;
        if(keyboard->R)
          TIM2->CCR3 = 1600;
        
				mouse_move_angle = mouse_move_angle + rc.mouse.y*2;
				(mouse_move_angle> 500)?(mouse_move_angle= 500):(mouse_move_angle);
				(mouse_move_angle<-500)?(mouse_move_angle=-500):(mouse_move_angle);
				
				/***********************************************************
				if(rc->mouse.press_r){TIM2->CCR1 = 1500; TIM2->CCR2 = 1500;} 
				else                 {TIM2->CCR1 = 1000; TIM2->CCR2 = 1000;}
				***********************************************************/
				
				/*(rc.mouse.press_r && rc.mouse.press_l)?(mouse_click_shoot = 10):(mouse_click_shoot = 0);*/
				
				Set_Gimbal_Current(rc.sw, mouse_move_angle, pokeSpeed);
				
				if(key_X.bit){LASER_ON}else LASER_OFF;
				break;
			}
			
			default:
				break;
		}
	}
}

void GimbalPIDInit(void){

	PID_struct_init(&pid_yaw, POSITION_PID, 30000, 5000,
									GIMBAL_YAW_KP, GIMBAL_YAW_KI, GIMBAL_YAW_KD);
  
	PID_struct_init(&pid_pit, POSITION_PID, 4096, 4096,
									3.3f, 0.1f, 10.0f);
  PID_struct_init(&pid_pit_omg, POSITION_PID, 30000, 5000,
									30.0f, 0.1f, 0.0f);
  
	PID_struct_init(&pid_poke, POSITION_PID, 16384, 5000,
									1.5f,	0.1f,	0.0f);
	HAL_Delay(100);

}

void GimbalInit(void){
		
	GimbalPIDInit();

	/*Initial Friction Wheel*/
	HAL_TIM_PWM_Start(&POKE_TIM_STRUCT, POKE_TIM_CHANNEL);

	moto_yaw.correcting_angle = YAW_CORRECTING_ANGLE; 
	moto_pit.correcting_angle = PIT_CORRECTING_ANGLE;
	
	moto_yaw.offset_angle = YAW_OFFSET_ANGLE; 
	moto_pit.offset_angle = PIT_OFFSET_ANGLE;
}

void Set_Gimbal_Current(int16_t yaw_target_spd, int16_t pit_target_spd, int16_t set_spd){
	
	pid_calc(&pid_yaw, moto_yaw.real_angle + moto_yaw.offset_angle, yaw_target_spd);
  
	pid_calc(&pid_pit, moto_pit.real_angle + moto_pit.offset_angle, pit_target_spd);
  pid_calc(&pid_pit_omg, moto_pit.real_current, pid_pit.pos_out);
  
	pid_calc(&pid_poke, moto_poke.speed_rpm, set_spd);

	set_moto_current(&hcan1, 
									 pid_yaw.pos_out,
									 pid_pit_omg.pos_out, 
									 pid_poke.pos_out, 
									 0, 0x01);


	osDelay(10);

}

void Angle_transimit(void){
	
	moto_pit.real_angle = (moto_pit.correcting_angle >= 4096)?
												(((moto_pit.angle <= 8192 && moto_pit.angle > moto_pit.correcting_angle-4096)?(moto_pit.angle):(moto_pit.angle+8192)) - moto_pit.correcting_angle):
												(((moto_pit.angle <= 8192 && moto_pit.angle > moto_pit.correcting_angle+4096)?(moto_pit.angle-8192):(moto_pit.angle)) - moto_pit.correcting_angle);
	
	
	
	
	moto_yaw.real_angle = (moto_yaw.correcting_angle >= 4096 )?
												(((moto_yaw.angle <= 8192 && moto_yaw.angle > moto_yaw.correcting_angle-4096)?(moto_yaw.angle):(moto_yaw.angle+8192)) - moto_yaw.correcting_angle):
												(((moto_yaw.angle <= 8192 && moto_yaw.angle > moto_yaw.correcting_angle+4096)?(moto_yaw.angle-8192):(moto_yaw.angle)) - moto_yaw.correcting_angle);
	
}

/**
 * void Set_GM6020_Current(int16_t target_spd)
 * {
 * 	pid_calc(&pid_pit, moto_pit.speed_rpm, target_spd);
 * 	set_motor_voltage(&hcan1, 
 *                     pid_pit.pos_out, 
 *                     pid_pit.pos_out, 
 *                     pid_poke.pos_out, 
 *                     0);
 *    
 * }
 */
