# init
![image](https://github.com/magnate3/rtems-app/blob/main/pic/rtems-init.png)
# SYSINIT
![image](https://github.com/magnate3/rtems-app/blob/main/pic/rtems-sysyinit.png)

```
RTEMS_SYSINIT_ITEM(_RTEMS_tasks_Initialize_user_task, RTEMS_SYSINIT_CLASSIC_USER_TASKS, RTEMS_SYSINIT_ORDER_MIDDLE);
```

```
 src/rtems/cpukit/include/rtems/sysinit.h 
#define _RTEMS_SYSINIT_INDEX_ITEM(handler, index)                               \
    enum { _Sysinit_##handler = index };                                        \
    RTEMS_LINKER_ROSET_ITEM_ORDERED(                                            \
        _Sysinit,                                                               \
        rtems_sysinit_item,                                                     \
        handler,                                                                \
        index                                                                   \
    ) = { handler }

#define _RTEMS_SYSINIT_ITEM(handler, module, order)                             _RTEMS_SYSINIT_INDEX_ITEM(handler, 0x##module##order)
#define RTEMS_SYSINIT_ITEM(handler, module, order)                              _RTEMS_SYSINIT_ITEM(handler, module, order)
```

# porting a driver from FreeBSD to rtems-libbsd
```
#define RTEMS_BSD_DEFINE_NEXUS_DEVICE(name, unit, resource_count, resources) \
    extern struct sysinit SYSINIT_ENTRY_NAME(name##_nexusmodule); \
    RTEMS_BSD_DEFINE_SET_ITEM(nexus, name##unit, rtems_bsd_device) = \
        { #name, unit, (resource_count), (resources), \
            &SYSINIT_ENTRY_NAME(name##_nexusmodule) }
```
 
```
#define RTEMS_BSD_DEFINE_SET_ITEM(set, sym, type)                       \
        static RTEMS_BSD_SET_ALIGN( type ) type                         \
        const __set_##set##_sym_##sym                                   \
        __section(".rtemsroset.bsd." __STRING(set) ".content.1") __used
```
