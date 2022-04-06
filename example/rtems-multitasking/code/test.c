/*
 *  COPYRIGHT (c) 1989-2012.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/printer.h>
#include <rtems/test.h>
#include <rtems/test-info.h>

#include <rtems.h>
#include <rtems/bspIo.h>

#include <bsp.h> /* for device driver prototypes */

#include <stdio.h>
#include <stdlib.h>

/* forward declarations to avoid warnings */
rtems_task Init(rtems_task_argument argument);

const char rtems_test_name[] = "Wait queue and Timer Manager";
rtems_printer rtems_test_printer;

/* TODO: define global variable counter */


/* TODO: define global variable reset_count */


/* TODO
 * Create a function wakeup_and_edit_counter
 * Reset global Counter every 0.25 seconds
 * and increase reset_count every 15 seconds
 */


/* TODO
 * Create a function wakeup_and_print that
 * Print out the value of counter
 * and print out the value of reset_count
 * then make the task 2 to sleep
 */


rtems_task Init(
        rtems_task_argument ignored
        )
{
    rtems_print_printer_printf(&rtems_test_printer);
    //rtems_test_begin("rtems_task Init", RTEMS_TEST_STATE_PASS);

    /* edit start */
    printf("Write two tasks that use Timer Manager to schedule a function that should execute every 0.25 seconds. \n" );

    /* TODO
     * Create first task
     * Calls wakeup_and_edit_counter
     * */

    /* TODO
     * Create Second task
     * calls wakeup_and_print
     * */


    /* TODO
     * Create Timer Manager using rtems_timer_create directive
     * Set interval of 0.25 sec using rtems_timer_fire_after
     */
    /* rtems_status_code rtems_timer_create(
       rtems_name name,
       rtems_id *id
       );

       rtems_status_code rtems_timer_fire_after(
       rtems_id id,
       rtems_interval ticks, 
       rtems_timer_service_routine_entry  routine,
       void *user_data 
       );

*/


    /* TODO
     * Create the RMS manager using rtems_rate_monotonic_create for the function
     * and allocate period of 15 sec using rtems_rate_monotonic_period
     */

    /* THe following code has dperiod of 100  and 40, change it to 0.25 and 5 */
    /* uncomment HERE */
    /*
    rtems_task Periodic_task(rtems_task_argument arg)
    {
        rtems_name        name_1, name_2;
        rtems_id          period_1, period_2;
        rtems_status_code status;

        name_1 = rtems_build_name( 'P', 'E', 'R', '1' );
        name_2 = rtems_build_name( 'P', 'E', 'R', '2' );

        (void ) rtems_rate_monotonic_create( name_1, &period_1 );
        (void ) rtems_rate_monotonic_create( name_2, &period_2 );

        while ( 1 ) {
            if ( rtems_rate_monotonic_period( period_1, 100 ) == RTEMS_TIMEOUT )
                break;

            if ( rtems_rate_monotonic_period( period_2, 40 ) == RTEMS_TIMEOUT )
                break;

            /*
             *      *  Perform first set of actions between clock
             *           *  ticks 0 and 39 of every 100 ticks.
             *                */
/*
            if ( rtems_rate_monotonic_period( period_2, 30 ) == RTEMS_TIMEOUT )
                break;

            /*
             *      *  Perform second set of actions between clock 40 and 69
             *           *  of every 100 ticks.  THEN ...
             *                *
             *                     *  Check to make sure we didn't miss the period_2 period.
             *                          */
/*
            if ( rtems_rate_monotonic_period( period_2, RTEMS_STATUS ) == RTEMS_TIMEOUT )
                break;

            (void) rtems_rate_monotonic_cancel( period_2 );
        }

        /* missed period so delete period and SELF */
/*
        (void ) rtems_rate_monotonic_delete( period_1 );
        (void ) rtems_rate_monotonic_delete( period_2 );
        (void ) task_delete( SELF );
    }

*/


    /* edit ends */
    //rtems_test_end("rtems_task Periodic_task end");
    exit( 0 );
}


/* NOTICE: the clock driver is explicitly disabled */
#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_MAXIMUM_TASKS            1

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

//#define CONFIGURE_INITIAL_EXTENSIONS RTEMS_TEST_INITIAL_EXTENSION

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
