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


union SW_Reg{
  uint8_t    value;
  struct {
		uint8_t L:2;
		uint8_t R:2;
		uint8_t st:4;
	 }sw_buff;
};

//extern union KEY_Reg keyboard;
extern union SW_Reg SWstate;

#endif
