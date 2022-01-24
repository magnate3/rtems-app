

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

### set in outer host

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