
# qemu

```
./configure --target-list=arm-softmmu --disable-git-update
make
make install

qemu-system-arm  --version
QEMU emulator version 4.2.0
Copyright (c) 2003-2019 Fabrice Bellard and the QEMU Project developers
[root@centos7 qemu-4.2.0]# 

qemu-system-arm  -M \? | grep xilinx-zynq-a9
xilinx-zynq-a9       Xilinx Zynq Platform Baseboard for Cortex-A9
```

# source-builder
```
[root@centos7 rtems]# ../source-builder/sb-set-builder --list-bsets | grep arm
    6/rtems-arm.bset
    7/rtems-arm.bset
```

```
../source-builder/sb-set-builder          --log=build-log.txt          --prefix=$HOME/development/rtems/compiler_arm/6  6/rtems-arm
```

## rtems kernel  

## rtems kernel version

```
[root@centos7 rtems]# pwd
/root/development/rtems/kernel2/rtems
You have new mail in /var/spool/mail/root
[root@centos7 rtems]# git branch --all
  master
* remotes/origin/5
  remotes/origin/4.10
  remotes/origin/4.11
  remotes/origin/4.8
  remotes/origin/4.9
  remotes/origin/5
  remotes/origin/HEAD -> origin/master
  remotes/origin/master
```

## build kernel 

```
./waf  bsp_list | grep arm

 (1)./waf bsp_defaults --rtems-bsps=arm/xilinx_zynq_a9_qemu   > config.ini
 RTEMS_POSIX_API = True in config.ini
 (2)./waf configure --prefix=$HOME/development/rtems/compiler_arm/6
 (3)./waf 
 (4)./waf install
```

# export
export PATH=$HOME/development/rtems/compiler_arm/6/bin:$PATH
export RTEMS_MAKEFILE_PATH=$HOME/development/rtems/compiler_arm/6/arm-rtems6/xilinx_zynq_a9_qemu

#  rtems-libbsd

## rtems-libbsd version

```
[root@centos7 rtems-libbsd-a64]# git branch
  master
* remotes/origin/5
  remotes/origin/6-freebsd-12
[root@centos7 rtems-libbsd-a64]# pwd
/root/development/rtems_rv/rtems-libbsd-a64
[root@centos7 rtems-libbsd-a64]# 


```

## build rtems-libbsd

./waf configure --prefix=$HOME/development/rtems/compiler_arm/6 --rtems-bsps=arm/xilinx_zynq_a9_qemu   --buildset=buildset/default.ini


# run



## network config

```
[root@centos7 rtems-libbsd-a64]#  tunctl -p -t qtap -u $(whoami)
Set 'qtap' persistent and owned by uid 0
[root@centos7 rtems-libbsd-a64]# ip link set dev qtap up
[root@centos7 rtems-libbsd-a64]#  ip addr add 169.254.1.1/16 dev qtap
RTNETLINK answers: File exists
[root@centos7 rtems-libbsd-a64]# ip a sh qtap
21: qtap: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc pfifo_fast state DOWN group default qlen 1000
    link/ether 36:76:9c:1c:e7:0f brd ff:ff:ff:ff:ff:ff
    inet 169.254.1.1/16 scope global qtap
       valid_lft forever preferred_lft forever
    inet6 fe80::3476:9cff:fe1c:e70f/64 scope link 
       valid_lft forever preferred_lft forever
[root@centos7 rtems-libbsd-a64]#
```



## run

```
[root@centos7 rtems-libbsd-a64]# qemu-system-arm -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12   -kernel build/arm-rtems6-xilinx_zynq_a9_qemu-default/media01.exe
qemu-system-arm: warning: nic cadence_gem.1 has no peer


*** BEGIN OF TEST LIBBSD MEDIA 1 ***
*** TEST VERSION: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
*** TEST STATE: USER_INPUT
*** TEST BUILD: RTEMS_POSIX_API
*** TEST TOOLS: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
nexus0: <RTEMS Nexus device>
cgem0: <Cadence CGEM Gigabit Ethernet Interface> on nexus0
miibus0: <MII bus> on cgem0
e1000phy0: <Marvell 88E1111 Gigabit PHY> PHY 0 on miibus0
e1000phy0:  none, 10baseT, 10baseT-FDX, 100baseTX, 100baseTX-FDX, 1000baseT-FDX, 1000baseT-FDX-master, auto
e1000phy1: <Marvell 88E1111 Gigabit PHY> PHY 23 on miibus0
e1000phy1:  none, 10baseT, 10baseT-FDX, 100baseTX, 100baseTX-FDX, 1000baseT-FDX, 1000baseT-FDX-master, auto
info: cgem0: Ethernet address: 0e:b0:ba:5e:ba:12
arasan_sdhci1: <Zynq-7000 SDHCI> on nexus0
arasan_sdhci0: <Zynq-7000 SDHCI> on nexus0
zy7_slcr0: <Zynq-7000 slcr block> on nexus0
info: lo0: link state changed to UP
cgem0: cgem_mediachange: could not set ref clk0 to 25000000.
info: cgem0: link state changed to UP
info: ftpd: FTP daemon started (4 sessions max)
info: telnetd: started successfully on port 23

```

