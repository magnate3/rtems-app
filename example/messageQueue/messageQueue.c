#include <bsp.h>
//#include <crt.h>
#include <string.h>
rtems_task Init( rtems_task_argument argument);
#define CONFIGURE_INIT
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_MAXIMUM_TASKS        4
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES 2
#include <rtems/confdefs.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// The task ids are global, because task2 needs task1's id
// "Read-Only" globals are okay in a multi-tasking app,
// but woe be to the developer who doesn't take special
// precautions when sharing read-write global data.

rtems_id   task_id[2];

rtems_id   msgq_id[2];


rtems_task task_1(rtems_task_argument arg){
	int terms;
	char snum[100];
	size_t size;
	double piVal = 0;
	int i;
	while(1){
		piVal = 0;
		for(i = 0;i<100;i++){
			snum[i] = '\0';
		}
		rtems_message_queue_receive(msgq_id[0], snum, &size, RTEMS_DEFAULT_ATTRIBUTES, RTEMS_WAIT);
		printf("Value passed:%s\n", snum);
		terms = atoi(snum);
		for(i = 0;i<100;i++){
			snum[i] = '\0';
		}
		for(i = 0;i<terms;i++){
			if(i%2 == 0)
				piVal+=4.0*(1.0/(2.0*i+1.0));
			else
				piVal-=4.0*(1.0/(2.0*i+1.0));
		}
		snprintf(snum, 100, "%f", piVal);
		//ftoa(piVal, snum, 10);
		rtems_message_queue_send(msgq_id[1], snum, 100);

	}

}

rtems_task task_0(rtems_task_argument arg){
	int terms, i;
	char snum[100];
	size_t size;
	while(1){

		printf("Enter the number of terms to use in the series: ");
		fflush(stdout);
		scanf("%d", &terms);
		itoa(terms, snum, 10);
		rtems_message_queue_send(msgq_id[0], snum, 100);
		for(i = 0;i<100;i++){
			snum[i] = '\0';
		}
		rtems_message_queue_receive(msgq_id[1], snum, &size, RTEMS_DEFAULT_ATTRIBUTES, RTEMS_WAIT);
		printf("The approximate value of pi using %d terms is %s\n", terms, snum);
		for(i = 0;i<100;i++){
			snum[i] = '\0';
		}
	}

}






// Although defined as global variables here, it is
// actually okay to define these inside Init() because
// the strings are stored in the .data section and so still
// exist even after Init() is deleted.  DO NOT PASS POINTERS
// TO DATA THAT RESIDES ON Init()'s STACK!!!


rtems_task Init( rtems_task_argument ignored)
{
  rtems_status_code status;

  status = rtems_task_create(
    rtems_build_name('T','S','K','1'), 1, RTEMS_MINIMUM_STACK_SIZE,
    RTEMS_DEFAULT_MODES, RTEMS_FLOATING_POINT, &task_id[0]
  );
  if (status != RTEMS_SUCCESSFUL) {
     fprintf(stderr, "Error creating task 1\n");
     exit(0);
  }

  status = rtems_task_create(
    rtems_build_name('T','S','K','2'), 2, RTEMS_MINIMUM_STACK_SIZE,
    RTEMS_DEFAULT_MODES, RTEMS_FLOATING_POINT, &task_id[1]
  );
  if (status != RTEMS_SUCCESSFUL) {
     fprintf(stderr, "Error creating task 2\n");
     exit(0);
  }

  status = rtems_message_queue_create(
    rtems_build_name('M','S','G','1'), 3, 100, RTEMS_DEFAULT_ATTRIBUTES, &msgq_id[0]
  );

  if(status == RTEMS_INVALID_NAME){
	  fprintf(stderr, "Error message 1\n");
  }else if(status == RTEMS_INVALID_ADDRESS){
	  fprintf(stderr, "Error message 2\n");
  }else if(status == RTEMS_INVALID_NUMBER){
	  fprintf(stderr, "Error message 3\n");
  }else if(status == RTEMS_INVALID_SIZE){
	  fprintf(stderr, "Error message 4\n");
  }else if(status == RTEMS_TOO_MANY){
	  fprintf(stderr, "Error message 5\n");
  }else if(status == RTEMS_UNSATISFIED){
	  fprintf(stderr, "Error message 6\n");
  }else if(status == RTEMS_MP_NOT_CONFIGURED){
	  fprintf(stderr, "Error message 7\n");
  }
  if(status != RTEMS_SUCCESSFUL){
    fprintf(stderr, "Error creating queue 1\n");
    exit(0);
  }

  status = rtems_message_queue_create(
    rtems_build_name('M','S','G','2'), 4, 100, RTEMS_DEFAULT_ATTRIBUTES, &msgq_id[1]
  );
  if(status != RTEMS_SUCCESSFUL){
    fprintf(stderr, "Error creating queue 2\n");
    exit(0);
  }

  status = rtems_task_start(task_id[0], task_0, (rtems_task_argument)0);
  status = rtems_task_start(task_id[1], task_1, (rtems_task_argument)0);
  //status = rtems_task_start(task_id[0], hello1, (rtems_task_argument)tsk1_msg);
  //status = rtems_task_start(task_id[1], hello2, (rtems_task_argument)tsk2_msg);

  status = rtems_task_delete(RTEMS_SELF);

  exit (0);
}
