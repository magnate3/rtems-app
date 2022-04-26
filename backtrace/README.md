# files
```
[root@centos7 rtems]# ls bsps/shared/start/arm-backtrace-print.c 
bsps/shared/start/arm-backtrace-print.c
[root@centos7 rtems]# ls bsps/include/bsp/my_fatal.h 
bsps/include/bsp/my_fatal.h
[root@centos7 rtems]# 
 ```
 
 # demo
 
 ```
 qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12   -kernel   o-optimize/hello.exe
 ```
 
 ```
 executing backtrace dump
*** Beginning of backtrace: ***
#0 0x1049b8 
*** FATAL ***
fatal source: 9 (RTEMS_FATAL_SOURCE_EXCEPTION)

R0   = 0xfff15964 R8  = 0x00000000
R1   = 0xfff15960 R9  = 0x0010c451
R2   = 0x00200850 R10 = 0x0000000c
R3   = 0x00000000 R11 = 0x00000000
R4   = 0x00000004 R12 = 0xffffffff
R5   = 0xfff15964 SP  = 0x00200760
R6   = 0x0011022f LR  = 0x0010e5b6
R7   = 0x00000001 PC  = 0x0010e5b6
CPSR = 0x200f01f7 VEC = 0x00000004
FPEXC = 0x40000000
FPSCR = 0x00000000
D00 = 0x0000000000000000
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
D16 = 0x0000000021dae500
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
executing backtrace dump
*** Beginning of backtrace: ***
#0 0x1049b8 QEMU: Terminated
 ```