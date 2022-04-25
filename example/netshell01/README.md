# build/arm-rtems6-xilinx_zynq_a9_qemu-default/netshell01.exe 
 
 ```
 [root@centos7 rtems-libbsd-a64]#  qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12   -kernel build/arm-rtems6-xilinx_zynq_a9_qemu-default/netshell01.exe
 ```
```
[root@centos7 rtems-libbsd-a64]#  qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12   -kernel build/arm-rtems6-xilinx_zynq_a9_qemu-default/netshell01.exe 
qemu-system-arm: warning: nic cadence_gem.1 has no peer


*** BEGIN OF TEST LIBBSD NETSHELL 1 ***
*** TEST VERSION: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
*** TEST STATE: USER_INPUT
*** TEST BUILD: RTEMS_POSIX_API
*** TEST TOOLS: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
nexus0: <RTEMS Nexus device>

RTEMS Shell on /dev/console. Use 'help' to list commands.
RTSH [/] # ls
dev etc
RTSH [/] # ip a         
ip: command not found
RTSH [/] # ls dev/
bpf     bpf0    console null    ttyS0   ttyS1   zero
RTSH [/] # ls etc/    
group     issue     issue.net passwd
RTSH [/] # 
```

## make
```
[root@centos7 event]# export PATH=$HOME/development/rtems/compiler_arm/6/bin:$PATH
[root@centos7 event]# export RTEMS_MAKEFILE_PATH=$HOME/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu
```


 ```
 [root@centos7 netshell01]# make
test -d o-optimize || mkdir o-optimize
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -I ./ -I ./waf -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/shellconfig.o shellconfig.c
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -I ./ -I ./waf -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/test_main.o test_main.c
In file included from /root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include/rtems/confdefs.h:61,
                 from default-network-init.h:293,
                 from test_main.c:173:
/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include/rtems/confdefs/obsolete.h:110:4: warning: #warning "CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS has been renamed to CONFIGURE_MAXIMUM_FILE_DESCRIPTORS since RTEMS 5.1" [-Wcpp]
  110 |   #warning "CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS has been renamed to CONFIGURE_MAXIMUM_FILE_DESCRIPTORS since RTEMS 5.1"
      |    ^~~~~~~
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -I ./ -I ./waf -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9     -B/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib -qrtems -Wl,--gc-sections   -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9   -o o-optimize/hello.exe  o-optimize/shellconfig.o o-optimize/test_main.o   -lftpd -lbsd -lm    
arm-rtems6-nm -g -n o-optimize/hello.exe > o-optimize/hello.num
arm-rtems6-size o-optimize/hello.exe
   text    data     bss     dec     hex filename
1367872  233556 265770444       267371872       fefc560 o-optimize/hello.exe
cp o-optimize/hello.exe o-optimize/hello.ralf
[root@centos7 netshell01]# 
 ```

## run

```
 qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12   -kernel   o-optimize/hello.exe
```

 




## error
```
 RTEMS version: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
RTEMS tools: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
executing thread ID: 0x08a010001
executing thread name: UI1 
*** LIBBSD NETSHELL 1 TEST ***

*** FATAL ***
fatal source: 9 (RTEMS_FATAL_SOURCE_EXCEPTION)
CPU: 0

R0   = 0x0030ea00 R8  = 0x0f2fee40
R1   = 0x0f2fefac R9  = 0x00229d74
R2   = 0x00229da4 R10 = 0x00000000
R3   = 0x0036a1cc R11 = 0x00001000
R4   = 0x0f2fef40 R12 = 0x00000004
R5   = 0x003821f0 SP  = 0x003821b8
R6   = 0x20000000 LR  = 0x00177c79
R7   = 0x00000080 PC  = 0x00177c92
CPSR = 0x40000173 VEC = 0x00000004
FPEXC = 0x40000000
FPSCR = 0x00000000
D00 = 0x0a0a0a0a0a0a0a0a
D01 = 0x0a0a0a0a0a0a0a0a
D02 = 0x0000000000000000
D03 = 0x0000000000000000
D04 = 0x0000000000000000
D05 = 0x0000000000000000
D06 = 0x8040201008040201
D07 = 0x8040201008040201
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
executing thread ID: 0x08a010001
executing thread name: UI1 
*** LIBBSD NETSHELL 1 TEST ***
QEMU: Terminated
```

