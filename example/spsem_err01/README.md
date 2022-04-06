 

# export 

export PATH=$HOME/development/rtems/compiler_arm/6/bin:$PATH
export RTEMS_MAKEFILE_PATH=$HOME/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu

# make

 ```
 arm-rtems6-gcc --pipe  -Wall  -O0 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib/include -Isupport -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/init.o init.c
arm-rtems6-gcc --pipe  -Wall  -O0 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib/include -Isupport -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9     -B/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib -qrtems -Wl,--gc-sections   -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9   -o o-optimize/hello.exe  o-optimize/init.o       
/root/development/rtems/compiler_arm/6/lib/gcc/arm-rtems6/10.3.1/../../../../arm-rtems6/bin/ld: o-optimize/init.o: in function `Init':
/root/development/rtems/rtems-examples/spsem_err01/init.c:32: undefined reference to `rtems_test_begin'
collect2: error: ld returned 1 exit status
make: *** [Makefile:26: o-optimize/hello.exe] Error 1


 ```
 
 
 ```
 [root@centos7 spsem_err01]# arm-rtems6-gcc --pipe  -Wall  -O0 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib/include -Isupport -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9     -B/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib -qrtems -Wl,--gc-sections   -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9   -o o-optimize/hello.exe  o-optimize/init.o   
/root/development/rtems/compiler_arm/6/lib/gcc/arm-rtems6/10.3.1/../../../../arm-rtems6/bin/ld: o-optimize/init.o: in function `Init':
/root/development/rtems/rtems-examples/spsem_err01/init.c:32: undefined reference to `rtems_test_begin'
collect2: error: ld returned 1 exit status
[root@centos7 spsem_err01]# ls /root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib
include        libftpd.a   libjffs2.a    librtemsbsp.a  librtemscxx.a            librtemstest.a  libtftpfs.a  linkcmds        linkcmds.armv7m  linkcmds.realview_pbx_a9_qemu
libdebugger.a  libftpfs.a  libmghttpd.a  librtemscpu.a  librtemsdefaultconfig.a  libtelnetd.a    libz.a       linkcmds.armv4  linkcmds.base    start.o
[root@centos7 spsem_err01]# 
 ```
 
##

```
rtems/cpukit/libtest/testbeginend.c
int rtems_test_begin(const char* name, const RTEMS_TEST_STATE state)
{
  return rtems_printf(
    &rtems_test_printer,
    "\n\n*** BEGIN OF TEST %s ***\n"
    "*** TEST VERSION: %s\n"
    "*** TEST STATE: %s\n"
    "*** TEST BUILD:"
#if RTEMS_DEBUG
    " RTEMS_DEBUG"
#endif
#if RTEMS_MULTIPROCESSING
    " RTEMS_MULTIPROCESSING"
#endif
#if RTEMS_NETWORKING
    " RTEMS_NETWORKING"
#endif
#if RTEMS_PARAVIRT
    " RTEMS_PARAVIRT"
#endif
#if RTEMS_POSIX_API
    " RTEMS_POSIX_API"
#endif
#if RTEMS_PROFILING
    " RTEMS_PROFILING"
#endif
#if RTEMS_SMP
    " RTEMS_SMP"
#endif
    "\n"
    "*** TEST TOOLS: " __VERSION__ "\n",
    name,
    rtems_version(),
    test_state_strings[state]
  );
}
```
 
### libtest

