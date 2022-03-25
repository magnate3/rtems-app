# make

```
[root@centos7 event]#  export PATH=$HOME/development/rtems/compiler/6/bin:$PATH
[root@centos7 event]#  export RTEMS_MAKEFILE_PATH=/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu
[root@centos7 semaphore]# make clean
rm -f a.out core mon.out gmon.out
rm -f -r 
rm -f -r  a.out *.o *.BAK Depends-o-optimize.tmp
rm -f -r o-optimize o-debug
[root@centos7 semaphore]# make
test -d o-optimize || mkdir o-optimize
aarch64-rtems6-gcc --pipe  -Wall  -O2 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/include -mcpu=cortex-a53      -c   -o o-optimize/test.o test.c
test.c: In function 'Init':
test.c:103:2: warning: implicit declaration of function 'createSemaphore' [-Wimplicit-function-declaration]
  103 |  createSemaphore();
      |  ^~~~~~~~~~~~~~~
test.c: At top level:
test.c:110:6: warning: conflicting types for 'createSemaphore'
  110 | void createSemaphore(void){
      |      ^~~~~~~~~~~~~~~
test.c:103:2: note: previous implicit declaration of 'createSemaphore' was here
  103 |  createSemaphore();
      |  ^~~~~~~~~~~~~~~
aarch64-rtems6-gcc --pipe  -Wall  -O2 -g -fdata-sections -ffunction-sections  -I/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib/include -mcpu=cortex-a53     -B/root/development/rtems/compiler/6/aarch64-rtems6/a53_lp64_qemu/lib -qrtems -Wl,--gc-sections   -mcpu=cortex-a53   -o o-optimize/hello.exe  o-optimize/test.o       
aarch64-rtems6-nm -g -n o-optimize/hello.exe > o-optimize/hello.num
aarch64-rtems6-size o-optimize/hello.exe
   text    data     bss     dec     hex filename
 114392    2392 134066584       134183368       7ff79c8 o-optimize/hello.exe
cp o-optimize/hello.exe o-optimize/hello.ralf
[root@centos7 semaphore]# 
```

# run


```
 [root@centos7 semaphore]# qemu-system-aarch64 -no-reboot -nographic -serial mon:stdio  -machine virt,gic-version=3 -cpu cortex-a53 -m 4096 -kernel o-optimize/hello.exe
Creation of Semaphore failed...

*** EXIT STATUS NOT ZERO ***
exit source: 5 (RTEMS_FATAL_SOURCE_EXIT)
exit code: 1 (0x00000001)
RTEMS version: 6.0.0.671f126a3a8e6ce5da87aa75c7205fb764e95c78
RTEMS tools: 10.3.1 20210409 (RTEMS 6, RSB 889cf95db0122bd1a6b21598569620c40ff2069d, Newlib eb03ac1)
executing thread ID: 0x08a010001
executing thread name: EXAM
```


#  rtems_semaphore_create
```
rtems_status_code rtems_semaphore_create(
  rtems_name           name,
  uint32_t             count,
  rtems_attribute      attribute_set,
  rtems_task_priority  priority_ceiling,
  rtems_id            *id
)
```
cpukit/rtems/src/semcreate.c