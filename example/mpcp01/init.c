
#define CONFIGURE_INIT
#define CONFIGURE_MAXIMUM_USER_EXTENSIONS 1
#include "system.h"
#include "stdio.h"
#include <assert.h>

rtems_id sid;   // Semaphore ID
rtems_id tasks[4];
rtems_status_code rsc; //tmp variable for status code
rtems_id scheds[2]; //scheduler ids
rtems_id schid;

rtems_task task0_entry(rtems_task_argument argument);
rtems_task task1_entry(rtems_task_argument argument);
rtems_task task2_entry(rtems_task_argument argument);
rtems_task task_loop_entry(rtems_task_argument argument);  

void busy_wait();
void print_name( rtems_id id );
void init_sched();

void init_sched(
)
{
  uint32_t cpu_index;
  printf( "PROCESSOR COUNT: %d\n",rtems_scheduler_get_processor_maximum());
  //printf( "PROCESSOR COUNT: %d\n",rtems_get_processor_count() );
    
  for ( cpu_index = 0; cpu_index < 2; cpu_index++ ) {
    rsc = rtems_scheduler_ident_by_processor( cpu_index, &scheds[cpu_index] );
    printf( "rtems_scheduler_by_processor(%d, &scheds[%d]): %s\n", cpu_index,cpu_index, rtems_status_text( rsc )  );
    printf( "%d\n",scheds[cpu_index] );
  }
}

rtems_task init(
rtems_task_argument argument
)
{
  printf("TEST START:\n");
  //init_extensions();
  init_sched();
  
  /* Normal Task: */
  rsc = rtems_task_create(
    rtems_build_name( 'T', 'A', 'S', '0' ), 
    1,
    RTEMS_MINIMUM_STACK_SIZE, RTEMS_PREEMPT,
    RTEMS_NO_FLOATING_POINT,
    &tasks[0]
  );
  printf( "Create task: %s\n", rtems_status_text( rsc ) );

  rsc = rtems_task_create(
    rtems_build_name( 'T', 'A', 'S', '1' ),
    69,
    RTEMS_MINIMUM_STACK_SIZE, RTEMS_PREEMPT,
    RTEMS_NO_FLOATING_POINT, 
    &tasks[1]
  );
  printf( "Create task: %s\n", rtems_status_text( rsc ) );

  rsc = rtems_task_create(
    rtems_build_name( 'T', 'A', 'S', '2' ),
    1,
    RTEMS_MINIMUM_STACK_SIZE, RTEMS_PREEMPT,
    RTEMS_NO_FLOATING_POINT, 
    &tasks[2]
  );
  printf( "Create task: %s\n", rtems_status_text( rsc ) );

  rsc = rtems_task_create(
    rtems_build_name( 'T', 'A', 'S', '3' ), 
    69,
    RTEMS_MINIMUM_STACK_SIZE, RTEMS_PREEMPT,
    RTEMS_NO_FLOATING_POINT, &tasks[3]
  );
  printf( "Create task: %s\n", rtems_status_text( rsc ) );
/*
   RTEMS_MULTIPROCESSOR_RESOURCE_SHARING
      | RTEMS_PRIORITY_CEILING
      | RTEMS_BINARY_SEMAPHORE
      | RTEMS_PRIORITY
      RTEMS_MULTIPROCESSOR_RESOURCE_SHARING
      | RTEMS_INHERIT_PRIORITY
      | RTEMS_BINARY_SEMAPHORE
      | RTEMS_PRIORITY
  RTEMS_MULTIPROCESSOR_RESOURCE_SHARING
      | RTEMS_BINARY_SEMAPHORE
      | RTEMS_FIFO
    ( RTEMS_BINARY_SEMAPHORE | RTEMS_MULTIPROCESSOR_RESOURCE_SHARING | RTEMS_PRIORITY_CEILING |  RTEMS_PRIORITY),
*/
  
  rsc = rtems_semaphore_create(
    rtems_build_name( 'M', 'P', 'C', 'P' ),
    1,
 RTEMS_BINARY_SEMAPHORE | RTEMS_PRIORITY_CEILING | RTEMS_PRIORITY,
    1,
    &sid
  );
  printf( "Create MPCP Semaphore: %s\n", rtems_status_text( rsc ) );

  /* Binding tasks to processor */
  rtems_task_set_scheduler( tasks[0], scheds[0], 2 );
  rtems_task_set_scheduler( tasks[1], scheds[0], 69 );
  rtems_task_set_scheduler( tasks[2], scheds[1], 2 );
  rtems_task_set_scheduler( tasks[3], scheds[1], 69 );

  /* Starting loops */
  rsc = rtems_task_start( tasks[1], task1_entry, 1 );
  rsc = rtems_task_start( tasks[3], task_loop_entry, 3 );

  printf( "INIT COMPLETE\n" );
  rsc = rtems_task_delete( RTEMS_SELF );    /* should not return */
}

