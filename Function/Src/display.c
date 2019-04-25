#include "display.h"

extern rc_info_t rc;
extern imu_t  imu;
uint8_t haveData;
uint16_t fdkey;

void Display_Task(void const * argument)
{
	oled_clear(Pen_Clear);
	oled_refresh_gram();
	
	for(;;)
	{
		if(bottom.countNUM == 1)display_rc();
		if(bottom.countNUM == 2)display_moto6020();
		if(bottom.countNUM == 3)oled_clear(Pen_Clear);
		oled_refresh_gram();
	}

}

void display_rc(void)
{
	oled_printf(0,1,"CH1:%4d ",rc.ch1);
	oled_printf(0,10,"CH2:%4d",rc.ch2);
	oled_printf(1,1,"CH3:%4d ",rc.ch3);
	oled_printf(1,10,"CH4:%4d",rc.ch4);
} 

void display_moto6020(void)
{
	oled_printf(3,1,"TEMP_PIT: %2d",moto_pit.hall);
	oled_printf(4,1,"TEMP_YAW: %2d",moto_yaw.hall);
} 

