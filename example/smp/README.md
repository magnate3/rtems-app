# build kernel

```
./waf  bsp_list | grep arm

 (1)./waf bsp_defaults --rtems-bsps=arm/xilinx_zynq_a9_qemu   > config.ini
 RTEMS_POSIX_API = True in config.ini
 
 # Enable the Symmetric Multiprocessing (SMP) support
RTEMS_SMP = True
 (2)./waf configure --prefix=$HOME/development/rtems/compiler_arm/6
 (3)./waf 
 (4)./waf install
```

# export 

export PATH=$HOME/development/rtems/compiler_arm/6/bin:$PATH
export RTEMS_MAKEFILE_PATH=$HOME/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu

# make

```
[root@centos7 smp]# make
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9     -B/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib -qrtems -Wl,--gc-sections   -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9   -o o-optimize/hello.exe  o-optimize/test.o       
/root/development/rtems/compiler_arm/6/lib/gcc/arm-rtems6/10.3.1/../../../../arm-rtems6/bin/ld: o-optimize/test.o: in function `.LC13':
test.c:(.rodata+0x160): undefined reference to `rtems_test_fatal_extension'
collect2: error: ld returned 1 exit status
make: *** [Makefile:23: o-optimize/hello.exe] Error 1
```

##
cpukit/include/rtems/test-info.h


```
/**
 * @brief Fatal extension for tests.
 */
void rtems_test_fatal_extension(
  rtems_fatal_source source,
  bool always_set_to_false,
  rtems_fatal_code code
);

/**
 * @brief Initial extension for tests.
 */
#define RTEMS_TEST_INITIAL_EXTENSION \
  { NULL, NULL, NULL, NULL, NULL, NULL, NULL, rtems_test_fatal_extension }
  
  
```

in test.c

```
#define CONFIGURE_INITIAL_EXTENSIONS RTEMS_TEST_INITIAL_EXTENSION
```


## slove bugs

not need
//#define CONFIGURE_INITIAL_EXTENSIONS RTEMS_TEST_INITIAL_EXTENSION


# run

```
qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M -smp 4    -kernel o-optimize/hello.exe
qemu-system-arm: Invalid SMP CPUs 4. The max CPUs supported by machine 'xilinx-zynq-a9' is 1
```

# arm/realview_pbx_a9_qemu 

## build kernel

```
[root@centos7 rtems]# ./waf  bsp_list | grep arm | grep qemu
arm/lm3s6965_qemu
arm/realview_pbx_a9_qemu
arm/xilinx_zynq_a9_qemu
[root@centos7 rtems]# 
```

```
./waf bsp_defaults --rtems-bsps=arm/realview_pbx_a9_qemu   > config.ini
./waf configure --prefix=$HOME/development/rtems/compiler_arm/6
[root@centos7 rtems]# ls $HOME/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu 
lib  make  Makefile.inc
[root@centos7 rtems]# 
```


## export 

export PATH=$HOME/development/rtems/compiler_arm/6/bin:$PATH
export RTEMS_MAKEFILE_PATH=$HOME/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu

## run

```
qemu-system-arm  -no-reboot -net none -nographic -smp 4 -icount auto -M realview-pbx-a9 -m 256M -kernel o-optimize/hello.exe
```


![image](https://github.com/magnate3/rtems-app/blob/main/example/smp/pic/smp.png)