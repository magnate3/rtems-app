# rtems-_app

```
/init.o init.c
init.c:20:10: fatal error: rtems/rtems_bsdnet.h: No such file or directory
   20 | #include <rtems/rtems_bsdnet.h>
      |          ^~~~~~~~~~~~~~~~~~~~~~
compilation terminated.
```



## posix enable

```
(1)./waf distclean  and ./waf bsp_defaults --rtems-bsps=riscv/rv64imafdc_medany   > config.ini

(2)sed -i \
-e "s|RTEMS_POSIX_API = False|RTEMS_POSIX_API = True|" \
-e "s|BUILD_TESTS = False|BUILD_TESTS = True|" \
config.ini

(3)./waf distclean  and ./waf bsp_defaults --rtems-bsps=riscv/rv64imafdc_medany   > config.ini
(4)./waf configure --prefix="$HOME/development/rtems_rv/compiler/6" --rtems-bsps=riscv/rv64imafdc_medany
(5)./waf 
(6)./waf install
```


## rtems-libbsd

```
[root@centos7 rtems-libbsd]# git branch
  master
* remotes/origin/5
  remotes/origin/6-freebsd-12
```

```
(1)git clone git://git.rtems.org/rtems-libbsd.git
(2)cd rtems-libbsd
(3)git submodule init
(4)git submodule update rtems_waf
(5)./waf configure -h
(6)./waf configure   --prefix=$HOME/development/rtems_rv/compiler/6  --rtems-bsps=riscv/rv64imafdc_medany  --buildset=buildset/default.ini
(7) ./waf
(8) ./waf install
```  

###

RTEMS_NETWORKING

```
Build failed
 -> task in 'debugger01.exe' failed with exit status 1: 
        {task 281473391112392: cprogram test_main.c.54.o -> debugger01.exe}
['/root/development/rtems_rv/compiler/6/bin/riscv-rtems6-gcc', '-march=rv64imafdc', '-mabi=lp64d', '-mcmodel=medany', '-I/root/development/rtems_rv/compiler/6/riscv-rtems6/rv64imafdc_medany/lib/include', '-MMD', '-B/root/development/rtems_rv/compiler/6/riscv-rtems6/rv64imafdc_medany/lib', '-qrtems', '-Wl,--gc-sections', 'testsuite/debugger01/test_main.c.54.o', '-o/root/development/rtems_rv/rtems-libbsd/build/riscv-rtems6-rv64imafdc_medany-default/debugger01.exe', '-Wl,-Bstatic', '-L.', '-lbsd', '-Wl,-Bdynamic', '-ldebugger', '-lbsd', '-lm', '-lz', '-lrtemstest']
```

```
RTEMS_NETWORKING = False
```



 
