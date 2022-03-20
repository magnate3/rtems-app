/*
 * Consume Ticks helper function. This file is part of the RTEMS Course 
 * Copyright (C) 2017-2020 University of Alcalá
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <consume_ticks.h>
#include <rtems.h>

void consume_ticks(uint32_t ticks)
{
	uint32_t previous_tick, current_tick;

	rtems_clock_get(RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &previous_tick);

	while (ticks > 0)
	{
		rtems_clock_get(RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &current_tick);
		if (current_tick != previous_tick)
		{
			previous_tick = current_tick;
			ticks--;
		}
	}

}