* RTEMS_POSIX_API = True in config.ini *

## run successfuly

```
[root@centos7 netshell01]# qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12   -kernel   o-optimize/hello.exe
qemu-system-arm: warning: nic cadence_gem.1 has no peer
*** LIBBSD NETSHELL 1 TEST ***
nexus0: <RTEMS Nexus device>
zy7_slcr0: <Zynq-7000 slcr block> on nexus0
arasan_sdhci0: <Zynq-7000 SDHCI> on nexus0
arasan_sdhci1: <Zynq-7000 SDHCI> on nexus0
cgem0: <Cadence CGEM Gigabit Ethernet Interface> on nexus0
miibus0: <MII bus> on cgem0
e1000phy0: <Marvell 88E1111 Gigabit PHY> PHY 0 on miibus0
e1000phy0:  none, 10baseT, 10baseT-FDX, 100baseTX, 100baseTX-FDX, 1000baseT-FDX, 1000baseT-FDX-master, auto
e1000phy1: <Marvell 88E1111 Gigabit PHY> PHY 23 on miibus0
e1000phy1:  none, 10baseT, 10baseT-FDX, 100baseTX, 100baseTX-FDX, 1000baseT-FDX, 1000baseT-FDX-master, auto
info: cgem0: Ethernet address: 0e:b0:ba:5e:ba:12
info: lo0: link state changed to UP
cgem0: cgem_mediachange: could not set ref clk0 to 25000000.
info: cgem0: link state changed to UP
add host 10.10.10.251: gateway cgem0
add net default: gateway 10.10.10.251

RTEMS Shell on /dev/console. Use 'help' to list commands.
RTSH [/] # ip a
ip: command not found
RTSH [/] # ping 10.10.10.251
PING 10.10.10.251 (10.10.10.251): 56 data bytes

--- 10.10.10.251 ping statistics ---
3 packets transmitted, 0 packets received, 100.0% packet loss
RTSH [/] # 
```


#  add hello command

*default-network-init.h*

```
 rtems_shell_add_cmd("hello","misc","Say hello RTEMS!",hello_command);
```

```
[root@centos7 netshell01]#  qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12   -kernel   o-optimize/hello.exe
qemu-system-arm: warning: nic cadence_gem.1 has no peer
*** LIBBSD NETSHELL 1 TEST ***
nexus0: <RTEMS Nexus device>
zy7_slcr0: <Zynq-7000 slcr block> on nexus0
arasan_sdhci0: <Zynq-7000 SDHCI> on nexus0
arasan_sdhci1: <Zynq-7000 SDHCI> on nexus0
cgem0: <Cadence CGEM Gigabit Ethernet Interface> on nexus0
miibus0: <MII bus> on cgem0
e1000phy0: <Marvell 88E1111 Gigabit PHY> PHY 0 on miibus0
e1000phy0:  none, 10baseT, 10baseT-FDX, 100baseTX, 100baseTX-FDX, 1000baseT-FDX, 1000baseT-FDX-master, auto
e1000phy1: <Marvell 88E1111 Gigabit PHY> PHY 23 on miibus0
e1000phy1:  none, 10baseT, 10baseT-FDX, 100baseTX, 100baseTX-FDX, 1000baseT-FDX, 1000baseT-FDX-master, auto
info: cgem0: Ethernet address: 0e:b0:ba:5e:ba:12
info: lo0: link state changed to UP
cgem0: cgem_mediachange: could not set ref clk0 to 25000000.
info: cgem0: link state changed to UP
add host 10.10.10.251: gateway cgem0
add net default: gateway 10.10.10.251

RTEMS Shell on /dev/console. Use 'help' to list commands.
RTSH [/] # hello
Hello RTEMS!
Create your own command here!
RTSH [/] # 
```

# rtems-tools
## rtems-tools version

```
[root@centos7 rtems-tools]# git branch
* (detached from origin/5)
  master
[root@centos7 rtems-tools]# 
```
## make
```
[root@centos7 rtems-tools]# ./waf configure --prefix=$HOME/development/rtems/compiler_arm/6
./waf build install

```
# reference
https://github.com/alanc98/rki/tree/5c531e9b7e229a7c4bce0890116835d672526964