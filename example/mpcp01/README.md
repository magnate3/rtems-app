 

# export 

export PATH=$HOME/development/rtems/compiler_arm/6/bin:$PATH
export RTEMS_MAKEFILE_PATH=$HOME/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu

# make

```
[root@centos7 mpcp01]# make
arm-rtems6-gcc --pipe  -Wall  -O0 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib/include -Iinc -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/init.o init.c
init.c: In function 'init_sched':
init.c:27:35: warning: implicit declaration of function 'rtems_get_processor_count' [-Wimplicit-function-declaration]
   27 |   printf( "PROCESSOR COUNT: %d\n",rtems_get_processor_count() );
      |                                   ^~~~~~~~~~~~~~~~~~~~~~~~~
init.c: In function 'init':
init.c:41:3: warning: implicit declaration of function 'init_extensions' [-Wimplicit-function-declaration]
   41 |   init_extensions();
      |   ^~~~~~~~~~~~~~~
init.c:83:32: error: 'RTEMS_MULTIPROCESSOR_PRIORITY_CEILING' undeclared (first use in this function); did you mean 'RTEMS_MULTIPROCESSOR_RESOURCE_SHARING'?
   83 |     ( RTEMS_BINARY_SEMAPHORE | RTEMS_MULTIPROCESSOR_PRIORITY_CEILING ),
      |                                ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      |                                RTEMS_MULTIPROCESSOR_RESOURCE_SHARING
init.c:83:32: note: each undeclared identifier is reported only once for each function it appears in
init.c: In function 'print_name':
init.c:224:3: warning: implicit declaration of function 'printk'; did you mean 'printf'? [-Wimplicit-function-declaration]
  224 |   printk( "ID=0x%08x name=%s\n", id, ((result) ? result : "no name") );
      |   ^~~~~~
      |   printf
make: *** [/root/development/rtems/compiler_arm/6/share/rtems6/make/compilers/gcc-target-default.cfg:100: o-optimize/init.o] Error 1
```

```
 rsc = rtems_semaphore_create(
    rtems_build_name( 'M', 'P', 'C', 'P' ),
    1,
    ( RTEMS_BINARY_SEMAPHORE | RTEMS_MULTIPROCESSOR_RESOURCE_SHARING | RTEMS_PRIORITY_CEILING |  RTEMS_PRIORITY),
    1,
    &sid
  );
```

```
[root@centos7 mpcp01]# make
arm-rtems6-gcc --pipe  -Wall  -O0 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib/include -Iinc -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/init.o init.c
init.c: In function 'init_sched':
init.c:27:35: warning: implicit declaration of function 'rtems_get_processor_count' [-Wimplicit-function-declaration]
   27 |   printf( "PROCESSOR COUNT: %d\n",rtems_get_processor_count() );
      |                                   ^~~~~~~~~~~~~~~~~~~~~~~~~
init.c: In function 'init':
init.c:41:3: warning: implicit declaration of function 'init_extensions' [-Wimplicit-function-declaration]
   41 |   init_extensions();
      |   ^~~~~~~~~~~~~~~
arm-rtems6-gcc --pipe  -Wall  -O0 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib/include -Iinc -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9     -B/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib -qrtems -Wl,--gc-sections   -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9   -o o-optimize/hello.exe  o-optimize/init.o       
/root/development/rtems/compiler_arm/6/lib/gcc/arm-rtems6/10.3.1/../../../../arm-rtems6/bin/ld: o-optimize/init.o: in function `init':
/root/development/rtems/rtems-examples/mpcp01/init.c:41: undefined reference to `init_extensions'
/root/development/rtems/compiler_arm/6/lib/gcc/arm-rtems6/10.3.1/../../../../arm-rtems6/bin/ld: o-optimize/init.o: in function `init_sched':
/root/development/rtems/rtems-examples/mpcp01/init.c:27: undefined reference to `rtems_get_processor_count'
collect2: error: ld returned 1 exit status
make: *** [Makefile:26: o-optimize/hello.exe] Error 1
[root@centos7 mpcp01]# 
```

## run

```
qemu-system-arm  -no-reboot -net none -nographic -smp 4 -icount auto -M realview-pbx-a9 -m 256M -kernel o-optimize/hello.exe
```

```
[root@centos7 mpcp01]# qemu-system-arm  -no-reboot -net none -nographic -smp 4 -icount auto -M realview-pbx-a9 -m 256M -kernel o-optimize/hello.exe
TEST START:
Create task: RTEMS_SUCCESSFUL
Create task: RTEMS_SUCCESSFUL
Create task: RTEMS_SUCCESSFUL
Create task: RTEMS_SUCCESSFUL
Create MPCP Semaphore: RTEMS_NOT_DEFINED
INIT COMPLETE
Task 1 started
Task 0 started
Obtain MPCP task0: RTEMS_INVALID_ID
Starting task2 in task0: RTEMS_SUCCESSFUL
Release MPCP task0: RTEMS_INVALID_ID
Task 2 started

```

```

  rsc = rtems_semaphore_create(
    rtems_build_name( 'M', 'P', 'C', 'P' ),
    1,
 RTEMS_BINARY_SEMAPHORE | RTEMS_PRIORITY_CEILING | RTEMS_PRIORITY,
    1,
    &sid
  );
```

```
[root@centos7 mpcp01]# qemu-system-arm  -no-reboot -net none -nographic -smp 4 -icount auto -M realview-pbx-a9 -m 256M -kernel o-optimize/hello.exe
TEST START:
PROCESSOR COUNT: 2
rtems_scheduler_by_processor(0, &scheds[0]): RTEMS_SUCCESSFUL
251723777
rtems_scheduler_by_processor(1, &scheds[1]): RTEMS_SUCCESSFUL
251723778
Create task: RTEMS_SUCCESSFUL
Create task: RTEMS_SUCCESSFUL
Create task: RTEMS_SUCCESSFUL
Create task: RTEMS_SUCCESSFUL
Create MPCP Semaphore: RTEMS_SUCCESSFUL
INIT COMPLETE
Task 1 started
Task 3 started
```


 