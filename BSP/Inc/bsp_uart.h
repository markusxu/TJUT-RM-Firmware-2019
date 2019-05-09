/****************************************************************************
 *  Copyright (C) 201 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of�
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.� See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
/** @file      bsp_usrt.h
 *  @version   1.0.0
 *  @date      Jan-30-2018
 *
 *  @brief     This file contains the common defines and functions prototypes for 
 *             the bsp_uart.c driver
 *
 *  @copyright 2018 RoboMaster. All rights reserved.
 *
 */

#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include "usart.h"

#define UART_RX_DMA_SIZE (1024)

/* For dji remote controler reciever */
#define DBUS_MAX_LEN     (50)
#define DBUS_BUFLEN      (18)
#define DBUS_HUART       huart1 

/* For referee system reciever */
#define RE_MAX_LEN     (128)
#define RE_BUFLEN      (128)
#define RE_HUART       huart3 

/* For PC reciever */
#define PC_MAX_LEN     (8)
#define PC_BUFLEN      (8)
#define PC_HUART       huart6 

/** 
  * @brief  mouse control information
  */
typedef __packed struct
{
	/* mouse move information */
	int16_t x;
	int16_t y;
	int16_t z;
	
	/* mouse move information */
	uint8_t press_l ;
	uint8_t press_r;
} mouse_info_t;

/** 
  * @brief  remote control information
  */
typedef struct
{
  /* rocker channel information */
  int16_t ch1;
  int16_t ch2;
  int16_t ch3;
  int16_t ch4;

  /* left and right lever information */
  uint8_t sw1;
  uint8_t sw2;
	int16_t sw;
	
	/* PC control information */
	mouse_info_t mouse;
	uint16_t key;
} rc_info_t;

typedef __packed struct
{
	uint8_t  frame_header[5];
	uint16_t cmd_id;
	uint8_t  data[119];
	uint16_t CRC16;
} re_info_t;

typedef __packed struct
{
	uint8_t  frame_header;
	uint16_t yaw_angle;
	uint16_t pit_angle;
	uint16_t retain;
	uint8_t  frame_tail;
} pc_info_t;

void uart_receive_handler(UART_HandleTypeDef *huart);
void Dbus_USRT_Init(void);
void Referee_USRT_Init(void);
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
#endif

