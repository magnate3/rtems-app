 # export
 
 ```
  export RTEMS_MAKEFILE_PATH=$HOME/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu
  export PATH=$HOME/development/rtems/compiler_arm/6/bin:$PATH
 ```
 
 # compile 
 
 ```
 /root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include/rtems/confdefs/threads.h:83:4: error: #error "You must define one of CONFIGURE_IDLE_TASK_INITIALIZES_APPLICATION, CONFIGURE_MAXIMUM_TASKS, and CONFIGURE_MAXIMUM_POSIX_THREADS"
   83 |   #error "You must define one of CONFIGURE_IDLE_TASK_INITIALIZES_APPLICATION, CONFIGURE_MAXIMUM_TASKS, and CONFIGURE_MAXIMUM_POSIX_THREADS"
 ```
 
 in include/rtems_config.h add :
 
 ```
#define CONFIGURE_MAXIMUM_TASKS 4
#define CONFIGURE_MAXIMUM_POSIX_THREADS 4
 ```
 
 ## RTEMS_CLOCK_GET_TICKS_SINCE_BOOT' undeclared (first use in this function)
 
 ```
 #define PRINT_TIME(fmt,args...) do { \
			unsigned int __current_tick; \
			rtems_clock_get(RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &__current_tick); \
			printf ("%lu: " fmt "\n", __current_tick, ##args); \
			} whi
 ```
 
 change to
 
 ```
 #define PRINT_TIME(fmt,args...) do { \
                        unsigned int __current_tick; \
                        __current_tick=rtems_clock_get_ticks_since_boot();\
                        printf ("%u: " fmt "\n", __current_tick, ##args); \
                        } while (0)

 ```
 
 # run
 
 ```
 [root@centos7 message_queues_rtems]# qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M -smp 1    -kernel o-optimize/hello.exe
0: Create the message queue 

QEMU: Terminated
 ```
 