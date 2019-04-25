#include "USER_chassis.h"

float MAX_WHEEL_SPEED = 6000;
double rcch[4];
int16_t Speed[4];

void ChsTask_Init(void){
	
	extern rc_info_t rc;
	ChassisPIDInit();
	
}

void ChsTask_Loop(void){
		keyboard.value = rc.key;
	
	switch (SWstate.value){
								
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
			rcch[0] = -rc.ch1*10;
			rcch[1] = -rc.ch2*10;
			rcch[2] = -rc.ch3*10;
			Mecanum_calc(rcch[0], rcch[1], rcch[2], MAX_WHEEL_SPEED, Speed);
			Set_M620_Current(Speed);
			break;
		
		case KEY_HL_DN:
			KeyboardContral();
			break;
		
		default:
			break;
			
		}
	
}

void KeyboardContral(void){

	rcch[1] = keyboard.Posision.W*(-3000) + keyboard.Posision.S*(3000);
	rcch[0] = keyboard.Posision.D*(-3000) + keyboard.Posision.A*(3000);
	
	if(keyboard.Posision.SHIFT || keyboard.Posision.CTRL){
		
		if(keyboard.Posision.SHIFT){
			rcch[1] *= 2;
			rcch[0] *= 2;
		}
		else if(keyboard.Posision.CTRL){
			rcch[1] *= 0.5;
			rcch[0] *= 0.5;
		}
	
	}

	rcch[2] = -rc.mouse.x*100;
		
	Mecanum_calc(rcch[0], rcch[1], rcch[2], MAX_WHEEL_SPEED, Speed);
	Set_M620_Current(Speed);
}
