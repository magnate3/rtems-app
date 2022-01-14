
## Requirement
- qemu

```
qemu-system-riscv64 -version
QEMU emulator version 6.1.0
Copyright (c) 2003-2021 Fabrice Bellard and the QEMU Project developers
```


## my host 

```
uname -a
Linux centos7 4.14.0-115.el7a.0.1.aarch64 #1 SMP Sun Nov 25 20:54:21 UTC 2018 aarch64 aarch64 aarch64 GNU/Linux
```

## rtems verion

**git checkout -b  remotes/origin/5**

## Debug
``` 
[root@centos7 rtems_rv]# ls
compiler  kernel  profile  rtems-examples  rtems-source-builder
[root@centos7 rtems_rv]# cd ./kernel/rtems/
[root@centos7 rtems]# ls
aclocal.m4      config.ini.bak  INSTALL               LICENSE.JFFS2   Makefile.in     testsuites
autom4te.cache  configure       LICENSE               LICENSE.NET     Makefile.maint  waf
bsps            cpukit          LICENSE.BSD-2-Clause  LICENSE.RPCXDR  README          wscript
build           Doxyfile        LICENSE.BSD-3-Clause  long_gcc.py     rtems-bsps      yaml
c               gccdeps.py      LICENSE.CC-BY-SA-4.0  MAINTAINERS     rtemslogo.png
config.ini      gccdeps.pyc     LICENSE.GPL-2.0       make            spec
```



## though rtems-source-builder to build rtems-gcc objump gdb

```
[root@centos7 rtems]#  ../source-builder/sb-set-builder --list-bsets | grep riscv
    6/rtems-riscv.bset
    7/rtems-riscv.bset
[root@centos7 rtems]# ../source-builder/sb-set-builder --prefix=$HOME/development/rtems_rv/compiler/6 6/rtems-riscv
```

```
ls $HOME/development/rtems_rv/compiler/6
bin  include  lib  libexec  make  riscv-rtems6  share
```


## build kernel
  ./waf  bsp_list
```
[root@centos7 rtems]# ./waf bsp_list | grep riscv
riscv/frdme310arty
riscv/griscv
riscv/grv32i
riscv/grv32im
riscv/grv32imac
riscv/grv32imafdc
riscv/rv32i
riscv/rv32iac
riscv/rv32im
riscv/rv32imac
riscv/rv32imafc
riscv/rv32imafd
riscv/rv32imafdc
riscv/rv64imac
riscv/rv64imac_medany
riscv/rv64imafd
riscv/rv64imafd_medany
riscv/rv64imafdc
riscv/rv64imafdc_medany
```

```
bsps   c           cpukit    gccdeps.py   INSTALL  LICENSE.BSD-2-Clause  LICENSE.CC-BY-SA-4.0  LICENSE.JFFS2  LICENSE.RPCXDR  MAINTAINERS  Makefile.maint  rtems-bsps     spec        waf      yaml
build  config.ini  Doxyfile  gccdeps.pyc  LICENSE  LICENSE.BSD-3-Clause  LICENSE.GPL-2.0       LICENSE.NET    long_gcc.py     make         README          rtemslogo.png  testsuites  wscript
```


```
(1)./waf distclean  and ./waf bsp_defaults --rtems-bsps=riscv/rv64imafdc_medany   > config.ini
(2)./waf configure --prefix="$HOME/development/rtems_rv/compiler/6" --rtems-bsps=riscv/rv64imafdc_medany
(3)./waf 
(4)./waf install
```


##   hello_world_c

```
 export RTEMS_MAKEFILE_PATH=$HOME/development/rtems_rv/compiler/6/riscv-rtems6/rv64imafdc_medany
 export PATH=$HOME/development/rtems_rv/compiler/6/bin:$PATH
```

```
root@ubuntu:/home/ubuntu# uname -a
Linux ubuntu 4.15.0-76-generic #86-Ubuntu SMP Fri Jan 17 17:25:58 UTC 2020 aarch64 aarch64 aarch64 GNU/Linux
root@ubuntu:/home/ubuntu# qemu-system-riscv64 -M virt -kernel hello.exe -bios none -serial stdio -display none


*** HELLO WORLD TEST ***
Hello World
*** END OF HELLO WORLD TEST ***

[ RTEMS shutdown ]
RTEMS version: 6.0.0.822ebb4cae2bb8bc9fe55915bd4acc4942fcd8ce
RTEMS tools: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
executing thread ID: 0x08a010001
executing thread name: UI1 
```