```
SHLL [/] # 
SHLL [/] # ifconfig
cgem0: flags=8843<UP,BROADCAST,RUNNING,SIMPLEX,MULTICAST> metric 0 mtu 1500
        options=80008<VLAN_MTU,LINKSTATE>
        ether 0e:b0:ba:5e:ba:12
        inet6 fe80::cb0:baff:fe5e:ba12%cgem0 prefixlen 64 scopeid 0x1
        inet 169.254.202.37 netmask 0xffff0000 broadcast 169.254.255.255
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
```

## route

```
info: cgem0: using IPv4LL address 169.254.202.37
debug: cgem0: adding IP address 169.254.202.37/16
info: cgem0: adding host route to 169.254.202.37 via 127.0.0.1
err: cgem0: ipv4_addroute: File exists
info: cgem0: adding route to 169.254.0.0/16
err: cgem0: ipv4_addroute: File exists
debug: cgem0: writing lease `/var/db/dhcpcd-cgem0.lease'
debug: cgem0: sending ARP announce (1 of 2), next in 2.0 seconds
debug: cgem0: sending ARP announce (2 of 2)
```

### settings in outer host

(1) qemu
 
![image](https://github.com/magnate3/rtems-_app/blob/main/pic/gem.png)

(2) host             
![image](https://github.com/magnate3/rtems-_app/blob/main/pic/network.png)

```
[root@centos7 rtems]# telnet  169.254.202.37
Trying 169.254.202.37...
^C
[root@centos7 rtems]# ping 169.254.202.37
PING 169.254.202.37 (169.254.202.37) 56(84) bytes of data.
^C
--- 169.254.202.37 ping statistics ---
1 packets transmitted, 0 received, 100% packet loss, time 0ms

[root@centos7 rtems]# route add -host 169.254.202.37 dev qtap
[root@centos7 rtems]# ip sh qtap
Object "sh" is unknown, try "ip help".
[root@centos7 rtems]# ip a sh qtap
21: qtap: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 36:76:9c:1c:e7:0f brd ff:ff:ff:ff:ff:ff
    inet6 fe80::3476:9cff:fe1c:e70f/64 scope link 
       valid_lft forever preferred_lft forever
[root@centos7 rtems]# ip addr add 169.254.1.1/16 dev qtap
[root@centos7 rtems]# ping 169.254.202.37
PING 169.254.202.37 (169.254.202.37) 56(84) bytes of data.
64 bytes from 169.254.202.37: icmp_seq=1 ttl=64 time=5.63 ms
64 bytes from 169.254.202.37: icmp_seq=2 ttl=64 time=0.185 ms
64 bytes from 169.254.202.37: icmp_seq=3 ttl=64 time=0.152 ms
64 bytes from 169.254.202.37: icmp_seq=4 ttl=64 time=0.143 ms
^C
--- 169.254.202.37 ping statistics ---
4 packets transmitted, 4 received, 0% packet loss, time 3074ms
rtt min/avg/max/mdev = 0.143/1.528/5.632/2.369 ms
[root@centos7 rtems]# telnet  169.254.202.37
Trying 169.254.202.37...
Connected to 169.254.202.37.
Escape character is '^]'.

RTEMS Shell on /dev/pty4. Use 'help' to list commands.
TLNT [/] # q
q: command not found
TLNT [/] # exit
Shell exiting
Connection closed by foreign host.
[root@centos7 rtems]# 
```

# debug

```
export PATH=$HOME/development/rtems/compiler_arm/6/bin:$PATH
```

```
 qemu-system-arm  -serial null -serial mon:stdio -nographic   -M xilinx-zynq-a9 -m 256M   -net tap,ifname=qtap,script=no,downscript=no   -net nic,model=cadence_gem,macaddr=0e:b0:ba:5e:ba:12   -kernel build/arm-rtems6-xilinx_zynq_a9_qemu-default/media01.exe -s -S
 
 arm-rtems6-gdb  build/arm-rtems6-xilinx_zynq_a9_qemu-default/media01.exe
