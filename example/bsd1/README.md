
# make

## make bug

```
[root@centos7 event]# make
Makefile:16: /make/leaf.cfg: No such file or directory
make: *** No rule to make target '/make/leaf.cfg'.  Stop.
[root@centos7 event]# ls
Makefile  o-optimize  Readme  test.c  wscript
[root@centos7 event]# export PATH=$HOME/development/rtems/compiler_arm/6/bin:$PATH
[root@centos7 event]# export RTEMS_MAKEFILE_PATH=$HOME/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu
[root@centos7 event]# make
make: Nothing to be done for 'default_target'.
[root@centos7 event]# cd -
/root/development/rtems/rtems-examples/media01
[root@centos7 media01]# make 
test -d o-optimize || mkdir o-optimize
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/pattern-test.o pattern-test.c
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/test_main.o test_main.c
test_main.c:210:10: fatal error: rtems/bsd/test/default-network-init.h: No such file or directory
  210 | #include <rtems/bsd/test/default-network-init.h>
      |          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
compilation terminated.
make: *** [/root/development/rtems/compiler_arm/6/share/rtems6/make/compilers/gcc-target-default.cfg:100: o-optimize/test_main.o] Error 1
[root@centos7 media01]#
```


## reference  makefile
```
#
# 	Template leaf node Makefile
#

# C source names, if any, go here -- minus the .c
C_PIECES=xxxd xxxe xxxf
C_FILES=$(C_PIECES:%=%.c)
C_O_FILES=$(C_PIECES:%=${ARCH}/%.o)

# C++ source names, if any, go here -- minus the .cc
CC_PIECES=xxxa xxxb xxxc
CC_FILES=$(CC_PIECES:%=%.cc)
CC_O_FILES=$(CC_PIECES:%=${ARCH}/%.o)

H_FILES=

# Assembly source names, if any, go here -- minus the .S
S_PIECES=
S_FILES=$(S_PIECES:%=%.S)
S_O_FILES=$(S_FILES:%.S=${ARCH}/%.o)

SRCS=$(C_FILES) $(CC_FILES) $(H_FILES) $(S_FILES)
OBJS=$(C_O_FILES) $(CC_O_FILES) $(S_O_FILES)

PGMS=${ARCH}/xxx-your-program-here ${ARCH}/xxx-another-one

include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
include $(RTEMS_CUSTOM)
include $(RTEMS_ROOT)/make/leaf.cfg

#
# (OPTIONAL) Add local stuff here using +=
#

DEFINES  +=
CPPFLAGS +=
CFLAGS   +=

#
# CFLAGS_DEBUG_V are used when the `make debug' target is built.
#

LD_PATHS  += xxx-your-EXTRA-library-paths-go-here, if any
LD_LIBS   += xxx-your-libraries-go-here eg: -lvx
LDFLAGS   +=

#
# Add your list of files to delete here.  The config files
#  already know how to delete some stuff, so you may want
#  to just run 'make clean' first to see what gets missed.
#  'make clobber' already includes 'make clean'
#

CLEAN_ADDITIONS += xxx-your-debris-goes-here
CLOBBER_ADDITIONS +=

all:	${ARCH} $(SRCS) $(PGMS)

# The following links using C rules.
${ARCH}/xxx-your-program-here: ${OBJS} ${LINK_FILES}
	$(make-exe)

# The following links using C++ rules to get the C++ libraries.
# Be sure you BSP has a make-cxx-exe rule if you use this.
# ${ARCH}/xxx-your-program-here: ${OBJS} ${LINK_FILES}
# 	$(make-cxx-exe)

# Install the program(s), appending _g or _p as appropriate.
# for include files, just use $(INSTALL_CHANGE)
install:  all
	$(INSTALL_VARIANT) -m 555 ${PGMS} ${PROJECT_RELEASE}/bin

```


## make successfully

```
[root@centos7 event]# export PATH=$HOME/development/rtems/compiler_arm/6/bin:$PATH
[root@centos7 event]# export RTEMS_MAKEFILE_PATH=$HOME/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu
```

```
[root@centos7 test-rtems5]# make
test -d o-optimize || mkdir o-optimize
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/hello.o hello.c
hello.c: In function 'POSIX_Init':
hello.c:18:9: warning: unused variable 'exit_code' [-Wunused-variable]
   18 |     int exit_code;
      |         ^~~~~~~~~
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/init.o init.c
In file included from /root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include/rtems/confdefs.h:68,
                 from init.c:49:
/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include/rtems/confdefs/initthread.h:56:51: warning: initialization of 'void * (*)(void *)' from incompatible pointer type 'void (*)(rtems_task_argument)' {aka 'void (*)(unsigned int)'} [-Wincompatible-pointer-types]
   56 |   #define CONFIGURE_POSIX_INIT_THREAD_ENTRY_POINT POSIX_Init
      |                                                   ^~~~~~~~~~
/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include/rtems/confdefs/initthread.h:76:3: note: in expansion of macro 'CONFIGURE_POSIX_INIT_THREAD_ENTRY_POINT'
   76 |   CONFIGURE_POSIX_INIT_THREAD_ENTRY_POINT,
      |   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include/rtems/confdefs/initthread.h:56:51: note: (near initialization for '_POSIX_Threads_User_thread_table.thread_entry')
   56 |   #define CONFIGURE_POSIX_INIT_THREAD_ENTRY_POINT POSIX_Init
      |                                                   ^~~~~~~~~~
