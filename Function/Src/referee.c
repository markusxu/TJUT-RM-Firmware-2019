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
#include <string.h>

extern re_info_t *re;
ext_power_heat_data_t power;

void refereeDataUnpack(void)
{
	if(re->cmd_id == 0x0202)
	{
		memcpy(&power,&re->data[0],14);
	}
}

