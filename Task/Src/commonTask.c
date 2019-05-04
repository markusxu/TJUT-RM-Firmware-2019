/****************************************************************************
 *  Copyright (C) 2019 TJUT-RoboMaster.
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
/** @file commonTask.c
 *  @version 1.0
 *  @date May 2019
 *
 *  @brief communicate with computer task
 *
 *  @copyright 2019 TJUT RoboMaster. All rights reserved.
 *
 */

#include "commonTask.h"
#include "oled.h"
#include "display.h"
#include "keyscan.h"
#include "remotecontrol.h"
#include <string.h>

/**
 * @brief task of display
 * 
 * @param argument 
 */
void display_Task(void const * argument)
{
	oled_clear(Pen_Clear);
	oled_refresh_gram();

	for(;;)
	{
		if(bottom.countNUM == 1)display_rc();
		if(bottom.countNUM == 2)display_moto6020();
		if(bottom.countNUM == 3)oled_clear(Pen_Clear);
		oled_refresh_gram();
	}

}