```

```
(gdb) step
_bsd_device_add_child (dev=dev@entry=0x50d898, name=0x228580 "cgem", unit=0) at ../../freebsd/sys/kern/subr_bus.c:1924
1924            return (device_add_child_ordered(dev, 0, name, unit));
(gdb) bt
#0  _bsd_device_add_child (dev=dev@entry=0x50d898, name=0x228580 "cgem", unit=0) at ../../freebsd/sys/kern/subr_bus.c:1924
#1  0x0017c12e in nexus_probe (dev=0x50d898) at ../../rtemsbsd/rtems/rtems-kernel-nexus.c:153
#2  0x001108a0 in DEVICE_PROBE (dev=0x50d898) at ../../rtemsbsd/include/rtems/bsd/local/device_if.h:115
#3  _bsd_device_probe_child (dev=0x50b368, child=child@entry=0x50d898) at ../../freebsd/sys/kern/subr_bus.c:2190
#4  0x00110ac8 in _bsd_device_probe (dev=dev@entry=0x50d898) at ../../freebsd/sys/kern/subr_bus.c:2922
#5  0x00110c7e in _bsd_device_probe_and_attach (dev=0x50d898) at ../../freebsd/sys/kern/subr_bus.c:2946
#6  _bsd_bus_generic_new_pass (dev=0x50b368) at ../../freebsd/sys/kern/subr_bus.c:4187
#7  0x0010f95c in BUS_NEW_PASS (_dev=0x50b368) at ../../rtemsbsd/include/rtems/bsd/local/bus_if.h:1046
#8  _bsd_bus_set_pass (pass=2147483647) at ../../freebsd/sys/kern/subr_bus.c:994
#9  0x00195ae4 in _bsd_mi_startup () at ../../freebsd/sys/kern/init_main.c:331
#10 0x0017b396 in rtems_bsd_initialize () at ../../rtemsbsd/rtems/rtems-kernel-init.c:235
#11 0x001047ca in Init (arg=<optimized out>) at ../../testsuite/include/rtems/bsd/test/default-network-init.h:239
#12 0x001f95b4 in _Thread_Handler () at ../../../cpukit/score/src/threadhandler.c:145
#13 0x001fa96a in _Thread_Start_multitasking () at ../../../cpukit/score/src/threadstartmultitasking.c:68
#14 0x00000000 in ?? ()
Backtrace stopped: previous frame identical to this frame (corrupt stack?)
(gdb) list
1919     * @returns             the new device
1920     */
1921    device_t
1922    device_add_child(device_t dev, const char *name, int unit)
1923    {
1924            return (device_add_child_ordered(dev, 0, name, unit));
1925    }
1926
1927    /**
1928     * @brief Create a new device
(gdb) 
```

## device_method_t

```
static device_method_t cgem_methods[] = {
	/* Device interface */
	DEVMETHOD(device_probe,		cgem_probe),
	DEVMETHOD(device_attach,	cgem_attach),
	DEVMETHOD(device_detach,	cgem_detach),

	/* Bus interface */
	DEVMETHOD(bus_child_detached,	cgem_child_detached),

	/* MII interface */
	DEVMETHOD(miibus_readreg,	cgem_miibus_readreg),
	DEVMETHOD(miibus_writereg,	cgem_miibus_writereg),
	DEVMETHOD(miibus_statchg,	cgem_miibus_statchg),
	DEVMETHOD(miibus_linkchg,	cgem_miibus_linkchg),

	DEVMETHOD_END
};s

static driver_t cgem_driver = {
	"cgem",
	cgem_methods,
	sizeof(struct cgem_softc),
};

#ifndef __rtems__
DRIVER_MODULE(cgem, simplebus, cgem_driver, cgem_devclass, NULL, NULL);
#else /* __rtems__ */
DRIVER_MODULE(cgem, nexus, cgem_driver, cgem_devclass, NULL, NULL);
#endif /* __rtems__ */
DRIVER_MODULE(miibus, cgem, miibus_driver, miibus_devclass, NULL, NULL);
MODULE_DEPEND(cgem, miibus, 1, 1, 1);
MODULE_DEPEND(cgem, ether, 1, 1, 1);

