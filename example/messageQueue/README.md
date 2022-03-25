** this case is changed from testsuites/rhealstone **

# make

```
export PATH=$HOME/development/rtems/compiler_arm/6/bin:$PATH
export RTEMS_MAKEFILE_PATH=$HOME/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu
```

```
[root@centos7 messageQueue]# make
test -d o-optimize || mkdir o-optimize
arm-rtems6-gcc --pipe  -Wall  -O0 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib/include -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/messageQueue.o messageQueue.c
arm-rtems6-gcc --pipe  -Wall  -O0 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib/include -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9     -B/root/development/rtems/compiler_arm/6/arm-rtems6/realview_pbx_a9_qemu/lib -qrtems -Wl,--gc-sections   -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9   -o o-optimize/messageQueue.exe  o-optimize/messageQueue.o       
arm-rtems6-nm -g -n o-optimize/messageQueue.exe > o-optimize/messageQueue.num
arm-rtems6-size o-optimize/messageQueue.exe
   text    data     bss     dec     hex filename
 189329    1728 262985068       263176125       fafbfbd o-optimize/messageQueue.exe
cp o-optimize/messageQueue.exe o-optimize/messageQueue.ralf
#mcopy -o o-optimize/messageQueue.exe x:
[root@centos7 messageQueue]# 
```
 
 
# run

```
[root@centos7 messageQueue]# qemu-system-arm  -no-reboot -net none -nographic -smp 4 -icount auto -M realview-pbx-a9 -m 256M -kernel o-optimize/messageQueue.exe 
Enter the number of terms to use in the series: 23
Value passed:23
The approximate value of pi using 23 terms is 3.185050
Enter the number of terms to use in the series: 99999
Value passed:99999
The approximate value of pi using 99999 terms is 3.141603
Enter the number of terms to use in the series: 
```

 



