/**
 ***************************************(C) COPYRIGHT 2019 TJUT***************************************
 * @file       gimbal.c
 * @brief      
 * @note         
 * @Version    V1.0.0
 * @Date       Mar-09-2019      
 ***************************************(C) COPYRIGHT 2019 TJUT***************************************
 */
 
#include "gimbal.h"

int16_t ddangle;

void GimbalPIDInit(void){

	PID_struct_init(&pid_yaw, POSITION_PID, 30000, 2000,
									GIMBAL_YAW_KP, GIMBAL_YAW_KI, GIMBAL_YAW_KD);
	PID_struct_init(&pid_pit, POSITION_PID, 30000, 2000,
									GIMBAL_PIT_KP, GIMBAL_PIT_KI, GIMBAL_PIT_KD);
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
	pid_calc(&pid_poke, moto_poke.speed_rpm, set_spd);

	set_moto_current(&hcan1, 
									 pid_yaw.pos_out,
									 pid_pit.pos_out, 
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

/**********************************************************
void Set_GM6020_Current(int16_t target_spd){
	
		pid_calc(&pid_pit, moto_pit.speed_rpm, target_spd);
    set_motor_voltage(&hcan1, 
                      pid_pit.pos_out, 
                      pid_pit.pos_out, 
                      pid_poke.pos_out, 
                      0);
    
}
**********************************************************/

void Gimbal_Task(void const * argument){
	
	GimTask_Init();

	for(;;){
		
		GimTask_Loop();
		
	}
	
	
}