rtems_task task0_entry(
rtems_task_argument i
)
{  
  rtems_status_code code;
  printf( "Task %d started\n", i );
  for ( int j = 0; j < 20; j++ ) {
    for ( int i = 0; i < 75000000; i++) {
        asm volatile("nop"::);
    }
  }
    
  code = rtems_semaphore_obtain( sid, RTEMS_WAIT, RTEMS_NO_TIMEOUT );   
  printf( "Obtain MPCP task0: %s\n", rtems_status_text( code ) );  
  
  for ( int j = 0; j < 20; j++ ) {
    for ( int i = 0; i < 75000000; i++ ) {
        asm volatile( "nop"::);
    }
  }
  code = rtems_task_start( tasks[2], task2_entry, 2 );
  printf( "Starting task2 in task0: %s\n", rtems_status_text( code ) );  
  
  for ( int j = 0; j < 20; j++ ) {
    for ( int i = 0; i < 75000000; i++ ) {
        asm volatile( "nop":: );
    }
  }
  code = rtems_semaphore_release(sid);  
  printf( "Release MPCP task0: %s\n", rtems_status_text( code ) ); 
  
  rtems_task_suspend( RTEMS_SELF );
}

/*task1 task1 only busy waits and starts task0*/
rtems_task task1_entry(
rtems_task_argument i
)
{  
  printf( "Task %d started\n", i );
  
  for ( int j = 0; j < 20; j++ ) {
    for ( int i = 0; i < 75000000; i++ ) {
      asm volatile( "nop":: );
    }
  }
      
  rsc = rtems_task_start( tasks[0], task0_entry, 0 );
  
  while ( 1 ) {
    for( int j = 0; j < 20; j++ ) {
        for ( int i = 0; i < 75000000; i++ ) {
          asm volatile( "nop"::);
        }
    }
  }
  rtems_task_suspend(RTEMS_SELF);
}

rtems_task task2_entry(
  rtems_task_argument i 
)
{  
  rtems_status_code code;
  printf( "Task %d started\n", i );
  
  for ( int j = 0; j < 20; j++ ) {
      for ( int i = 0; i < 75000000; i++) {
          asm volatile( "nop":: );
      }
  }
  
  printf( "task2 will try to obtain the MPCP semaphore, but gets suspendend.\n" );
  code = rtems_semaphore_obtain( sid, RTEMS_WAIT, RTEMS_NO_TIMEOUT );
  printf( "Obtain MPCP task2: %s\n", rtems_status_text( code ) );
  
  for ( int j = 0; j < 20; j++) {
    for ( int i = 0; i < 75000000; i++) {
      asm volatile( "nop":: );
    }
  }
  
  code = rtems_semaphore_release( sid );  
  printf( "Release MPCP task2: %s\n", rtems_status_text( code ) );
  
  rtems_task_suspend( RTEMS_SELF );
}

rtems_task task_loop_entry(
rtems_task_argument i
)
{  
  printf( "Task %d started\n", i );

  while ( 1337>69 ) {
    for ( int j = 0; j < 20; j++ ) {
      for ( int i = 0; i < 75000000; i++ ) {
        asm volatile( "nop":: );
      }
    }
  }
  rtems_task_suspend( RTEMS_SELF );
}

void busy_wait(
)
{
  for(int j = 0; j < 20; j++) {
    for (int i = 0; i < 75000000; i++) {
      asm volatile ("nop"::);
    }
  }
}

void print_name(
rtems_id id
)
{
  char  buffer[10];   /* name assumed to be 10 characters or less */
  char *result;
  result = rtems_object_get_name( id, sizeof(buffer), buffer );
  printf( "ID=0x%08x name=%s\n", id, ((result) ? result : "no name") );
}

