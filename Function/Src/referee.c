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
/** @file referee.c
 *  @version 1.0
 *  @date May 2019
 *
 *  @brief unpacking the data from referee system
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */

#include "referee.h"
#include "referee_info.h"
#include "bsp_uart.h"
#include "CRC.h"
#include <string.h>

extern re_info_t *re;
referee_data_t *re_data;

void refereeDataUnpack(void)
{
	uint16_t data_length = (uint16_t)(re->frame_header[1] | re->frame_header[2] << 8);
	
	switch(re->cmd_id)
	{
		case EXT_POWER_HEAT_DATA:
		{
			memcpy(&re_data->power_heat_data, &re->data, data_length);
			break;
		}
		
		case EXT_ROBO_STATE:
		{
			memcpy(&re_data->robot_state, &re->data, data_length);
			break;
		}
		
		case EXT_SHOOT_DATA:
		{
			memcpy(&re_data->shoot_data, &re->data, data_length);
			break;
		}
		
		default:
			break;
	}
}

void refereeDataPack()
{
	re_data->supply_booking->supply_projectile_id = re_data->supply_action->supply_projectile_id;
	if(re_data->supply_action->supply_robot_id == re_data->robot_state->robot_id)
	{
		re_data->supply_booking->supply_robot_id = re_data->robot_state->robot_id;
	}
	re_data->supply_booking->supply_num = 50;
}
