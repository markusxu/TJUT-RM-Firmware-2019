/****************************************************************************
 *  Copyright (C) 2019 TJUT-RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
/** @file display.c
 *  @version 1.0
 *  @date May 2019
 *
 *  @brief display different type of data in OLED
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */
 
#include "display.h"
#include "bsp_uart.h"
#include "bsp_imu.h"
#include "bsp_can.h"
#include "oled.h"
#include "keyscan.h"
#include "remotecontrol.h"
#include "chassis.h"

extern rc_info_t rc;

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
