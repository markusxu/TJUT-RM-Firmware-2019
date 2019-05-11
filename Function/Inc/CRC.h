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
/** @file      CRC.h
 *  @version   1.0
 *  @date      May 2019
 *
 *  @brief     communicate with computer task
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */
 
#ifndef __CRC_H__
#define __CRC_H__

#include "stm32f4xx_hal.h"

typedef enum 
{
  CRC_FALSE    = 0x00U, 
  CRC_TURE     = 0x01U,
  CRC_ERROR    = 0x02U,
  CRE_OK       = 0x03U
} CRC_StatusTypeDef;

unsigned char Get_CRC8_Check_Sum(unsigned char *pchMessage,unsigned int dwLength,unsigned char ucCRC8);
unsigned int Verify_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
void Append_CRC8_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);

unsigned short int Get_CRC16_Check_Sum(unsigned char *pchMessage,unsigned int dwLength,unsigned short int wCRC);
unsigned int Verify_CRC16_Check_Sum(unsigned char *pchMessage, unsigned int dwLength);
void Append_CRC16_Check_Sum(unsigned char * pchMessage,unsigned int dwLength);

#endif
