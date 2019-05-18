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
/** @file chassisTask.h
 *  @version 1.0
 *  @date May 2019
 *
 *  @brief communicate with computer task
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */

#ifndef __CHASSIA_TASK_H__
#define __CHASSIA_TASK_H__

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h" 

#define CHASSIATASK_DELAY_TIMES 10

#ifdef EC60
	#define Max_WheelSpeed 2500  
#else
	#define Max_WheelSpeed 850
#endif

#define 	Gyro_Ratio  1 // (1.651376146f)  
#define 	PI 					(3.1415926535898f)

#define MyAbs(x) 	( (x>0) ? (x) : (-x) )

//#define MAX_WHEEL_SPEED						3600//300
#define MAX_CHASSIS_VX_SPEED			14000//3200//150
#define MAX_CHASSIS_VY_SPEED			14000//4000//150
#define MAX_CHASSIS_OMEGA_SPEED		10000//300
#define MAX_FOLLOW_SPEED          6000

#define CHASSIS_OLD
//#define DEBUG_REVERSE		//2 Different Chassis


//int16_t Buff_3508iq[4];

typedef enum
{
	Ctrl_Mode_RemoteControl = 1,
	Ctrl_Mode_KeyBoard_OpenLoop = 3, //Openloop angular velocity
	Ctrl_Mode_KeyBoard_CloseLoop = 2,//CloseLoop angular velocity
	
	
	CHASSIS_STOP,	//stall
	CHASSIS_RELAX,	//relax
	CHASSIS_OPEN_LOOP,
	CHASSIS_CLOSE_GYRO_LOOP,
	CHASSIS_FOLLOW_GIMBAL_ENCODER,
	
}ChassisMode; 

typedef enum{
	MOVE_NONE=0,	//no move, just move accoding by rc.
	MOVE_Y_LINE,  //move a straight line, then stop,
	MOVE_SQUARE,
	MOVE_CIRCLE,
}Move_State;

typedef struct 
{
	//float my_normal_speed;   //Chassis Closing Cpeed
	float vx;       //X-Direction Partial Velocity	Forward/Back
	float vy;				//Y-Direction Partial Velocity	Left/Right
	float omega;		//W angular velocity  To calc matrix, Target omega
	float vx1;
	float vy1;
	float vy3;
	float vy4;
	float vybiaoshi;
	float vxbiaoshi;
	float vvv;
	float omega_biaoshi;
	float omega1;		   //W angular velocity  To calc matrix, Target omega
	float vx2;       //X-Direction Partial Velocity	Forward/Back
	float vy2;				 //Y-Direction Partial Velocity	Left/Right
	float omega2;		
	float WW;      
	float WW1;				
	float WW2;		
  float vz;
	float kb_vx;
	float kb_vy;
	float mouse_omega;
	ChassisMode mode;
	ChassisMode last_mode;
	float target_angle;
	float angle_from_gyro;
	float omega_from_gyro; //measure omega
	float last_angle;
	int		is_snipe_mode;	
	int anti_attack;
}Chassis_TypeDef;

/* function define */
void Mecanum_calc(float vx, float vy, float omega, const int each_max_spd, int16_t speed[]);
void ChassisPIDInit(void);
void Set_M620_Current(int16_t set_spd[]);
void Chassis_Task(void const *argu);


extern Chassis_TypeDef Chassis1;

#endif