```
[root@centos7 rtems-libbsd-a64]# ls freebsd/sys/dev/
bce  bge      dc   e1000  extres  ffec  gpio  led  mmc   ofw  re  rtwn   smc   usb
bfe  cadence  dwc  evdev  fdt     fxp   kbd   mii  nvme  pci  rl  sdhci  tsec
```

```
##  cgem_probe

```
(gdb) bt
#0  cgem_probe (dev=0x50da10) at ../../freebsd/sys/dev/cadence/if_cgem.c:1958
#1  0x001108a0 in DEVICE_PROBE (dev=0x50da10) at ../../rtemsbsd/include/rtems/bsd/local/device_if.h:115
#2  _bsd_device_probe_child (dev=0x50d898, child=child@entry=0x50da10) at ../../freebsd/sys/kern/subr_bus.c:2190
#3  0x00110ac8 in _bsd_device_probe (dev=dev@entry=0x50da10) at ../../freebsd/sys/kern/subr_bus.c:2922
#4  0x00110c7e in _bsd_device_probe_and_attach (dev=0x50da10) at ../../freebsd/sys/kern/subr_bus.c:2946
#5  _bsd_bus_generic_new_pass (dev=0x50d898) at ../../freebsd/sys/kern/subr_bus.c:4187
#6  0x00110c6e in BUS_NEW_PASS (_dev=0x50d898) at ../../rtemsbsd/include/rtems/bsd/local/bus_if.h:1046
#7  _bsd_bus_generic_new_pass (dev=0x50b368) at ../../freebsd/sys/kern/subr_bus.c:4185
#8  0x0010f95c in BUS_NEW_PASS (_dev=0x50b368) at ../../rtemsbsd/include/rtems/bsd/local/bus_if.h:1046
#9  _bsd_bus_set_pass (pass=2147483647) at ../../freebsd/sys/kern/subr_bus.c:994
#10 0x00195ae4 in _bsd_mi_startup () at ../../freebsd/sys/kern/init_main.c:331
#11 0x0017b396 in rtems_bsd_initialize () at ../../rtemsbsd/rtems/rtems-kernel-init.c:235
#12 0x001047ca in Init (arg=<optimized out>) at ../../testsuite/include/rtems/bsd/test/default-network-init.h:239
#13 0x001f95b4 in _Thread_Handler () at ../../../cpukit/score/src/threadhandler.c:145
#14 0x001fa96a in _Thread_Start_multitasking () at ../../../cpukit/score/src/threadstartmultitasking.c:68
#15 0x00000000 in ?? ()
Backtrace stopped: previous frame identical to this frame (corrupt stack?)
(gdb) 
```

##
```
(gdb) c
Continuing.

