# rtems-_app
expat-2.1.0/conftools/config.sub

        ·if hash_hex != hash[1] and hash_base64 != hash[1]:
            log.warning('checksum error: %s' % (file_))
            #failed = True
      

## my host 

```
uname -a
Linux centos7 4.14.0-115.el7a.0.1.aarch64 #1 SMP Sun Nov 25 20:54:21 UTC 2018 aarch64 aarch64 aarch64 GNU/Linux
```

## rtems verion

**git checkout -b  remotes/origin/5**

## though rtems-source-builder to build rtems-gcc objump gdb

```
../source-builder/sb-set-builder          --log=build-log.txt          --prefix=$HOME/development/rtems/compiler/6  6/rtems-aarch64
```

## build kernel

	./waf  bsp_list
```
bsps   c           cpukit    gccdeps.py   INSTALL  LICENSE.BSD-2-Clause  LICENSE.CC-BY-SA-4.0  LICENSE.JFFS2  LICENSE.RPCXDR  MAINTAINERS  Makefile.maint  rtems-bsps     spec        waf      yaml
build  config.ini  Doxyfile  gccdeps.pyc  LICENSE  LICENSE.BSD-3-Clause  LICENSE.GPL-2.0       LICENSE.NET    long_gcc.py     make         README          rtemslogo.png  testsuites  wscript
```

```
(1)./waf distclean  and ./waf bsp_defaults --rtems-bsps=aarch64/a53_lp64_qemu   > config.ini
(2)./waf configure --prefix=$HOME/development/rtems/compiler/6
(3)./waf 
(4)./waf install
```

##   hello_world_c

```
 export PATH=$HOME/development/rtems/compiler/6/bin:$PATH
 export RTEMS_MAKEFILE_PATH=/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu
```

```
 make
aarch64-rtems6-gcc --pipe  -Wall  -O2 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/include -mcpu=cortex-a53     -B/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib -qrtems -Wl,--gc-sections   -mcpu=cortex-a53   -o o-optimize/hello.exe  o-optimize/test.o       
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: o-optimize/test.o: Relocations in generic ELF (EM: 243)
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: o-optimize/test.o: Relocations in generic ELF (EM: 243)
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: o-optimize/test.o: Relocations in generic ELF (EM: 243)
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: o-optimize/test.o: Relocations in generic ELF (EM: 243)
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: o-optimize/test.o: Relocations in generic ELF (EM: 243)
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: o-optimize/test.o: Relocations in generic ELF (EM: 243)
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: o-optimize/test.o: Relocations in generic ELF (EM: 243)
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: o-optimize/test.o: Relocations in generic ELF (EM: 243)
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: o-optimize/test.o: Relocations in generic ELF (EM: 243)
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: o-optimize/test.o: error adding symbols: file in wrong format
collect2: error: ld returned 1 exit status
make: *** [Makefile:23: o-optimize/hello.exe] Error 1
```
make clean

```
[root@centos7 hello_world_c]# make clean
rm -f a.out core mon.out gmon.out
rm -f -r 
rm -f -r  a.out *.o *.BAK Depends-o-optimize.tmp
rm -f -r o-optimize o-debug
[root@centos7 hello_world_c]# make
test -d o-optimize || mkdir o-optimize
aarch64-rtems6-gcc --pipe  -Wall  -O2 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/include -mcpu=cortex-a53      -c   -o o-optimize/test.o test.c
test.c: In function 'Init':
test.c:75:3: warning: implicit declaration of function 'RTEMS_Malloc_Initialize' [-Wimplicit-function-declaration]
   75 |   RTEMS_Malloc_Initialize( &area,  NULL );
      |   ^~~~~~~~~~~~~~~~~~~~~~~
test.c:79:3: warning: implicit declaration of function 'rtems_test_assert'; did you mean 'rtems_task_start'? [-Wimplicit-function-declaration]
   79 |   rtems_test_assert( p == NULL );
      |   ^~~~~~~~~~~~~~~~~
      |   rtems_task_start
aarch64-rtems6-gcc --pipe  -Wall  -O2 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/include -mcpu=cortex-a53     -B/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib -qrtems -Wl,--gc-sections   -mcpu=cortex-a53   -o o-optimize/hello.exe  o-optimize/test.o       
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: /root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/start.o: in function `_el1_start':
/root/development/rtems/kernel2/rtems/build/aarch64/a53_lp64_qemu/../../../bsps/aarch64/shared/start/start.S:317: undefined reference to `_ISR_Stack_size'
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: /root/development/rtems/kernel2/rtems/build/aarch64/a53_lp64_qemu/../../../bsps/aarch64/shared/start/start.S:317: undefined reference to `_ISR_Stack_area_begin'
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: /root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/librtemscpu.a(isr.c.53.o): in function `_ISR_Handler_initialization':
/root/development/rtems/kernel2/rtems/build/aarch64/a53_lp64_qemu/../../../cpukit/score/src/isr.c:46: undefined reference to `_ISR_Stack_area_begin'
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: /root/development/rtems/kernel2/rtems/build/aarch64/a53_lp64_qemu/../../../cpukit/score/src/isr.c:46: undefined reference to `_ISR_Stack_area_begin'
/root/development/rtems/compiler/6/lib/gcc/aarch64-rtems6/10.3.1/../../../../aarch64-rtems6/bin/ld: /root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/librtemscpu.a(isr.c.53.o): in function `_Addresses_Add_offset':
```

because not include  rtems/confdefs.h 
```
[root@centos7 hello_world_c]# vim test.c
/*
 *  Classic API Hello World
 */

