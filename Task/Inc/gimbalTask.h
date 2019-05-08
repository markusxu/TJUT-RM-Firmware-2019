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
/** @file gimbalTask.h
 *  @version 1.0
 *  @date May 2019
 *
 *  @brief communicate with computer task
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */
 
#ifndef __GIMBAL_TASK_H__
#define __GIMBAL_TASK_H__

#include "stm32f4xx_hal.h"
#include "cmsis_os.h" 

void GimbalPIDInit(void);
void GimbalInit(void);
void Set_Gimbal_Current(int16_t yaw_target_spd, int16_t pit_target_spd, int16_t set_spd);
//void Set_GM6020_Current(int16_t target_spd);
void Angle_transimit(void);
void Gimbal_Task(void const *argu);

#endif