Breakpoint 3, cgem_attach (dev=0x50da10) at ../../freebsd/sys/dev/cadence/if_cgem.c:1984
1984            struct cgem_softc *sc = device_get_softc(dev);
(gdb) bt
#0  cgem_attach (dev=0x50da10) at ../../freebsd/sys/dev/cadence/if_cgem.c:1984
#1  0x00110358 in DEVICE_ATTACH (dev=0x50da10) at ../../rtemsbsd/include/rtems/bsd/local/device_if.h:195
#2  _bsd_device_attach (dev=dev@entry=0x50da10) at ../../freebsd/sys/kern/subr_bus.c:2998
#3  0x00110c88 in _bsd_device_probe_and_attach (dev=0x50da10) at ../../freebsd/sys/kern/subr_bus.c:2953
#4  _bsd_bus_generic_new_pass (dev=0x50d898) at ../../freebsd/sys/kern/subr_bus.c:4187
#5  0x00110c6e in BUS_NEW_PASS (_dev=0x50d898) at ../../rtemsbsd/include/rtems/bsd/local/bus_if.h:1046
#6  _bsd_bus_generic_new_pass (dev=0x50b368) at ../../freebsd/sys/kern/subr_bus.c:4185
#7  0x0010f95c in BUS_NEW_PASS (_dev=0x50b368) at ../../rtemsbsd/include/rtems/bsd/local/bus_if.h:1046
#8  _bsd_bus_set_pass (pass=2147483647) at ../../freebsd/sys/kern/subr_bus.c:994
#9  0x00195ae4 in _bsd_mi_startup () at ../../freebsd/sys/kern/init_main.c:331
#10 0x0017b396 in rtems_bsd_initialize () at ../../rtemsbsd/rtems/rtems-kernel-init.c:235
#11 0x001047ca in Init (arg=<optimized out>) at ../../testsuite/include/rtems/bsd/test/default-network-init.h:239
#12 0x001f95b4 in _Thread_Handler () at ../../../cpukit/score/src/threadhandler.c:145
#13 0x001fa96a in _Thread_Start_multitasking () at ../../../cpukit/score/src/threadstartmultitasking.c:68
#14 0x00000000 in ?? ()
Backtrace stopped: previous frame identical to this frame (corrupt stack?)
(gdb) 
```

##  cgem_recv 

```
Breakpoint 1, cgem_recv (sc=0x50e500) at ../../freebsd/sys/dev/cadence/if_cgem.c:702
702             if_t ifp = sc->ifp;
(gdb) bt
#0  cgem_recv (sc=0x50e500) at ../../freebsd/sys/dev/cadence/if_cgem.c:702
#1  cgem_intr (arg=0x50e500) at ../../freebsd/sys/dev/cadence/if_cgem.c:1185
#2  0x001e9ff8 in bsp_interrupt_server_task (arg=4676060) at ../../../bsps/shared/irq/irq-server.c:363
#3  0x001f95b4 in _Thread_Handler () at ../../../cpukit/score/src/threadhandler.c:145
#4  0x001f945e in _Thread_Do_dispatch (cpu_self=<optimized out>, level=<optimized out>) at ../../../cpukit/score/src/threaddispatch.c:309
#5  0x00000000 in ?? ()
Backtrace stopped: previous frame identical to this frame (corrupt stack?)
(gdb) 
```

## cgem_int-->rtems_interrupt_server_handler_install

```
(gdb) c
Continuing.

Breakpoint 2, rtems_interrupt_server_handler_install (server_index=server_index@entry=0, vector=vector@entry=79, info=0x50db10 "arasan_sdhci1", options=options@entry=0, handler=handler@entry=0x17d22d <arasan_sdhci_intr>, arg=arg@entry=0x513568)
    at ../../../bsps/shared/irq/irq-server.c:385
385       s = bsp_interrupt_server_get_context(server_index, &sc);
(gdb) bt
#0  rtems_interrupt_server_handler_install (server_index=server_index@entry=0, vector=vector@entry=79, info=0x50db10 "arasan_sdhci1", options=options@entry=0, handler=handler@entry=0x17d22d <arasan_sdhci_intr>, arg=arg@entry=0x513568)
    at ../../../bsps/shared/irq/irq-server.c:385
#1  0x0017bf60 in nexus_setup_intr (dev=<optimized out>, child=<optimized out>, res=0x513c48, flags=<optimized out>, filt=0x0, intr=0x17d22d <arasan_sdhci_intr>, arg=0x513568, cookiep=0x513574) at ../../rtemsbsd/rtems/rtems-kernel-nexus.c:335
#2  0x00110102 in BUS_SETUP_INTR (_cookiep=0x513574, _arg=0x513568, _intr=0x17d22d <arasan_sdhci_intr>, _filter=0x0, _flags=514, _irq=0x513c48, _child=0x50daa8, _dev=0x50d898) at ../../rtemsbsd/include/rtems/bsd/local/bus_if.h:553
#3  _bsd_bus_setup_intr (dev=dev@entry=0x50daa8, r=0x513c48, flags=flags@entry=514, filter=filter@entry=0x0, handler=handler@entry=0x17d22d <arasan_sdhci_intr>, arg=arg@entry=0x513568, cookiep=cookiep@entry=0x513574)
    at ../../freebsd/sys/kern/subr_bus.c:4799
