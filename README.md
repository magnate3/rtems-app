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
[root@centos7 rtems]# ../source-builder/sb-set-builder --list-bsets | grep aarch
    6/rtems-aarch64.bset
    7/rtems-aarch64.bset
```

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

**because not include  rtems/confdefs.h**

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

## gdb

```
qemu-system-aarch64 -no-reboot -nographic -serial mon:stdio  -machine virt,gic-version=3 -cpu cortex-a53 -m 4096 -kernel o-optimize/low_ticker.exe -s -S
```

```
[root@centos7 low_ticker]#  aarch64-rtems6-gdb  o-optimize/low_ticker.exe
GNU gdb (GDB) 10.1.90.20210409-git
Copyright (C) 2021 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "--host=aarch64-linux-gnu --target=aarch64-rtems6".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from o-optimize/low_ticker.exe...
(gdb) target remote:1234
Remote debugging using :1234
bsp_vector_table_begin () at ../../../bsps/aarch64/shared/start/start.S:55
55        mov x5, x1    /* machine type number or ~0 for DT boot */
(gdb) load
Loading section .start, size 0x1fc lma 0x40008000
Loading section .text, size 0x93fc lma 0x40008800
Loading section .init, size 0x34 lma 0x40011bfc
Loading section .fini, size 0x34 lma 0x40011c30
Loading section .rodata, size 0x1a54 lma 0x40011c68
Loading section .eh_frame, size 0x4 lma 0x400136bc
Loading section .init_array, size 0x8 lma 0x400136c0
Loading section .fini_array, size 0x8 lma 0x400136c8
Loading section .rtemsroset, size 0x88 lma 0x400136d0
Loading section .data, size 0x378 lma 0x40100000
Start address 0x0000000040008000, load size 46280
Transfer rate: 15065 KB/sec, 1492 bytes/write.
(gdb) run
The "remote" target does not support "run".  Try "help target" or "continue".
(gdb) b BSP_rtems_irq_mngt_init
Function "BSP_rtems_irq_mngt_init" not defined.
Make breakpoint pending on future shared library load? (y or [n]) n
(gdb) b bsp_start
Breakpoint 1 at 0x40008e90: file ../../../bsps/aarch64/a53/start/bspstart.c, line 44.
(gdb) b bsp_interrupt_initialize
Breakpoint 2 at 0x40008fd0: file ../../../bsps/shared/irq/irq-generic.c, line 163.
(gdb) c
Continuing.

Breakpoint 1, bsp_start () at ../../../bsps/aarch64/a53/start/bspstart.c:44
44        bsp_interrupt_initialize();
(gdb) c
Continuing.

