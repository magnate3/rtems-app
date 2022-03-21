
# build kernel

```
[root@centos7 rtems]# pwd
/root/development/rtems/kernel2/rtems
```

```
 (1) ./waf bsp_defaults --rtems-bsps=arm/realview_pbx_a9_qemu   > config.ini
 RTEMS_POSIX_API = True in config.ini
 
 # Enable the Symmetric Multiprocessing (SMP) support
RTEMS_SMP = True

  BUILD_SAMPLES = True
  BUILD_TESTS = False
 (2) ./waf configure --prefix=$HOME/development/rtems/compiler_arm/6
 (3)./waf 
 (4)./waf install
```
## samples/ticker.exe
```
[root@centos7 rtems]# ls ./build/arm/realview_pbx_a9_qemu/testsuites/samples/ticker.exe
./build/arm/realview_pbx_a9_qemu/testsuites/samples/ticker.exe
```

##

```
[root@centos7 rtems]# pwd
/root/development/rtems/kernel2/rtems
```

```
[root@centos7 rtems]# qemu-system-arm  -no-reboot -net none -nographic -smp 4 -icount auto -M realview-pbx-a9 -m 256M -kernel ./build/arm/realview_pbx_a9_qemu/testsuites/samples/ticker.exe


*** BEGIN OF TEST CLOCK TICK ***
*** TEST VERSION: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
*** TEST STATE: EXPECTED_PASS
*** TEST BUILD: RTEMS_POSIX_API RTEMS_SMP
*** TEST TOOLS: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
TA1  - rtems_clock_get_tod - 09:00:00   12/31/1988
TA2  - rtems_clock_get_tod - 09:00:00   12/31/1988
TA3  - rtems_clock_get_tod - 09:00:00   12/31/1988
TA1  - rtems_clock_get_tod - 09:00:04   12/31/1988
TA2  - rtems_clock_get_tod - 09:00:09   12/31/1988
TA1  - rtems_clock_get_tod - 09:00:09   12/31/1988
TA3  - rtems_clock_get_tod - 09:00:14   12/31/1988
TA1  - rtems_clock_get_tod - 09:00:14   12/31/1988
TA2  - rtems_clock_get_tod - 09:00:19   12/31/1988
TA1  - rtems_clock_get_tod - 09:00:19   12/31/1988
TA1  - rtems_clock_get_tod - 09:00:24   12/31/1988
TA3  - rtems_clock_get_tod - 09:00:29   12/31/1988
TA2  - rtems_clock_get_tod - 09:00:29   12/31/1988
TA1  - rtems_clock_get_tod - 09:00:29   12/31/1988
TA1  - rtems_clock_get_tod - 09:00:34   12/31/1988

*** END OF TEST CLOCK TICK ***


[ RTEMS shutdown ]
CPU: 0
RTEMS version: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
RTEMS tools: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
executing thread ID: 0x08a010003
executing thread name: TA2
```