#4  0x0017d2d0 in arasan_sdhci_attach (dev=0x50daa8) at ../../rtemsbsd/sys/dev/sdhci/arasan_sdhci.c:258
#5  0x00110358 in DEVICE_ATTACH (dev=0x50daa8) at ../../rtemsbsd/include/rtems/bsd/local/device_if.h:195
#6  _bsd_device_attach (dev=dev@entry=0x50daa8) at ../../freebsd/sys/kern/subr_bus.c:2998
#7  0x00110c88 in _bsd_device_probe_and_attach (dev=0x50daa8) at ../../freebsd/sys/kern/subr_bus.c:2953
#8  _bsd_bus_generic_new_pass (dev=0x50d898) at ../../freebsd/sys/kern/subr_bus.c:4187
#9  0x00110c6e in BUS_NEW_PASS (_dev=0x50d898) at ../../rtemsbsd/include/rtems/bsd/local/bus_if.h:1046
#10 _bsd_bus_generic_new_pass (dev=0x50b368) at ../../freebsd/sys/kern/subr_bus.c:4185
#11 0x0010f95c in BUS_NEW_PASS (_dev=0x50b368) at ../../rtemsbsd/include/rtems/bsd/local/bus_if.h:1046
#12 _bsd_bus_set_pass (pass=2147483647) at ../../freebsd/sys/kern/subr_bus.c:994
#13 0x00195ae4 in _bsd_mi_startup () at ../../freebsd/sys/kern/init_main.c:331
#14 0x0017b396 in rtems_bsd_initialize () at ../../rtemsbsd/rtems/rtems-kernel-init.c:235
#15 0x001047ca in Init (arg=<optimized out>) at ../../testsuite/include/rtems/bsd/test/default-network-init.h:239
#16 0x001f95b4 in _Thread_Handler () at ../../../cpukit/score/src/threadhandler.c:145
#17 0x001fa96a in _Thread_Start_multitasking () at ../../../cpukit/score/src/threadstartmultitasking.c:68
#18 0x00000000 in ?? ()
Backtrace stopped: previous frame identical to this frame (corrupt stack?)
```


##  rtems_interrupt_server_request_initialize

```
(gdb) target remote:1234
Remote debugging using :1234
bsp_start_vector_table_end () at ../../../bsps/arm/shared/start/start.S:192
192     ../../../bsps/arm/shared/start/start.S: No such file or directory.
(gdb) c
Continuing.

Breakpoint 1, rtems_interrupt_server_request_initialize (server_index=0, 
    request=0x4140a8 <_Linker_set__Per_CPU_Data_epoch+40>, handler=0x17aca5 <epoch_call_handler>, 
    arg=0x414080 <_Linker_set__Per_CPU_Data_epoch>) at ../../../bsps/shared/irq/irq-server.c:861
861     ../../../bsps/shared/irq/irq-server.c: No such file or directory.
(gdb) bt
#0  rtems_interrupt_server_request_initialize (server_index=0, 
    request=0x4140a8 <_Linker_set__Per_CPU_Data_epoch+40>, handler=0x17aca5 <epoch_call_handler>, 
    arg=0x414080 <_Linker_set__Per_CPU_Data_epoch>) at ../../../bsps/shared/irq/irq-server.c:861
#1  0x00195ae4 in _bsd_mi_startup () at ../../freebsd/sys/kern/init_main.c:331
#2  0x0017b396 in rtems_bsd_initialize () at ../../rtemsbsd/rtems/rtems-kernel-init.c:235
#3  0x001047ca in Init (arg=<optimized out>) at ../../testsuite/include/rtems/bsd/test/default-network-init.h:239
#4  0x001f95b4 in _Thread_Handler () at ../../../cpukit/score/src/threadhandler.c:145
#5  0x001fa96a in _Thread_Start_multitasking () at ../../../cpukit/score/src/threadstartmultitasking.c:68
#6  0x00000000 in ?? ()
Backtrace stopped: previous frame identical to this frame (corrupt stack?)
(gdb) 
```

##  bsp_interrupt_server_install_helper
```
(gdb) c
Continuing.

Breakpoint 1, bsp_interrupt_server_install_helper (arg=0x4834c4)
    at ../../../bsps/shared/irq/irq-server.c:154
154     ../../../bsps/shared/irq/irq-server.c: No such file or directory.
(gdb) bt
#0  bsp_interrupt_server_install_helper (arg=0x4834c4)
    at ../../../bsps/shared/irq/irq-server.c:154
#1  0x001e9ff8 in bsp_interrupt_server_task (arg=4676060)
    at ../../../bsps/shared/irq/irq-server.c:363
#2  0x001f95b4 in _Thread_Handler () at ../../../cpukit/score/src/threadhandler.c:145
#3  0x001f945e in _Thread_Do_dispatch (cpu_self=<optimized out>, level=<optimized out>)
    at ../../../cpukit/score/src/threaddispatch.c:309
#4  0x00000000 in ?? ()
Backtrace stopped: previous frame identical to this frame (corrupt stack?)
(gdb) 
```