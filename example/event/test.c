/*
 *  This file contains an example of a simple RTEMS
 *  application.  It instantiates the RTEMS Configuration
 *  Information using confdef.h and contains two tasks:
 *  a *  user initialization task and a simple task.
 *
 *  This example assumes that a board support package exists.
 */

#include <stdlib.h>
#include <stdio.h>
#include <bsp.h>
#include <rtems.h>

rtems_id waitingTask;

rtems_task user_application(rtems_task_argument argument);
rtems_task task_1(rtems_task_argument argument);

rtems_task Init(
  rtems_task_argument ignored
)
{

  rtems_id          tid;
  rtems_status_code status;
  rtems_name        name;

  name = rtems_build_name( 'A', 'P', 'P', '1' );

  status = rtems_task_create(
     name, 1, RTEMS_MINIMUM_STACK_SIZE,
     RTEMS_NO_PREEMPT, RTEMS_FLOATING_POINT, &tid
  );
  if ( status != RTEMS_SUCCESSFUL ) {
    printf( "1) rtems_task_create failed with status of %d.\n", status );
    exit(1);
  }

  status = rtems_task_start( tid, user_application, 0 );
  if ( status != RTEMS_SUCCESSFUL ) {
    printf( "1) rtems_task_start failed with status of %d.\n", status );
    exit( 1 );
  }

  /*
   * SECOND TASK
   * */

   rtems_id          tid_2;
   rtems_status_code status_2;
   rtems_name        name_2;

   name_2 = rtems_build_name( 'A', 'P', 'P', '2' );

   status_2 = rtems_task_create(
		   name_2, 1, RTEMS_MINIMUM_STACK_SIZE,
      RTEMS_NO_PREEMPT, RTEMS_FLOATING_POINT, &tid_2
   );
   if ( status_2 != RTEMS_SUCCESSFUL ) {
     printf( "2) rtems_task_create failed with status of %d.\n", status );
     exit(1);
   }
   else
	  waitingTask = tid_2;

   status_2 = rtems_task_start( tid_2, task_1, 0 );
   if ( status_2 != RTEMS_SUCCESSFUL ) {
     printf( "2) rtems_task_start failed with status of %d.\n", status );
     exit( 1 );
   }

  /*
   * END OF SECOND TASK
   * */

  status = rtems_task_delete( RTEMS_SELF );    /* should not return */
  printf( "rtems_task_delete returned with status of %d.\n", status );
  exit( 1 );
}


rtems_task user_application(rtems_task_argument argument)
{
	/* application specific initialization goes here */
	while ( 1 )  {              /* infinite loop */
		/*  APPLICATION CODE GOES HERE
		 *
		 *  This code will typically include at least one
		 *  directive which causes the calling task to
		 *  give up the processor.
		 */
		printf("Main task is now started... \nSending event to secondary task soon...\n");
		rtems_task_wake_after(10);

		rtems_event_send(
		waitingTask,
		RTEMS_EVENT_1
		);

		printf("Event to secondary task has been sent... \n");
		printf("Quitting current task... \n");
		rtems_task_delete ( RTEMS_SELF );
		exit(1);

	}
}

rtems_task task_1(rtems_task_argument argument){
	while(1){
		rtems_status_code returning;
		rtems_event_set out;

		printf("Waiting Task is now started... \nWaiting for event to be received...\n");

		returning = rtems_event_receive(
		RTEMS_EVENT_1,
		RTEMS_EVENT_ALL | RTEMS_WAIT,
		RTEMS_NO_TIMEOUT,
		&out
		);

		switch(returning){
		case RTEMS_SUCCESSFUL: printf("Received Event Successfully..."); break;
		default: printf("Event NOT received successfully...\n"); break;
		};


		rtems_task_wake_after(5);

		printf("Quitting current task... \n");
		rtems_task_delete ( RTEMS_SELF );
		exit(1);
	}
}

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER  /* for stdio */
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER    /* for time services */

#define CONFIGURE_MAXIMUM_TIMERS 1
#define CONFIGURE_MAXIMUM_TASKS 4
#define CONFIGURE_MAXIMUM_PARTITIONS 1
#define maximum_global_objects 10

#define CONFIGURE_INIT_TASK_NAME rtems_build_name( 'E', 'X', 'A', 'M' )
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>
