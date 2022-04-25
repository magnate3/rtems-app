# make

```
   export PATH=$HOME/development/rtems/compiler/6/bin:$PATH
   export RTEMS_MAKEFILE_PATH=/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu
   
   
   arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -I ./inc -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/rki_whetstone_cmd.o rki_whetstone_cmd.c
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -I ./inc -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9      -c   -o o-optimize/target_shell_cmds.o target_shell_cmds.c
arm-rtems6-gcc --pipe  -Wall    -I/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib/include -I ./inc -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9     -B/root/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu/lib -qrtems -Wl,--gc-sections   -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -mtune=cortex-a9   -o o-optimize/hello.exe  o-optimize/rki_benchmarks.o o-optimize/rki_cfs_cmd.o o-optimize/rki_dhrystone_cmd.o o-optimize/rki_dl_cmds.o o-optimize/rki_filesys.o o-optimize/rki_hello_cmd.o o-optimize/rki_init.o o-optimize/rki_libbsd.o o-optimize/rki_net_svc.o o-optimize/rki_ramdisk.o o-optimize/rki_shell_cmds.o o-optimize/rki_start_cfs.o o-optimize/rki_task_cmd.o o-optimize/rki_whetstone_cmd.o o-optimize/target_shell_cmds.o   -lftpd -lbsd -lm    
arm-rtems6-nm -g -n o-optimize/hello.exe > o-optimize/hello.num
arm-rtems6-size o-optimize/hello.exe
   text    data     bss     dec     hex filename
2348692 1091872 263931316       267371880       fefc568 o-optimize/hello.exe
cp o-optimize/hello.exe o-optimize/hello.ralf
```

# run

```
[root@centos7 qemu_rki2]#  qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12   -kernel   o-optimize/hello.exe
qemu-system-arm: warning: nic cadence_gem.1 has no peer


RTEMS Kernel Image With LibBSD Booting


*** RTEMS Info ***
6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78


 BSP Ticks Per Second = 100
*** End RTEMS info ***

Setting up filesystems.
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
Found first Ethernet interface called cgem0
cgem0: cgem_mediachange: could not set ref clk0 to 25000000.
Starting the FTP Server.
Initializing Local Commands.
Adding Target specific commands
Running /shell-init.

shell: open input /shell-init failed: No such file or directory
info: lo0: link state changed to UP
info: cgem0: link state changed to UP
Starting shell....


RTEMS Shell on /dev/console. Use 'help' to list commands.
shell0 [/] # ipconfig
ipconfig: command not found
shell0 [/] # ifconfig
cgem0: flags=8843<UP,BROADCAST,RUNNING,SIMPLEX,MULTICAST> metric 0 mtu 1500
        options=80008<VLAN_MTU,LINKSTATE>
        ether 0e:b0:ba:5e:ba:12
        inet6 fe80::cb0:baff:fe5e:ba12%cgem0 prefixlen 64 scopeid 0x1
        nd6 options=21<PERFORMNUD,AUTO_LINKLOCAL>
        media: Ethernet autoselect (100baseTX <full-duplex>)
        status: active
lo0: flags=8049<UP,LOOPBACK,RUNNING,MULTICAST> metric 0 mtu 16384
        options=680003<RXCSUM,TXCSUM,LINKSTATE,RXCSUM_IPV6,TXCSUM_IPV6>
        inet 127.0.0.1 netmask 0xffffff00
        inet6 ::1 prefixlen 128
        inet6 fe80::1%lo0 prefixlen 64 scopeid 0x2
        nd6 options=21<PERFORMNUD,AUTO_LINKLOCAL>
        groups: lo
shell0 [/] #
```
 