```
[root@centos7 rtems]# ls ./kernel2/rtems/build/arm/realview_pbx_a9_qemu/cpukit/libtest
testbeginend.c.80.d   testparallel.c.80.d  t-test-busy.c.80.d       t-test-checks.c.80.d      t-test-hash-sha256.c.80.d  t-test-rtems-context.c.80.d  t-test-rtems-measure.c.80.d  t-test-rtems-posix-keys.c.80.d
testbeginend.c.80.o   testparallel.c.80.o  t-test-busy.c.80.o       t-test-checks.c.80.o      t-test-hash-sha256.c.80.o  t-test-rtems-context.c.80.o  t-test-rtems-measure.c.80.o  t-test-rtems-posix-keys.c.80.o
testbusy.c.80.d       testrun.c.80.d       t-test-busy-tick.c.80.d  t-test-checks-eno.c.80.d  t-test-interrupt.c.80.d    t-test-rtems-fds.c.80.d      t-test-rtems-memory.c.80.d   t-test-thread-switch.c.80.d
testbusy.c.80.o       testrun.c.80.o       t-test-busy-tick.c.80.o  t-test-checks-eno.c.80.o  t-test-interrupt.c.80.o    t-test-rtems-fds.c.80.o      t-test-rtems-memory.c.80.o   t-test-thread-switch.c.80.o
testextension.c.80.d  testwrappers.c.80.d  t-test.c.80.d            t-test-checks-psx.c.80.d  t-test-rtems.c.80.d        t-test-rtems-heap.c.80.d     t-test-rtems-objs.c.80.d     t-test-time.c.80.d
testextension.c.80.o  testwrappers.c.80.o  t-test.c.80.o            t-test-checks-psx.c.80.o  t-test-rtems.c.80.o        t-test-rtems-heap.c.80.o     t-test-rtems-objs.c.80.o     t-test-time.c.80.o
[root@centos7 rtems]# 
```
###  lib
```
[root@centos7 spsem_err01]# ls $HOME/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib 
include   libdebugger.a  libftpfs.a  libmghttpd.a   librtemscpu.a  librtemsdefaultconfig.a  libtelnetd.a  libz.a    linkcmds.armv4   linkcmds.base
libbsd.a  libftpd.a      libjffs2.a  librtemsbsp.a  librtemscxx.a  librtemstest.a           libtftpfs.a   linkcmds  linkcmds.armv7m  start.o
[root@centos7 spsem_err01]# ls $HOME/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu
lib  make  Makefile.inc
[root@centos7 spsem_err01]# 
[root@centos7 spsem_err01]# ls $HOME/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib 
include        libftpd.a   libjffs2.a    librtemsbsp.a  librtemscxx.a            librtemstest.a  libtftpfs.a  linkcmds        linkcmds.armv7m  linkcmds.realview_pbx_a9_qemu
libdebugger.a  libftpfs.a  libmghttpd.a  librtemscpu.a  librtemsdefaultconfig.a  libtelnetd.a    libz.a       linkcmds.armv4  linkcmds.base    start.o
[root@centos7 spsem_err01]# ls $HOME/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib/
include                        libftpfs.a                     librtemsbsp.a                  librtemsdefaultconfig.a        libtftpfs.a                    linkcmds.armv4                 linkcmds.realview_pbx_a9_qemu  
libdebugger.a                  libjffs2.a                     librtemscpu.a                  librtemstest.a                 libz.a                         linkcmds.armv7m                start.o                        
libftpd.a                      libmghttpd.a                   librtemscxx.a                  libtelnetd.a                   linkcmds                       linkcmds.base                  
[root@centos7 spsem_err01]# ls $HOME/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib/
```
### LDFLAGS
```
[root@centos7 6]# ls make/custom/
default.cfg  raspberrypi.cfg  realview_pbx_a9_qemu.cfg  xilinx_zynq_a9_qemu.cfg
[root@centos7 6]# cat make/custom/realview_pbx_a9_qemu.cfg 
include $(RTEMS_ROOT)/make/custom/default.cfg
CPU_DEFINES = -I$(exec_prefix)/$(RTEMS_BSP)/lib/include
CPU_CFLAGS = -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9
CFLAGS_OPTIMIZE_V = -O0 -g -fdata-sections -ffunction-sections
LDFLAGS = -B$(exec_prefix)/$(RTEMS_BSP)/lib -qrtems -Wl,--gc-sections
[root@centos7 6]# 

```

###  librtemstest.a matches rtems_test_begin

```
[root@centos7 spsem_err01]# cd /root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib
[root@centos7 lib]# ls
include        libftpd.a   libjffs2.a    librtemsbsp.a  librtemscxx.a            librtemstest.a  libtftpfs.a  linkcmds        linkcmds.armv7m  linkcmds.realview_pbx_a9_qemu
libdebugger.a  libftpfs.a  libmghttpd.a  librtemscpu.a  librtemsdefaultconfig.a  libtelnetd.a    libz.a       linkcmds.armv4  linkcmds.base    start.o
[root@centos7 lib]# grep rtems_test_begin -rn *
include/rtems/test-info.h:100:int rtems_test_begin(const char* name, const RTEMS_TEST_STATE state);
Binary file librtemstest.a matches
```

