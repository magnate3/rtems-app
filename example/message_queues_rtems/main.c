/*
 * Message Queue Server RTEMS Project
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

#include <rtems.h>

#include <rtems_config.h>

/** Luckily, we have the libc! :) */
#include <stdio.h>
#include <stdlib.h>

#define PRINT(fmt,args...)  printf ( fmt "\n",\
                            ##args)

#define PRINT_TIME(fmt,args...) do { \
			unsigned int __current_tick; \
			__current_tick=rtems_clock_get_ticks_since_boot();\
			printf ("%u: " fmt "\n", __current_tick, ##args); \
			} while (0)

#include <consume_ticks.h>

typedef struct {

	/** Sender Task ID */
	rtems_id sender_id;
	/** Telemetry Frame Counter */
	unsigned int counter;
	/** Data size */
	unsigned int data_size;
	/** Data buffer */
	char data[20];

} telemetry_t;

/** The one and only message queue */
rtems_id tm_message_queue;

/** Telemetry Server Task ID */
rtems_id telemetry_server_id;

/** Houskeeping Task ID */
rtems_id housekeeping_task_id;

/** ACS Task ID */
rtems_id acs_task_id;

/**
 * Telemetry downlink server demo task.
 *
 * This task must implement an infinite loop that does the following:
 *
 * 1) waits for an incoming message from the rest of the tasks.
 * 2) when a message arrives, it formats the message and "sends: it
 *    (i.e. it prints it).
 * 3) occupies the CPU for 1 tick
 */

rtems_task telemetry_server(rtems_task_argument argument)
{
	telemetry_t tm;
	size_t size;

	for (;;)
	{
		// TODO: Wait for a message

		// TODO: Simulate processing

		PRINT_TIME("Sent TM => %s | %u | %s",
				((tm.sender_id == housekeeping_task_id) ?
				"HK" : "ACS"),
				tm.data_size,
				tm.data);

	}
}

/**
 * Houskeeping demo task.
 *
 * This task must implement an infinite loop that does the following:
 *
 * 1) occupies the CPU for 2 ticks
 * 2) sends a telemetry
 * 3) sleeps for 10 ticks
 */

rtems_task housekeeping_task(rtems_task_argument argument)
{
	telemetry_t tm;
	tm.sender_id = housekeeping_task_id;
	tm.counter = 0;

	for (;;)
	{
		PRINT_TIME("HK Activation");

		// TODO: Simulate processing

		// Fill the telemetry packet
		strcpy(tm.data, "SYSTEM OK");
		tm.data_size = strlen(tm.data);
		tm.counter++;

		// TODO: Send the message

		// TODO: Wait until next execution

	}
}

/**
 * ACS demo task.
 *
 * This task must implement an infinite loop that does the following:
 *
 * 1) occupies the CPU for 40 ticks
 * 2) sends a telemetry
 * 3) sleeps for 100 ticks
 */
rtems_task acs_task(rtems_task_argument argument)
{
	telemetry_t tm;
	tm.sender_id = acs_task_id;
	tm.counter = 0;

	for (;;)
	{
		PRINT_TIME("ACS Activation");

		// TODO: Simulate processing

		// Fill the telemetry packet
		strcpy(tm.data, "ACS OK");
		tm.data_size = strlen(tm.data);
		tm.counter++;

		// TODO: Send the message

		// TODO: Wait until next execution

	}
}


rtems_task Init(rtems_task_argument arg)
{

	PRINT_TIME("Create the message queue \n");
	// TODO: Create the message queue

	// TODO: Create Telemetry Server

	// TODO: Start Telemetry Server

	// TODO: Create Housekeeping task

	// TODO: Start Housekeeping task

	// TODO: Create ACS task

	// TODO: Start ACS task

	/** Delete the initial task from the system */
	rtems_task_delete(RTEMS_SELF);

}