/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include/rtems/confdefs/initthread.h:76:3: note: in expansion of macro 'CONFIGURE_POSIX_INIT_THREAD_ENTRY_POINT'
   76 |   CONFIGURE_POSIX_INIT_THREAD_ENTRY_POINT,
      |   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9     -B/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib -qrtems -Wl,--gc-sections   -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9   -o o-optimize/hello.exe  o-optimize/hello.o o-optimize/init.o   -lftpd -lbsd -lm    
arm-rtems6-nm -g -n o-optimize/hello.exe > o-optimize/hello.num
arm-rtems6-size o-optimize/hello.exe
   text    data     bss     dec     hex filename
2198184 1089120 264084564       267371868       fefc55c o-optimize/hello.exe
cp o-optimize/hello.exe o-optimize/hello.ralf
[root@centos7 test-rtems5]# 
```

# run

```
 qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12   -kernel   o-optimize/hello.exe
```

![Alt text](https://github.com/magnate3/rtems-app/blob/main/example/bsd1/pic/bsd1.png)




## error
```
RTEMS version: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
RTEMS tools: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
executing thread ID: 0x08b010001
executing thread name: 

*** FATAL ***
fatal source: 9 (RTEMS_FATAL_SOURCE_EXCEPTION)
CPU: 0

R0   = 0x0040da80 R8  = 0x0f2fee40
R1   = 0x0f2fefac R9  = 0x0029a970
R2   = 0x0029a9a0 R10 = 0x00000000
R3   = 0x0051eb7c R11 = 0x00001000
R4   = 0x0f2fef40 R12 = 0x00000004
R5   = 0x005414e0 SP  = 0x005414a8
R6   = 0x20000000 LR  = 0x001698e9
R7   = 0x00000080 PC  = 0x00169902
CPSR = 0x400f0173 VEC = 0x00000004
FPEXC = 0x40000000
FPSCR = 0x00000000
D00 = 0xffffffff00319f0c
D01 = 0x0000000000000000
D02 = 0x0000000000000000
D03 = 0x0000000000000000
D04 = 0x0000000000000000
D05 = 0x0000000000000000
D06 = 0x0000000000000000
D07 = 0x0000000000000000
D08 = 0x0000000000000000
D09 = 0x0000000000000000
D10 = 0x0000000000000000
D11 = 0x0000000000000000
D12 = 0x0000000000000000
D13 = 0x0000000000000000
D14 = 0x0000000000000000
D15 = 0x0000000000000000
D16 = 0x0000000000000000
D17 = 0x0000000000000000
D18 = 0x0000000000000000
D19 = 0x0000000000000000
D20 = 0x0000000000000000
D21 = 0x0000000000000000
D22 = 0x0000000000000000
D23 = 0x0000000000000000
D24 = 0x0000000000000000
D25 = 0x0000000000000000
D26 = 0x0000000000000000
D27 = 0x0000000000000000
D28 = 0x0000000000000000
D29 = 0x0000000000000000
D30 = 0x0000000000000000
D31 = 0x0000000000000000
RTEMS version: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
RTEMS tools: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
executing thread ID: 0x08b010001
executing thread name: 

*** FATAL ***
fatal source: 9 (RTEMS_FATAL_SOURCE_EXCEPTION)
CPU: 0

R0   = 0x0040da80 R8  = 0x0f2fee40
R1   = 0x0f2fefac R9  = 0x0029a970
R2   = 0x0029a9a0 R10 = 0x00000000
R3   = 0x0051eb7c R11 = 0x00001000
R4   = 0x0f2fef40 R12 = 0x00000004
R5   = 0x005414e0 SP  = 0x005414a8
R6   = 0x20000000 LR  = 0x001698e9
R7   = 0x00000080 PC  = 0x00169902
CPSR = 0x400f0173 VEC = 0x00000004
FPEXC = 0x40000000
FPSCR = 0x00000000
D00 = 0xffffffff00319f0c
D01 = 0x0000000000000000
D02 = 0x0000000000000000
D03 = 0x0000000000000000
D04 = 0x0000000000000000
D05 = 0x0000000000000000
D06 = 0x0000000000000000
D07 = 0x0000000000000000
D08 = 0x0000000000000000
D09 = 0x0000000000000000
D10 = 0x0000000000000000
D11 = 0x0000000000000000
D12 = 0x0000000000000000
D13 = 0x0000000000000000
D14 = 0x0000000000000000
D15 = 0x0000000000000000
D16 = 0x0000000000000000
D17 = 0x0000000000000000
D18 = 0x0000000000000000
D19 = 0x0000000000000000
D20 = 0x0000000000000000
D21 = 0x0000000000000000
D22 = 0x0000000000000000
D23 = 0x0000000000000000
D24 = 0x0000000000000000
D25 = 0x0000000000000000
D26 = 0x0000000000000000
D27 = 0x0000000000000000
D28 = 0x00000000QEMU: Terminated
```