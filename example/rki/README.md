# make

```
 arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -I ./include -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/rtems_net.o rtems_net.c
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -I ./include -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/rtems_net_svc.o rtems_net_svc.c
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -I ./include -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/task_cmd.o task_cmd.c
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -I ./include -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/whetstone_cmd.o whetstone_cmd.c
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -I ./include -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9     -B/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib -qrtems -Wl,--gc-sections   -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9   -o o-optimize/hello.exe  o-optimize/benchmarks.o o-optimize/dhrystone_cmd.o o-optimize/filesys.o o-optimize/hello_cmd.o o-optimize/init.o o-optimize/local_shell_cmds.o o-optimize/nvramdisk.o o-optimize/ramdisk.o o-optimize/rtems_net.o o-optimize/rtems_net_svc.o o-optimize/task_cmd.o o-optimize/whetstone_cmd.o   -lftpd -lbsd -lm    
arm-rtems6-nm -g -n o-optimize/hello.exe > o-optimize/hello.num
arm-rtems6-size o-optimize/hello.exe
   text    data     bss     dec     hex filename
 353740    5328 267011320       267370388       fefbf94 o-optimize/hello.exe
cp o-optimize/hello.exe o-optimize/hello.ralf
```

# run

```
[root@centos7 rki]#  qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12   -kernel   o-optimize/hello.exe
qemu-system-arm: warning: nic cadence_gem.1 has no peer


RTEMS Kernel Image Booting


*** RTEMS Info ***

 BSP Ticks Per Second = 100
*** End RTEMS info ***

Setting up filesystems.
Initializing Local Commands.
Running /shell-init.

shell: open input /shell-init failed: No such file or directory
Starting shell....


RTEMS Shell on /dev/console. Use 'help' to list commands.
shell0 [/] # task
ID       NAME                 SHED PRI STATE  MODES    EVENTS WAITINFO
------------------------------------------------------------------------------
0a010001 UI1                  UPD  120 EV     P:T:nA   NONE   
0a010002 BSWP                 UPD   10 EV     P:T:nA   NONE   
0a010004 shel                 UPD  100 READY  P:T:nA   NONE   
shell0 [/] # sema
  ID       NAME   ATTR        PRICEIL CURR_CNT HOLDID 
------------------------------------------------------------------------------
shell0 [/] # dhrystone
Running Dhrystone Command!

Dhrystone Benchmark, Version 2.1 (Language: C)

Program compiled without 'register' attribute

Number of runs is 1000000
Execution starts, 1000000 runs through Dhrystone
Execution ends

Final values of the variables used in the benchmark:

Int_Glob:            5
        should be:   5
Bool_Glob:           1
        should be:   1
Ch_1_Glob:           A
        should be:   A
Ch_2_Glob:           B
        should be:   B
Arr_1_Glob[8]:       7
        should be:   7
Arr_2_Glob[8][7]:    1000010
        should be:   Number_Of_Runs + 10
Ptr_Glob->
  Ptr_Comp:          3394776
        should be:   (implementation-dependent)
  Discr:             0
        should be:   0
  Enum_Comp:         2
        should be:   2
  Int_Comp:          17
        should be:   17
  Str_Comp:          DHRYSTONE PROGRAM, SOME STRING
        should be:   DHRYSTONE PROGRAM, SOME STRING
Next_Ptr_Glob->
  Ptr_Comp:          3394776
        should be:   (implementation-dependent), same as above
  Discr:             0
        should be:   0
  Enum_Comp:         1
        should be:   1
  Int_Comp:          18
        should be:   18
  Str_Comp:          DHRYSTONE PROGRAM, SOME STRING
        should be:   DHRYSTONE PROGRAM, SOME STRING
Int_1_Loc:           5
        should be:   5
Int_2_Loc:           13
        should be:   13
Int_3_Loc:           7
        should be:   7
Enum_Loc:            1
        should be:   1
Str_1_Loc:           DHRYSTONE PROGRAM, 1'ST STRING
        should be:   DHRYSTONE PROGRAM, 1'ST STRING
Str_2_Loc:           DHRYSTONE PROGRAM, 2'ND STRING
        should be:   DHRYSTONE PROGRAM, 2'ND STRING

Microseconds for one run through Dhrystone:    2.0 
Dhrystones per Second:                      500000.0 

Completed Dhrystone
shell0 [/] # whetstone
Running Whetstone Command!
      0       0       0   1.0000e+00  -1.0000e+00  -1.0000e+00  -1.0000e+00
     60      70      60  -6.7500e-02  -4.6465e-01  -7.3153e-01  -1.1286e+00
     70      60      60  -6.0913e-02  -4.5692e-01  -7.2207e-01  -1.1181e+00
   1725       0       0   1.0000e+00  -1.0000e+00  -1.0000e+00  -1.0000e+00
   1050       1       2   6.0000e+00   6.0000e+00  -7.2207e-01  -1.1181e+00
    160       1       2   4.9518e-01   4.9518e-01   4.9516e-01   4.9516e-01
   4495       1       2   1.0000e+00   1.0000e+00   9.9994e-01   9.9994e-01
   3080       1       2   3.0000e+00   2.0000e+00   3.0000e+00  -1.1181e+00
      0       2       3   1.0000e+00  -1.0000e+00  -1.0000e+00  -1.0000e+00
    465       2       3   7.9611e-01   7.9611e-01   7.9611e-01   7.9611e-01

Insufficient duration- Increase the LOOP count
Completed Whetstone
shell0 [/] # hello
Hello RTEMS!
Create your own command here!
shell0 [/] # taskdemo


*** TASKING DEMO ***


  Create 5 tasks that will run for 10 seconds
shell0 [/] # *** TASK 0x0A010005 FINISHED ***
*** TASK 0x0A010006 FINISHED ***
*** TASK 0x0A010007 FINISHED ***
*** TASK 0x0A010008 FINISHED ***
*** TASK 0x0A010009 FINISHED ***

shell0 [/] #  help
help: The topics are
  all, misc, help, files, mem, rtems, monitor
shell0 [/] # cat shell-init
cat: shell-init: No such file or directory
shell0 [/] # ls
dev etc
shell0 [/] # 
 
```
 