Breakpoint 2, bsp_interrupt_initialize () at ../../../bsps/shared/irq/irq-generic.c:163
163       bsp_interrupt_facility_initialize();
(gdb) s
bsp_interrupt_facility_initialize () at ../../../bsps/shared/dev/irq/arm-gicv3.c:394
394       uint32_t id_count = get_id_count(dist);
(gdb) list
389     }
390
391     void bsp_interrupt_facility_initialize(void)
392     {
393       volatile gic_dist *dist = ARM_GIC_DIST;
394       uint32_t id_count = get_id_count(dist);
395       uint32_t id;
396
397       arm_interrupt_facility_set_exception_handler();
398
(gdb) bt
#0  bsp_interrupt_facility_initialize () at ../../../bsps/shared/dev/irq/arm-gicv3.c:394
#1  0x0000000040008fdc in bsp_interrupt_initialize () at ../../../bsps/shared/irq/irq-generic.c:163
#2  0x0000000040008e9c in bsp_start () at ../../../bsps/aarch64/a53/start/bspstart.c:44
#3  0x0000000040009e70 in rtems_initialize_executive () at ../../../cpukit/sapi/src/exinit.c:116
#4  0x0000000040008d4c in boot_card (cmdline=<optimized out>) at ../../../bsps/shared/start/bootcard.c:55
#5  0x00000000400080cc in _el1_start () at ../../../bsps/aarch64/shared/start/start.S:308
Backtrace stopped: previous frame identical to this frame (corrupt stack?)
(gdb) 
```

##  rtems-libbsd

### rtems-libbsd version

```
[root@centos7 rtems-libbsd-a64]# git branch
  master
* remotes/origin/5
  remotes/origin/6-freebsd-12
[root@centos7 rtems-libbsd-a64]# pwd
/root/development/rtems_rv/rtems-libbsd-a64
[root@centos7 rtems-libbsd-a64]# 


```

### rtems version

```
[root@centos7 rtems]# pwd
/root/development/rtems/kernel2/rtems
You have new mail in /var/spool/mail/root
[root@centos7 rtems]# git branch --all
  master
* remotes/origin/5
  remotes/origin/4.10
  remotes/origin/4.11
  remotes/origin/4.8
  remotes/origin/4.9
  remotes/origin/5
  remotes/origin/HEAD -> origin/master
  remotes/origin/master
```



```
(1)git clone git://git.rtems.org/rtems-libbsd.git
(2)cd rtems-libbsd
(3)git submodule init
(4)git submodule update rtems_waf
(5)./waf configure --prefix=$HOME/development/rtems/compiler/6 --rtems-bsps=aarch64/a53_lp64_qemu   --buildset=buildset/default.ini
(6) ./waf
(7) ./waf install

```

##### run

```



[root@centos7 rtems-libbsd-a64]# qemu-system-aarch64 -no-reboot -nographic -serial mon:stdio  -machine virt,gic-version=3 -cpu cortex-a53 -m 4096 -kernel  build/aarch64-rtems6-a53_lp64_qemu-default/media01.exe   -net tap,ifname=qtap,script=no,downscript=no  -net nic,model=e1000,macaddr=0e:b0:ba:5e:ba:12


*** BEGIN OF TEST LIBBSD MEDIA 1 ***
*** TEST VERSION: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
*** TEST STATE: USER_INPUT
*** TEST BUILD: RTEMS_POSIX_API
*** TEST TOOLS: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
nexus0: <RTEMS Nexus device>
info: lo0: link state changed to UP
info: ftpd: FTP daemon started (4 sessions max)
info: telnetd: started successfully on port 23

RTEMS Shell on /dev/console. Use 'help' to list commands.
SHLL [/] # info: version 6.2.1 starting
err: no valid interfaces found
warning: no interfaces have a carrier

SHLL [/] # 
SHLL [/] # 
```

```
[root@centos7 rtems-libbsd-a64]# ip a sh qtap
11: qtap: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc pfifo_fast state DOWN group default qlen 1000
    link/ether 3e:01:b5:63:ad:69 brd ff:ff:ff:ff:ff:ff
    inet 169.254.1.1/16 scope global qtap
       valid_lft forever preferred_lft forever
    inet6 fe80::3c01:b5ff:fe63:ad69/64 scope link 
       valid_lft forever preferred_lft forever
[root@centos7 rtems-libbsd-a64]# ip link set dev qtap up
```

```
SHLL [/] # help
help: The topics are
  all, help, misc, files, rtems, mem, net, monitor
SHLL [/] # net
net: command not found
SHLL [/] # help net   
help: list for the topic 'net'
arp          - arp [args]
hostname     - hostname [-fms] [name-of-host]
ping         - ping [args]
route        - route [args]
netstat      - netstat [args]
sysctl       - sysctl [-bdehiNnoRTqx] [-f filename] name[=value] ...
ifconfig     - ifconfig [args]
ifmcstat     - ifmcstat [args]
vmstat       - vmstat [args]

SHLL [/] # ping  169.254.1.1
PING 169.254.1.1 (169.254.1.1): 56 data bytes
ping: sendto: Host is unreachable
ping: sendto: Host is unreachable
ping: sendto: Host is unreachable

--- 169.254.1.1 ping statistics ---
3 packets transmitted, 0 packets received, 100.0% packet loss
SHLL [/] # ifconfig
lo0: flags=8049<UP,LOOPBACK,RUNNING,MULTICAST> metric 0 mtu 16384
        options=680003<RXCSUM,TXCSUM,LINKSTATE,RXCSUM_IPV6,TXCSUM_IPV6>
        inet 127.0.0.1 netmask 0xffffff00
        inet6 ::1 prefixlen 128
        inet6 fe80::1%lo0 prefixlen 64 scopeid 0x1
        nd6 options=21<PERFORMNUD,AUTO_LINKLOCAL>
        groups: lo
SHLL [/] #   exit   


SHLL [/] # exit
Shell exiting
                             STACK USAGE BY THREAD
ID         NAME                  LOW        HIGH       CURRENT     AVAIL   USED
0x09010001 IDLE                  0x404adc00 0x404afc4f 0x404af900   8256   1584
0x0a010001 UI1                   0x404b2fc0 0x404bafbf 0x404bad90  32752   5504
0x0a010002 BSWP                  0x404ec0d0 0x404ee8cf 0x404ee770  10224    896
0x0a010003 BRDA                  0x404ef090 0x404f188f 0x404f1750  10224    448
0x0a010004 MDIA                  0x404f2080 0x404fa07f 0x404f9f20  32752    480
0x0a010005 TIME                  0x404fa8d0 0x405028cf 0x405027b0  32752   1184
0x0a010006 IRQS                  0x40503090 0x4050b08f 0x4050af70  32752    416
0x0a010007 config_0              0x40531c40 0x40539c3f 0x40539ae0  32752    896
0x0a010008 swi5: fast task       0x4053a720 0x4054271f 0x405425d0  32752    464
0x0a010009 thread taskq          0x405430a0 0x4054b09f 0x4054af40  32752    480
0x0a01000a swi6: Giant tas       0x4054bb80 0x40553b7f 0x40553a30  32752    464
0x0a01000b swi6: task queu       0x40554660 0x4055c65f 0x4055c510  32752   1968
0x0a01000c kqueue_ctx task       0x4055cfe0 0x40564fdf 0x40564e80  32752    480
0x0a01000d swi1: netisr 0        0x405659e0 0x4056d9df 0x4056d890  32752   1232
0x0a01000e bufdaemon             0x4059d530 0x405a552f 0x405a5350  32752   1264
0x0a01000f vnlru                 0x405a5db0 0x405addaf 0x405adb40  32752    752
0x0a010010 syncer                0x405ae630 0x405b662f 0x405b63f0  32752    704
0x0a010011 softirq_0             0x405b6fb0 0x405befaf 0x405bee50  32752    480
0x0a010012 bufspacedaemon-       0x405bf830 0x405c782f 0x405c7690  32752    544
0x0a010013 DHCP                  0x405ce4c0 0x405d34bf 0x405d2e40  20464   2848
0x0a010014 FTPa                  0x405d42c0 0x405d7abf 0x405d74c0  14320   1664
0x0a010015 FTPb                  0x405d8280 0x405dba7f 0x405db480  14320   1664
0x0a010016 FTPc                  0x405dc240 0x405dfa3f 0x405df440  14320   1664
0x0a010017 FTPd                  0x405e0200 0x405e39ff 0x405e3400  14320   1664
0x0a010018 FTPD                  0x405e41c0 0x405e69bf 0x405e6640  10224   1216
0x0a010019 TNTa                  0x405e76d0 0x405ef6cf 0x405ef570  32752   1024
0x0a01001a TNTb                  0x405f0820 0x405f881f 0x405f86c0  32752    912
0x0a01001b TNTc                  0x405f9970 0x4060196f 0x40601810  32752    912
0x0a01001c TNTd                  0x40602ac0 0x4060aabf 0x4060a960  32752    912
0x0a01001d TNTe                  0x4060b880 0x4061387f 0x40613720  32752   1600
0x0a01001e TNTD                  0x406149d0 0x406171cf 0x40616e70  10224    992
0x0a01001f RCRD                  0x40617a50 0x4061a24f 0x40619ee0  10224   1104
0x00000000 Interrupt Stack       0x404b0400 0x404b2bff 0x00000000  10224    480

*** END OF TEST LIBBSD MEDIA 1 ***


[ RTEMS shutdown ]
RTEMS version: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
RTEMS tools: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
executing thread ID: 0x08a010001
executing thread name: UI1 
```

##### RTEMS Nexus device

```
nexus_probe(device_t dev)
{
        int err;
        const rtems_bsd_device *nd;

        device_set_desc(dev, "RTEMS Nexus device");
}

(gdb) bt
#0  nexus_probe (dev=0x4056ff70) at ../../rtemsbsd/rtems/rtems-kernel-nexus.c:120
#1  0x000000004007d844 in DEVICE_PROBE (dev=0x4056ff70) at ../../rtemsbsd/include/rtems/bsd/local/device_if.h:115
#2  _bsd_device_probe_child (dev=0x4056ebd0, child=child@entry=0x4056ff70) at ../../freebsd/sys/kern/subr_bus.c:2190
#3  0x000000004007dba4 in _bsd_device_probe (dev=dev@entry=0x4056ff70) at ../../freebsd/sys/kern/subr_bus.c:2922
#4  0x000000004007de64 in _bsd_device_probe_and_attach (dev=0x4056ff70) at ../../freebsd/sys/kern/subr_bus.c:4187
#5  _bsd_bus_generic_new_pass (dev=0x4056ebd0) at ../../freebsd/sys/kern/subr_bus.c:4187
#6  0x000000004007c4c8 in BUS_NEW_PASS (_dev=0x4056ebd0) at ../../rtemsbsd/include/rtems/bsd/local/bus_if.h:1046
#7  _bsd_bus_set_pass (pass=2147483647) at ../../freebsd/sys/kern/subr_bus.c:994
#8  0x0000000040071478 in _bsd_mi_startup () at ../../freebsd/sys/kern/init_main.c:302
#9  0x0000000040058118 in rtems_bsd_initialize () at ../../rtemsbsd/rtems/rtems-kernel-init.c:235
#10 0x0000000040008b5c in Init (arg=<optimized out>) at ../../testsuite/include/rtems/bsd/test/default-network-init.h:239
#11 0x0000000040152914 in _Thread_Handler () at ../../../cpukit/score/src/threadhandler.c:145
#12 0x00000000401528b0 in ?? ()

Breakpoint 2, bsp_interrupt_vector_enable (vector=vector@entry=30) at ../../../bsps/shared/dev/irq/arm-gicv3.c:307
307     ../../../bsps/shared/dev/irq/arm-gicv3.c: No such file or directory.
(gdb) bt
#0  bsp_interrupt_vector_enable (vector=vector@entry=30) at ../../../bsps/shared/dev/irq/arm-gicv3.c:307
#1  0x000000004013bdd4 in bsp_interrupt_entry_install_first (entry=0x404b2d80, options=1, vector=30) at ../../../bsps/shared/irq/irq-generic.c:201
#2  bsp_interrupt_entry_install (entry=0x404b2d80, options=1, vector=30) at ../../../bsps/shared/irq/irq-generic.c:226
#3  rtems_interrupt_entry_install (vector=vector@entry=30, options=options@entry=1, entry=entry@entry=0x404b2d80) at ../../../bsps/shared/irq/irq-generic.c:280
#4  0x000000004013b014 in rtems_interrupt_handler_install (vector=30, info=info@entry=0x401cc958 "Clock", options=options@entry=1, routine=routine@entry=0x4013ab60 <Clock_isr>, arg=arg@entry=0x0) at ../../../bsps/shared/irq/irq-handler-install.c:107
#5  0x000000004013ac10 in arm_gt_clock_handler_install () at ../../../bsps/shared/dev/clock/arm-generic-timer.c:65
#6  _Clock_Initialize () at ../../../bsps/aarch64/include/../../shared/dev/clock/clockimpl.h:216
#7  0x000000004014d340 in rtems_initialize_executive () at ../../../cpukit/sapi/src/exinit.c:116
#8  0x000000004013afbc in boot_card (cmdline=<optimized out>) at ../../../bsps/shared/start/bootcard.c:55
#9  0x00000000400080dc in _el1_start () at ../../../bsps/aarch64/shared/start/start.S:317
Backtrace stopped: previous frame identical to this frame (corrupt stack?)

```

##### selectpollkqueue01.exe 

```
[root@centos7 rtems-libbsd-a64]# qemu-system-aarch64 -no-reboot -nographic -serial mon:stdio  -machine virt,gic-version=3 -cpu cortex-a53 -m 4096 -net none -kernel  build/aarch64-rtems6-a53_lp64_qemu-default/selectpollkqueue01.exe 


*** BEGIN OF TEST LIBBSD SELECT AND POLL AND KQUEUE AND PIPE 1 ***
*** TEST VERSION: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
*** TEST STATE: EXPECTED_PASS
*** TEST BUILD: RTEMS_POSIX_API
*** TEST TOOLS: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
nexus0: <RTEMS Nexus device>
[zone: unpcb] kern.ipc.maxsockets limit reached
info: lo0: link state changed to UP
test select timeout
test select connect
worker: create new connect socket
worker: connect
test select read
worker: write
test select write
worker: read
test select close
worker: close
test pselect sigmask
test pselect timeout
test poll timeout
test poll connect
worker: create new connect socket
worker: connect
test poll read
worker: write
test poll write
worker: read
test poll close
worker: close
test kqueue timer
test kqueue timer
test kqueue connect
worker: create new connect socket
worker: connect
test kqueue read
worker: write
test kqueue write
worker: read
test kqueue close
worker: shutdown
test kqueue user
                             STACK USAGE BY THREAD
ID         NAME                  LOW        HIGH       CURRENT     AVAIL   USED
0x09010001 IDLE                  0x4025fc00 0x402623ff 0x402620b0  10224    944
0x0a010001 UI1                   0x40264fc0 0x4026cfbf 0x4026c990  32752   5360
0x0a010002 TIME                  0x4026d530 0x4027552f 0x40275410  32752    528
0x0a010003 IRQS                  0x40275540 0x4027d53f 0x4027d420  32752    384
0x0a010004 config_0              0x402a3880 0x402ab87f 0x402ab720  32752    448
0x0a010005 swi5: fast task       0x402abbb0 0x402b3baf 0x402b3a60  32752    432
0x0a010006 thread taskq          0x402b3d80 0x402bbd7f 0x402bbc20  32752    448
0x0a010007 swi6: Giant tas       0x402bc0b0 0x402c40af 0x402c3f60  32752    432
0x0a010008 swi6: task queu       0x402c43e0 0x402cc3df 0x402cc290  32752   1968
0x0a010009 kqueue_ctx task       0x402cc5b0 0x402d45af 0x402d4450  32752    448
0x0a01000a swi1: netisr 0        0x402d4800 0x402dc7ff 0x402dc3b0  32752   1952
0x0a01000b bufdaemon             0x40306a80 0x4030ea7f 0x4030e8a0  32752   1264
0x0a01000c vnlru                 0x4030eb50 0x40316b4f 0x403168e0  32752    720
0x0a01000d syncer                0x40316c20 0x4031ec1f 0x4031e9e0  32752    672
0x0a01000e softirq_0             0x4031edf0 0x40326def 0x40326c90  32752    448
0x0a01000f bufspacedaemon-       0x40326ec0 0x4032eebf 0x4032ed20  32752    512
0x0a010010 WORK                  0x4032ef90 0x4033178f 0x40331230  10224   1616
0x00000000 Interrupt Stack       0x40262400 0x40264bff 0x00000000  10224    480

*** END OF TEST LIBBSD SELECT AND POLL AND KQUEUE AND PIPE 1 ***


[ RTEMS shutdown ]
RTEMS version: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
RTEMS tools: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
executing thread ID: 0x08a010001
executing thread name: UI1 
```


##  rtems-libbsd  xilinx_zynqmp_lp64_qemu

###    kernel
```
 ./waf bsp_defaults --rtems-bsps=aarch64/xilinx_zynqmp_lp64_qemu   > config.ini
```

###    bsd

```
./waf configure --prefix=$HOME/development/rtems/compiler/6 --rtems-bsps=aarch64-rtems6/xilinx_zynqmp_lp64_qemu   --buildset=buildset/default.ini
```