### arm-rtems6-gcc  --help

```
compilation terminated.
[root@centos7 spsem_err01]# arm-rtems6-gcc  --help
Usage: arm-rtems6-gcc [options] file...
Options:
  -pass-exit-codes         Exit with highest error code from a phase.
  --help                   Display this information.
  --target-help            Display target specific command line options.
  --help={common|optimizers|params|target|warnings|[^]{joined|separate|undocumented}}[,...].
                           Display specific types of command line options.
  (Use '-v --help' to display command line options of sub-processes).
  --version                Display compiler version information.
  -dumpspecs               Display all of the built in spec strings.
  -dumpversion             Display the version of the compiler.
  -dumpmachine             Display the compiler's target processor.
  -print-search-dirs       Display the directories in the compiler's search path.
  -print-libgcc-file-name  Display the name of the compiler's companion library.
  -print-file-name=<lib>   Display the full path to library <lib>.
  -print-prog-name=<prog>  Display the full path to compiler component <prog>.
  -print-multiarch         Display the target's normalized GNU triplet, used as
                           a component in the library path.
  -print-multi-directory   Display the root directory for versions of libgcc.
  -print-multi-lib         Display the mapping between command line options and
                           multiple library search directories.
  -print-multi-os-directory Display the relative path to OS libraries.
  -print-sysroot           Display the target libraries directory.
  -print-sysroot-headers-suffix Display the sysroot suffix used to find headers.
  -Wa,<options>            Pass comma-separated <options> on to the assembler.
  -Wp,<options>            Pass comma-separated <options> on to the preprocessor.
  -Wl,<options>            Pass comma-separated <options> on to the linker.
  -Xassembler <arg>        Pass <arg> on to the assembler.
  -Xpreprocessor <arg>     Pass <arg> on to the preprocessor.
  -Xlinker <arg>           Pass <arg> on to the linker.
  -save-temps              Do not delete intermediate files.
  -save-temps=<arg>        Do not delete intermediate files.
  -no-canonical-prefixes   Do not canonicalize paths when building relative
                           prefixes to other gcc components.
  -pipe                    Use pipes rather than intermediate files.
  -time                    Time the execution of each subprocess.
  -specs=<file>            Override built-in specs with the contents of <file>.
  -std=<standard>          Assume that the input sources are for <standard>.
  --sysroot=<directory>    Use <directory> as the root directory for headers
                           and libraries.
  -B <directory>           Add <directory> to the compiler's search paths.
  -v                       Display the programs invoked by the compiler.
  -###                     Like -v but options quoted and commands not executed.
  -E                       Preprocess only; do not compile, assemble or link.
  -S                       Compile only; do not assemble or link.
  -c                       Compile and assemble, but do not link.
  -o <file>                Place the output into <file>.
  -pie                     Create a dynamically linked position independent
                           executable.
  -shared                  Create a shared library.
  -x <language>            Specify the language of the following input files.
                           Permissible languages include: c c++ assembler none
                           'none' means revert to the default behavior of
                           guessing the language based on the file's extension.

Options starting with -g, -f, -m, -O, -W, or --param are automatically
 passed on to the various sub-processes invoked by arm-rtems6-gcc.  In order to pass
 other options on to these processes the -W<letter> options must be used.

For bug reporting instructions, please see:
<https://gcc.gnu.org/bugs/>.
```

###  LDFLAGS
```
[root@centos7 spsem_err01]# cat Makefile 
#
#  RTEMS_MAKEFILE_PATH is typically set in an environment variable
#

PGM=${ARCH}/hello.exe

# optional managers required
MANAGERS=all

# C source names
CSRCS = init.c
COBJS = $(CSRCS:%.c=${ARCH}/%.o)

#include inc/rtems_config.h
include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
include $(RTEMS_CUSTOM)
include $(PROJECT_ROOT)/make/leaf.cfg

CPU_DEFINES += -Isupport
LDFLAGS += -L$(exec_prefix)/$(RTEMS_BSP)/lib -lrtemstest.a
OBJS= $(COBJS) $(CXXOBJS) $(ASOBJS)

all:    ${ARCH} $(PGM)

$(PGM): $(OBJS)
        $(make-exe)
```

