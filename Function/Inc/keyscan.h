#ifndef __KEYSCAN_H__
#define __KEYSCAN_H__

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "tim.h"
#include "oled.h"
#include "remotecontrol.h"
#include "USER_DEFINITION.h"
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

extern rc_info_t rc;
extern Key_STATUS bottom;
extern Key_STATUS key_X;

#endif 
