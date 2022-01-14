# rtems-_app
expat-2.1.0/conftools/config.sub

        ·if hash_hex != hash[1] and hash_base64 != hash[1]:
            log.warning('checksum error: %s' % (file_))
            #failed = True
          ·

## rtems verion

**git checkout -b  remotes/origin/5**

## though rtems-source-builder to build rtems-gcc objump gdb

```
../source-builder/sb-set-builder          --log=build-log.txt          --prefix=$HOME/development/rtems/compiler/6  6/rtems-aarch64
```

## build development environment

	./waf  bsp_list
```
bsps   c           cpukit    gccdeps.py   INSTALL  LICENSE.BSD-2-Clause  LICENSE.CC-BY-SA-4.0  LICENSE.JFFS2  LICENSE.RPCXDR  MAINTAINERS  Makefile.maint  rtems-bsps     spec        waf      yaml
build  config.ini  Doxyfile  gccdeps.pyc  LICENSE  LICENSE.BSD-3-Clause  LICENSE.GPL-2.0       LICENSE.NET    long_gcc.py     make         README          rtemslogo.png  testsuites  wscript
```

```
(1)./waf bsp_defaults --rtems-bsps=aarch64/a53_lp64_qemu   > config.ini
(2)./waf configure --prefix=$HOME/development/rtems/compiler/6
(3)./waf 
(4)./waf install
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
