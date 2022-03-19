# make

```
[root@centos7 event]#  export PATH=$HOME/development/rtems/compiler/6/bin:$PATH
[root@centos7 event]#  export RTEMS_MAKEFILE_PATH=/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu
[root@centos7 event]# make clean
rm -f a.out core mon.out gmon.out
rm -f -r 
rm -f -r  a.out *.o *.BAK Depends-o-optimize.tmp
rm -f -r o-optimize o-debug
[root@centos7 event]# ls
Makefile  Readme  test.c  wscript
[root@centos7 event]# 
```

# run

```
[root@centos7 event]# qemu-system-aarch64 -no-reboot -nographic -serial mon:stdio  -machine virt,gic-version=3 -cpu cortex-a53 -m 4096 -kernel o-optimize/hello.exe
Main task is now started... 
Sending event to secondary task soon...
Waiting Task is now started... 
Waiting for event to be received...
Event to secondary task has been sent... 
Quitting current task... 
Received Event Successfully...Quitting current task... 
QEMU: Terminated
```


#  rtems_event_send

```
		rtems_event_send(
		waitingTask,
		RTEMS_EVENT_1
		);
```

*waitingTask is the id of receiver*