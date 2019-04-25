#include "USER_gimbal.h"

int16_t mouse_move_angle = 0;
uint8_t mouse_click_shoot = 0;

void GimTask_Init(void){
	
	extern rc_info_t rc;
	GimbalInit();

}

void GimTask_Loop(void){
	
	Angle_transimit();
		
	switch (SWstate.value){
		
		case KEY_OFF_UP:
			break;
		case KEY_CL_UP:
		case KEY_HL_UP:
			Set_Gimbal_Current(0, 0, 0);
			TIM2->CCR1 = 1000;
			LASER_OFF;
			break;
		
		case KEY_OFF_MD:
		case KEY_CL_MD:
		case KEY_HL_MD:
			Set_Gimbal_Current(rc.sw, -rc.ch4, 0);
			TIM2->CCR1 = 1000;
			LASER_OFF;
			break;
		
		case KEY_OFF_DN:
		case KEY_CL_DN:
			TIM2->CCR1 = 2000;
			Set_Gimbal_Current(rc.sw, -rc.ch4, 1200);
			LASER_ON;
			break;
		
		case KEY_HL_DN:
			MouseContral();
			break;
		
		default:
			break;
	}
	
}

void MouseContral(void){
	
	mouse_move_angle = mouse_move_angle + rc.mouse.y;
	(mouse_move_angle> 660)?(mouse_move_angle= 660):(mouse_move_angle);
	(mouse_move_angle<-660)?(mouse_move_angle=-660):(mouse_move_angle);
	
	(rc.mouse.press_r)?(TIM2->CCR1 = 1300):(TIM2->CCR1 = 1000);
	(rc.mouse.press_r && rc.mouse.press_l)?(mouse_click_shoot = 10):(mouse_click_shoot = 0);
	
	Set_Gimbal_Current(rc.sw, mouse_move_angle, mouse_click_shoot*100);
	
	if(key_X.bit){LASER_ON}else LASER_OFF;
		
}
