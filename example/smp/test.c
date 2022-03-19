#include <stdio.h>

#include <rtems.h>
#include <rtems/test-info.h>

#include "tmacros.h"


#define CPU_COUNT 3

#define SCHEDULER_A rtems_build_name('S','C','H','A')
#define SCHEDULER_B rtems_build_name('S','C','H','B')
#define SCHEDULER_C rtems_build_name('S','C','H','C')
#define SCHEDULER_D rtems_build_name('S','C','H','D')


const char rtems_test_name[] = "SMP QEMU";
static volatile bool runnable;

struct task_info {
    rtems_task (*entry)(rtems_task_argument);
    rtems_id thread;
    rtems_id scheduler_name;
    rtems_task_priority priority;
    uint32_t cpu_affinity;
};

#ifndef BIT
#define BIT(n) (0x1 << (n))
#endif

#define _TASK_INIT(_n, _prio, _sched_name, _affinity) \
    [_n] = {\
        .entry = test_task__##_n, \
        .thread = 0, \
        .scheduler_name = _sched_name, \
        .priority = _prio, \
        .cpu_affinity = _affinity \
    }


#define TASK_DEFINE(_n) \
    static rtems_task test_task__##_n(rtems_task_argument arg) \
    { \
        for ( ; ; ) { \
            printf("Core_%u: T" #_n "\n", rtems_scheduler_get_processor()); \
            rtems_task_wake_after(RTEMS_MILLISECONDS_TO_TICKS(50)); \
        } \
    }

TASK_DEFINE(0);
TASK_DEFINE(1);
TASK_DEFINE(2);
TASK_DEFINE(3);
TASK_DEFINE(4);
TASK_DEFINE(5);
TASK_DEFINE(6);
TASK_DEFINE(7);
TASK_DEFINE(8);

static struct task_info _task_table[] = {
    _TASK_INIT(0, 100, 0, 0),
    _TASK_INIT(1, 100, 0, 0),
    _TASK_INIT(2, 100, 0, 0),
    _TASK_INIT(3, 100, 0, BIT(1)),
    _TASK_INIT(4, 100, 0, BIT(1)),
    _TASK_INIT(5, 100, 0, BIT(1)),
    _TASK_INIT(6, 100, 0, BIT(2)),
    _TASK_INIT(7, 100, 0, BIT(2)),
    _TASK_INIT(8, 100, 0, BIT(2)),
};

static void create_tasks(struct task_info *tasks, size_t n)
{
    rtems_status_code sc;
    for (int i = 0; i < n; i++) {
        sc = rtems_task_create(rtems_build_name('t','s','t','0'+i), tasks[i].priority, 4096, 
            RTEMS_DEFAULT_MODES, RTEMS_DEFAULT_ATTRIBUTES, &tasks[i].thread);
        rtems_test_assert(sc == RTEMS_SUCCESSFUL);

        /* Set schedule domain */
        if (tasks[i].scheduler_name) {
            rtems_id scheduler;
            sc = rtems_scheduler_ident(tasks[i].scheduler_name, &scheduler);
            rtems_test_assert(sc == RTEMS_SUCCESSFUL);
            sc = rtems_task_set_scheduler(tasks[i].thread, scheduler, tasks[i].priority);
            rtems_test_assert(sc == RTEMS_SUCCESSFUL);
        }

        /* Set affinity */
        if (tasks[i].cpu_affinity) {
            cpu_set_t affinity;
            uint32_t  value;
            int index = 0;
            
            value = tasks[i].cpu_affinity;
            CPU_ZERO(&affinity);
            while (index < 32) {
                if (value & 0x1) {
                    CPU_SET(index, &affinity);
                }
                value >>= 1;
                index++;
            }
                
            sc = rtems_task_set_affinity(tasks[i].thread, 
                sizeof(affinity), &affinity);
            rtems_test_assert(sc == RTEMS_SUCCESSFUL);
        }

        /* Starting task */
        sc = rtems_task_start(tasks[i].thread, tasks[i].entry, 0);
        rtems_test_assert(sc == RTEMS_SUCCESSFUL);
    }
}


rtems_task Init(rtems_task_argument arg)
{
    rtems_status_code sc;

    rtems_test_assert(rtems_scheduler_get_processor_maximum() == CPU_COUNT);

    create_tasks(_task_table, RTEMS_ARRAY_SIZE(_task_table));
    
    for ( ; ; ) {
        printf("Core_%u: Init-Task\n", rtems_scheduler_get_processor());
        rtems_task_wake_after(RTEMS_MILLISECONDS_TO_TICKS(500));
    }
}

#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_SIMPLE_CONSOLE_DRIVER
#define CONFIGURE_MAXIMUM_PROCESSORS CPU_COUNT
#define CONFIGURE_SCHEDULER_EDF_SMP
//#define CONFIGURE_SCHEDULER_PRIORITY_SMP


#include <rtems/scheduler.h>

#if 0
RTEMS_SCHEDULER_PRIORITY_SMP(a, 255);
RTEMS_SCHEDULER_PRIORITY_SMP(b, 255);

#define CONFIGURE_SCHEDULER_TABLE_ENTRIES \
  RTEMS_SCHEDULER_TABLE_PRIORITY_SMP(a, SCHEDULER_A), \
  RTEMS_SCHEDULER_TABLE_PRIORITY_SMP(b, SCHEDULER_B)

#define CONFIGURE_SCHEDULER_ASSIGNMENTS \
  RTEMS_SCHEDULER_ASSIGN(0, RTEMS_SCHEDULER_ASSIGN_PROCESSOR_MANDATORY), \
  RTEMS_SCHEDULER_ASSIGN(1, RTEMS_SCHEDULER_ASSIGN_PROCESSOR_OPTIONAL)
  
//#else
RTEMS_SCHEDULER_EDF_SMP(a);
RTEMS_SCHEDULER_EDF_SMP(b);
RTEMS_SCHEDULER_EDF_SMP(c);
RTEMS_SCHEDULER_EDF_SMP(d);

#define CONFIGURE_SCHEDULER_TABLE_ENTRIES \
  RTEMS_SCHEDULER_TABLE_EDF_SMP(a, SCHEDULER_A), \
  RTEMS_SCHEDULER_TABLE_EDF_SMP(b, SCHEDULER_B), \
  RTEMS_SCHEDULER_TABLE_EDF_SMP(c, SCHEDULER_C), \
  RTEMS_SCHEDULER_TABLE_EDF_SMP(d, SCHEDULER_D)

#define CONFIGURE_SCHEDULER_ASSIGNMENTS \
  RTEMS_SCHEDULER_ASSIGN(0, RTEMS_SCHEDULER_ASSIGN_PROCESSOR_MANDATORY), \
  RTEMS_SCHEDULER_ASSIGN(1, RTEMS_SCHEDULER_ASSIGN_PROCESSOR_OPTIONAL), \
  RTEMS_SCHEDULER_ASSIGN(2, RTEMS_SCHEDULER_ASSIGN_PROCESSOR_OPTIONAL), \
  RTEMS_SCHEDULER_ASSIGN(3, RTEMS_SCHEDULER_ASSIGN_PROCESSOR_OPTIONAL)
  
#endif

#define CONFIGURE_MAXIMUM_TASKS 10

#define CONFIGURE_MAXIMUM_TIMERS 1

//#define CONFIGURE_INITIAL_EXTENSIONS RTEMS_TEST_INITIAL_EXTENSION

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>