#include <rtems.h>
#include <stdlib.h>
#include <stdio.h>

rtems_task Init(
  rtems_task_argument ignored
)
{
  printf( "\n\n*** HELLO WORLD TEST ***\n" );
  printf( "Hello World\n" );
  printf( "*** END OF HELLO WORLD TEST ***\n" );
  exit( 0 );
}

/* configuration information */

#include <bsp.h>

/* NOTICE: the clock driver is explicitly disabled */
#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_USE_DEVFS_AS_BASE_FILESYSTEM

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_MAXIMUM_TASKS 1

#define CONFIGURE_INIT
//#include <rtems/confdefs.h>
/* end of file */
```

##   error arch
```
qemu-system-aarch64 -no-reboot -serial null -serial mon:stdio -net none  -nographic -M xilinx-zynq-a9 -m 256M -kernel o-optimize/hello.exe
qemu-system-aarch64: GLib: g_mapped_file_unref: assertion 'file != NULL' failed
```

do not have xilinx-zynq-a9,have a53

##  CONFIGURE_USE_DEVFS_AS_BASE_FILESYSTEM
```
qemu-system-aarch64 -no-reboot -nographic -serial mon:stdio  -machine virt,gic-version=3 -cpu cortex-a53 -m 4096 -kernel o-optimize/hello.exe 

*** FATAL ***
fatal source: 6 (RTEMS_FATAL_SOURCE_BSP)
fatal code: 11 (0x0000000b)
RTEMS version: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
RTEMS tools: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
executing thread ID: 0x089010001
executing thread name: IDLE
```

int test.c, remove  CONFIGURE_USE_DEVFS_AS_BASE_FILESYSTEM

//#define CONFIGURE_USE_DEVFS_AS_BASE_FILESYSTEM


```
[root@centos7 hello_world_c]# cat test.c
/*
 *  Classic API Hello World
 */

#include <rtems.h>
#include <stdlib.h>
#include <stdio.h>

rtems_task Init(
  rtems_task_argument ignored
)
{
  printf( "\n\n*** HELLO WORLD TEST ***\n" );
  printf( "Hello World\n" );
  printf( "*** END OF HELLO WORLD TEST ***\n" );
  exit( 0 );
}

/* configuration information */

#include <bsp.h>

/* NOTICE: the clock driver is explicitly disabled */
#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
//#define CONFIGURE_USE_DEVFS_AS_BASE_FILESYSTEM

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_MAXIMUM_TASKS 1

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
```


```
[root@centos7 hello_world_c]# make
aarch64-rtems6-gcc --pipe  -Wall  -O2 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/include -mcpu=cortex-a53      -c   -o o-optimize/test.o test.c
aarch64-rtems6-gcc --pipe  -Wall  -O2 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/include -mcpu=cortex-a53     -B/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib -qrtems -Wl,--gc-sections   -mcpu=cortex-a53   -o o-optimize/hello.exe  o-optimize/test.o       
aarch64-rtems6-nm -g -n o-optimize/hello.exe > o-optimize/hello.num
aarch64-rtems6-size o-optimize/hello.exe
   text    data     bss     dec     hex filename
  84304    1856 134097256       134183416       7ff79f8 o-optimize/hello.exe
cp o-optimize/hello.exe o-optimize/hello.ralf
[root@centos7 hello_world_c]# qemu-system-aarch64 -no-reboot -nographic -serial mon:stdio  -machine virt,gic-version=3 -cpu cortex-a53 -m 4096 -kernel o-optimize/hello.exe 


*** HELLO WORLD TEST ***
Hello World
*** END OF HELLO WORLD TEST ***

[ RTEMS shutdown ]
RTEMS version: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
RTEMS tools: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
executing thread ID: 0x08a010001
executing thread name: UI1 
```
