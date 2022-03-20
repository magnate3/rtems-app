

#  compile


##  CPU_DEFINES



/root/development/rtems/compiler/6/make/custom/a53_lp64_qemu.cfg

```
[root@centos7 6]# cat make/custom/a53_lp64_qemu.cfg
include $(RTEMS_ROOT)/make/custom/default.cfg
CPU_DEFINES = -I$(exec_prefix)/$(RTEMS_BSP)/lib/include
CPU_CFLAGS = -mcpu=cortex-a53
CFLAGS_OPTIMIZE_V = -O2 -g -fdata-sections -ffunction-sections
LDFLAGS = -B$(exec_prefix)/$(RTEMS_BSP)/lib -qrtems -Wl,--gc-sections
[root@centos7 6]#
```
in Makefile add 
```
CPU_DEFINES += -Iinc
```

##  You must define one of CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

```
[root@centos7 hello_world_rtems]# make
aarch64-rtems6-gcc --pipe  -Wall  -O2 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/include -Iinc -mcpu=cortex-a53      -c   -o o-optimize/main.o main.c
In file included from /root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/include/rtems/confdefs.h:64,
                 from inc/rtems_config.h:63,
                 from main.c:21:
/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/include/rtems/confdefs/clock.h:51:4: error: #error "You must define one of CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER, CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER, and CONFIGURE_APPLICATION_NEEDS_TIMER_DRIVER"
   51 |   #error "You must define one of CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER, CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER, and CONFIGURE_APPLICATION_NEEDS_TIMER_DRIVER"
      |    ^~~~~
make: *** [/root/development/rtems/compiler/6/share/rtems6/make/compilers/gcc-target-default.cfg:100: o-optimize/main.o] Error 1
```

in  inc/rtems_config.h  add :
```
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER  /* for stdio */
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER    /* for time services */
```

## make

```
[root@centos7 hello_world_rtems]# make
aarch64-rtems6-gcc --pipe  -Wall  -O2 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/include -Iinc -mcpu=cortex-a53      -c   -o o-optimize/main.o main.c
aarch64-rtems6-gcc --pipe  -Wall  -O2 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/include -Iinc -mcpu=cortex-a53     -B/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib -qrtems -Wl,--gc-sections   -mcpu=cortex-a53   -o o-optimize/hello.exe  o-optimize/main.o       
aarch64-rtems6-nm -g -n o-optimize/hello.exe > o-optimize/hello.num
aarch64-rtems6-size o-optimize/hello.exe
   text    data     bss     dec     hex filename
  85137    1880 134096352       134183369       7ff79c9 o-optimize/hello.exe
cp o-optimize/hello.exe o-optimize/hello.ralf
```

#  run

```
[root@centos7 hello_world_rtems]# qemu-system-aarch64 -no-reboot -nographic -serial mon:stdio  -machine virt,gic-version=3 -cpu cortex-a53 -m 4096 -kernel o-optimize/hello.exe 
Hello World

[ RTEMS shutdown ]
RTEMS version: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
RTEMS tools: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
executing thread ID: 0x08a010001
executing thread name: UI1 
```