```
[root@centos7 spsem_err01]# make
test -d o-optimize || mkdir o-optimize
arm-rtems6-gcc --pipe  -Wall  -O0 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib/include -Isupport -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/init.o init.c
arm-rtems6-gcc --pipe  -Wall  -O0 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib/include -Isupport -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9     -B/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib -qrtems -Wl,--gc-sections  -L/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib -lrtemstest.a  -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9   -o o-optimize/hello.exe  o-optimize/init.o       
/root/development/rtems/compiler_arm/6/lib/gcc/arm-rtems6/10.3.1/../../../../arm-rtems6/bin/ld: cannot find -lrtemstest.a
collect2: error: ld returned 1 exit status
```


```
LDFLAGS += -B $(TOOL_PATH)/arm-rtems5/beagleboneblack/lib -specs bsp_specs -qrtems -Wl,--gc-sections
LIBS	  += -Wl,-Bstatic -L. -lbsd -Wl,-Bdynamic -lm -lz 
CFLAGS  += -I $(TOOL_PATH)/arm-rtems5/beagleboneblack/lib/include -ffunction-sections -fdata-sections -g -mcpu=cortex-a8 -fno-strict-aliasing -ffreestanding -fno-common -w -DHAVE_RTEMS_SCORE_CPUOPTS_H=1 -DHAVE_RTEMS_H=1 -DHAVE_DLFCN_H=1 -DHAVE_RTEMS_PCI_H=1 -DHAVE_RTEMS_RTEMS_DEBUGGER_H=1 -g


```

# solve bugs

```
 //TEST_BEGIN();
 //TEST_END();
```
# run

```
[root@centos7 spsem_err01]# qemu-system-arm  -no-reboot -net none -nographic -smp 4 -icount auto -M realview-pbx-a9 -m 256M -kernel o-optimize/hello.exe
TA1 - rtems_semaphore_create - RTEMS_SUCCESSFUL
TA1 - rtems_semaphore_release - RTEMS_UNSATISFIED
TA1 - rtems_semaphore_delete - RTEMS_SUCCESSFUL
TA1 - rtems_semaphore_create - RTEMS_INVALID_NAME
TA1 - rtems_semaphore_create - RTEMS_INVALID_ADDRESS
TA1 - rtems_semaphore_create - 1 - RTEMS_SUCCESSFUL
TA1 - rtems_semaphore_create - 2 - RTEMS_SUCCESSFUL
TA1 - rtems_semaphore_create - 3 - RTEMS_TOO_MANY
TA1 - rtems_semaphore_create - FIFO and inherit - RTEMS_NOT_DEFINED
TA1 - rtems_semaphore_create - FIFO and ceiling - RTEMS_NOT_DEFINED
TA1 - rtems_semaphore_create - ceiling and inherit - RTEMS_NOT_DEFINED
TA1 - rtems_semaphore_create - RTEMS_NOT_DEFINED
TA1 - rtems_semaphore_create - RTEMS_INVALID_NUMBER
TA1 - rtems_semaphore_delete - RTEMS_INVALID_ID
TA1 - rtems_semaphore_delete - local RTEMS_INVALID_ID
TA1 - rtems_semaphore_ident - global RTEMS_INVALID_NAME
TA1 - rtems_semaphore_ident - local RTEMS_INVALID_NAME
TA1 - rtems_semaphore_release - RTEMS_INVALID_ID
TA1 - rtems_semaphore_flush - RTEMS_INVALID_ID

*** FATAL ***
fatal source: 0 (INTERNAL_ERROR_CORE)
CPU: 0
fatal code: 5 (INTERNAL_ERROR_THREAD_EXITTED)
RTEMS version: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
RTEMS tools: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
executing thread ID: 0x08a010001
executing thread name: UI1 
[root@centos7 spsem_err01]# 
```

# refercence

https://github.com/hermixy?after=Y3Vyc29yOjMw&language=&q=rtems&sort=&tab=repositories<br>
https://github.com/alanc98?tab=repositories&q=rtems&type=&language=&sort=