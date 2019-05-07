/**
 ***************************************(C) COPYRIGHT 2018 DJI***************************************
 * @file       display.h
 * @brief      
 * @note         
 * @Version    V1.0.0
 * @Date       Jan-28-2018      
 ***************************************(C) COPYRIGHT 2018 DJI***************************************
 */

#ifndef __DISPLAY__H 
#define __DISPLAY__H

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

void display_rc(void);
void display_moto6020(void);
void display_refereeSystem(void);
void Display_Task(void const * argument);

#endif
