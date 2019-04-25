/**
 ***************************************(C) COPYRIGHT 2018 DJI***************************************
 * @file       oled.h
 * @brief      this file contains sd card basic operating function
 * @note         
 * @Version    V1.0.0
 * @Date       Jan-28-2018      
 ***************************************(C) COPYRIGHT 2018 DJI***************************************
 */

#ifndef __REMOTECONTROL__H
#define __REMOTECONTROL__H

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "bsp_uart.h"

typedef struct {
	uint16_t W:     1;
	uint16_t S:     1;
	uint16_t A:     1;
	uint16_t D:     1;
	uint16_t SHIFT: 1;
	uint16_t CTRL:  1;
	uint16_t Q:     1;
	uint16_t E:     1;
	uint16_t R:     1;
	uint16_t F:     1;
	uint16_t G:     1;
	uint16_t Z:     1;
	uint16_t X:     1;
	uint16_t C:     1;
	uint16_t V:     1;
	uint16_t B:     1;
}KEY_STATE;

union KEY_Reg{
   uint16_t       value;
   KEY_STATE   Posision;
};

union SW_Reg{
  uint8_t    value;
  struct {
		uint8_t L:2;
		uint8_t R:2;
		uint8_t st:4;
	 }sw_buff;
};

extern union KEY_Reg keyboard;
extern union SW_Reg SWstate;

void RC_Data(void const * argument);
#endif
