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
/** @file commonTask.h
 *  @version 1.0
 *  @date May 2019
 *
 *  @brief display different type of data in OLED
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */
 
#ifndef __COMMONTASK_H__
#define __COMMONTASK_H__

#include "stm32f4xx_hal.h"

void modeSwitch_Task(void const * argument);
void display_Task(void const * argument);
void unpack_Task(void const * argument);

#endif
