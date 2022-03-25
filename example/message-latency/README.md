** this case is changed from testsuites/rhealstone **

# make

```
export PATH=$HOME/development/rtems/compiler_arm/6/bin:$PATH
export RTEMS_MAKEFILE_PATH=$HOME/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu
```

```
[root@centos7 message-latency]# make
test -d o-optimize || mkdir o-optimize
arm-rtems6-gcc --pipe  -Wall  -O0 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib/include -I../support -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/message-latency.o message-latency.c
message-latency.c: In function 'Init':
message-latency.c:68:3: warning: implicit declaration of function 'benchmark_timer_initialize' [-Wimplicit-function-declaration]
   68 |   benchmark_timer_initialize();
      |   ^~~~~~~~~~~~~~~~~~~~~~~~~~
message-latency.c:72:20: warning: implicit declaration of function 'benchmark_timer_read' [-Wimplicit-function-declaration]
   72 |   tloop_overhead = benchmark_timer_read();
      |                    ^~~~~~~~~~~~~~~~~~~~
arm-rtems6-gcc --pipe  -Wall  -O0 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib/include -I../support -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9     -B/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib -qrtems -Wl,--gc-sections   -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9   -o o-optimize/hello.exe  o-optimize/message-latency.o       
arm-rtems6-nm -g -n o-optimize/hello.exe > o-optimize/hello.num
arm-rtems6-size o-optimize/hello.exe
   text    data     bss     dec     hex filename
 152265    1712 263022148       263176125       fafbfbd o-optimize/hello.exe
cp o-optimize/hello.exe o-optimize/hello.ralf

```
# run

```

[root@centos7 message-latency]# qemu-system-arm  -no-reboot -net none -nographic -smp 4 -icount auto -M realview-pbx-a9 -m 256M -kernel o-optimize/hello.exe
*************** Rhealstone: Intertask Message Latency - 0

[ RTEMS shutdown ]
CPU: 0
RTEMS version: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
RTEMS tools: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
executing thread ID: 0x08a010003
executing thread name: TA02
[root@centos7 message-latency]# 
```



