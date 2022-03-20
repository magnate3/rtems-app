/*
 * Hello World RTEMS Project. Configuration file.
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

#ifndef __RTEMS_CONFIG_H__
#define __RTEMS_CONFIG_H__

#include <rtems.h>

rtems_task Init(rtems_task_argument arg);

/** Definition of the Console Driver */
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

/** Default value of microseconds per tick */
#define CONFIGURE_MICROSECONDS_PER_TICK	(10000)

/** Default value of ticks per timeslice */
#define CONFIGURE_TICKS_PER_TIMESLICE (50)

/** Maximum number of semaphores */
#define CONFIGURE_MAXIMUM_SEMAPHORES (0)

/** Maximum number of tasks */
#define CONFIGURE_MAXIMUM_TASKS      (1)

/**
 * Extra stack memory needed for the tasks. It must include all the memory
 * of the different tasks that exceeds of 4KiB per task.
 */
#define CONFIGURE_EXTRA_TASK_STACKS (3 * RTEMS_MINIMUM_STACK_SIZE)

/** 16 KB should be enough :) */
#define CONFIGURE_INIT_TASK_STACK_SIZE	   (4 * RTEMS_MINIMUM_STACK_SIZE)

/** Default Init task priority: maximum */
#define CONFIGURE_INIT_TASK_PRIORITY       1

/** Default initial task modes */
#define CONFIGURE_INIT_TASK_INITIAL_MODES (RTEMS_NO_PREEMPT | \
                                           RTEMS_NO_TIMESLICE | \
                                           RTEMS_INTERRUPT_LEVEL(0))

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER  /* for stdio */
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER    /* for time services */
/** Ensure that the default initialization table is defined */
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>

#endif /* __RTEMS_CONFIG_H__ */
