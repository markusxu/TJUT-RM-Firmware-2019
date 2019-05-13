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
/** @file chassisTask.c
 *  @version 1.0
 *  @date May 2019
 *
 *  @brief communicate with computer task
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */

#include "chassisTask.h"

Move_State	ChassisMoveState = MOVE_NONE;

extern rc_info_t *rc;
extern key_state_t *keyboard;

Chassis_TypeDef Chassis1;
float MAX_WHEEL_SPEED = 6000;
double rcch[4];
int16_t Speed[4];

void Mecanum_calc(float vx, float vy, float omega, const int each_max_spd, int16_t speed[]){
	int16_t buf[4];
	int i;
	float max=0, rate;
	
	vx = vx > MAX_CHASSIS_VX_SPEED ? MAX_CHASSIS_VX_SPEED : vx;
	vx = vx < -MAX_CHASSIS_VX_SPEED ? -MAX_CHASSIS_VX_SPEED : vx;	
	vy = vy > MAX_CHASSIS_VY_SPEED ? MAX_CHASSIS_VY_SPEED : vy;
	vy = vy < -MAX_CHASSIS_VY_SPEED ? -MAX_CHASSIS_VY_SPEED : vy;
	omega = omega > MAX_CHASSIS_OMEGA_SPEED ? MAX_CHASSIS_OMEGA_SPEED : omega;
	omega = omega < -MAX_CHASSIS_OMEGA_SPEED ? -MAX_CHASSIS_OMEGA_SPEED : omega;
	
#ifdef DEBUG_REVERSE
	buf[0] = ( -vx + vy + omega );
	buf[1] = ( -vx - vy + omega );
	buf[2] = ( +vx + vy + omega );
	buf[3] = ( +vx - vy + omega ); 
#endif	
	
	
#ifdef CHASSIS_OLD
	buf[0] = ( -vx + vy - omega );
	buf[1] = ( -vx - vy - omega );
	buf[2] = ( +vx - vy - omega );
	buf[3] = ( +vx + vy - omega );  
#else 
	buf[0] = ( vx + vy + omega );
	buf[1] = -( vx - vy - omega );
	buf[2] = ( vx - vy + omega );
	buf[3] = -( vx + vy - omega );  
#endif

	for(i=0; i<4; i++){
		if ( MyAbs(buf[i]) > max )
			max = MyAbs(buf[i]) ;
	}
	if (max > each_max_spd){
		rate = each_max_spd / max;
		for(i=0; i<4; i++)
			buf[i] *= rate;
	}
	//output
	memcpy(speed, buf, sizeof(s16)*4); 
}

void ChassisPIDInit(void){

	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);
	
	my_can_filter_init_recv_all(&hcan1);
	HAL_CAN_Receive_IT(&hcan1, CAN_FIFO0);
	HAL_CAN_Receive_IT(&hcan2, CAN_FIFO0);
	
	#if defined CAN_CONTROL
	
//	PID_struct_init(&pid_omg, POSITION_PID, 16384, 20000,
//									1.5f,	0.1f,	0.0f	);  //angular rate closeloop.
	
	for(int i=0; i<4; i++)
	{
		PID_struct_init(&pid_spd[i], POSITION_PID, 3000, 2000,
									CHASSIS_KP,	CHASSIS_KI,	CHASSIS_KD	);  //4 motos angular rate closeloop.
	}
	
	#elif defined PWM_CONTROL
		__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_1, 1000);
		__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 1000);
		__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_3, 1000);
		__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_4, 1000);	//ppm must be 1000 at first time.
		HAL_Delay(100);
	#endif

}

void Set_M620_Current(int16_t set_spd[]){

	#if defined CAN_CONTROL
		
		for(int i=0; i<4; i++)
		{
			pid_calc(&pid_spd[i], moto_chassis[i].speed_rpm, set_spd[i]);
		}
		set_moto_current(&hcan1, pid_spd[0].pos_out, 
								pid_spd[1].pos_out,
								pid_spd[2].pos_out,
								pid_spd[3].pos_out, 
								0x00);
		
	#elif defined PWM_CONTROL
		__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_1, 1000+set_spd[0]);//spd range[0,999]
		__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, 1000+set_spd[1]);
		__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_3, 1000+set_spd[2]);
		__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_4, 1000+set_spd[3]);
		//TIM5->CCR1 = set_spd[0];
	#endif

	osDelay(10);

}



void Chassis_Task(void const * argument)
{
	ChassisPIDInit();
	
	uint32_t PreviousWakeTime = osKernelSysTick();
	uint32_t DelayTime        = 10;
	
	for(;;)
	{
		osDelayUntil(&PreviousWakeTime,DelayTime);
		
		switch (SWstate.value)
		{						
			case KEY_OFF_UP:
			case KEY_OFF_MD:
			case KEY_OFF_DN:
				break;
			
			case KEY_CL_UP:
			case KEY_CL_MD:
			case KEY_CL_DN:
				for(int i=0; i<4;i++){
					Speed[i]=0;
				}
				Set_M620_Current(Speed);
				break;
			
			case KEY_HL_UP:
			case KEY_HL_MD:
				rcch[0] = -rc->ch1*10;
				rcch[1] = -rc->ch2*10;
				rcch[2] = -rc->ch3*10;
				Mecanum_calc(rcch[0], rcch[1], rcch[2], MAX_WHEEL_SPEED, Speed);
				Set_M620_Current(Speed);
				break;
			
			case KEY_HL_DN:
			{
				rcch[1] = keyboard->W*(-3000) + keyboard->S*(3000);
				rcch[0] = keyboard->D*(-3000) + keyboard->A*(3000);
				
				if(keyboard->SHIFT || keyboard->CTRL)
				{
					if(keyboard->SHIFT)
					{
						rcch[1] *= 2;
						rcch[0] *= 2;
					}
					else if(keyboard->CTRL)
					{
						rcch[1] *= 0.5;
						rcch[0] *= 0.5;
					}
				}
				rcch[2] = -rc->mouse.x*100;
				Mecanum_calc(rcch[0], rcch[1], rcch[2], MAX_WHEEL_SPEED, Speed);
				Set_M620_Current(Speed);
				break;
			}
			
			default:
				break;
		}
	}
}


