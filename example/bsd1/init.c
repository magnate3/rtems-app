#include <rtems.h>

#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_LIBBLOCK
#define CONFIGURE_APPLICATION_NEEDS_STUB_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_ZERO_DRIVER


#define CONFIGURE_UNLIMITED_OBJECTS
#define CONFIGURE_UNIFIED_WORK_AREAS
#define CONFIGURE_UNLIMITED_ALLOCATION_SIZE 5
#define CONFIGURE_MAXIMUM_USER_EXTENSIONS 5

//#define CONFIGURE_FILESYSTEM_ALL
#define CONFIGURE_USE_IMFS_AS_BASE_FILESYSTEM

#define CONFIGURE_MAXIMUM_FILE_DESCRIPTORS 64
#define CONFIGURE_IMFS_ENABLE_MKFIFO    2

void POSIX_Init(rtems_task_argument ignored);
    
#define CONFIGURE_POSIX_INIT_THREAD_TABLE
#define CONFIGURE_MINIMUM_POSIX_THREAD_STACK_SIZE (64*1024)
#define CONFIGURE_INIT

#define RTEMS_BSD_CONFIG_BSP_CONFIG
#define RTEMS_BSD_CONFIG_INIT

#define CONFIGURE_SHELL_COMMANDS_INIT
#define CONFIGURE_SHELL_COMMANDS_ALL
#define CONFIGURE_SHELL_MOUNT_MSDOS
#define CONFIGURE_SHELL_MOUNT_NFS
#define CONFIGURE_MAXIMUM_POSIX_KEYS (5)

#include <rtems/netcmds-config.h>
#define CONFIGURE_SHELL_USER_COMMANDS \
  &rtems_shell_ARP_Command, \
  &rtems_shell_HOSTNAME_Command, \
  &rtems_shell_PING_Command, \
  &rtems_shell_ROUTE_Command, \
  &rtems_shell_NETSTAT_Command, \
  &rtems_shell_IFCONFIG_Command, \
  &rtems_shell_TCPDUMP_Command, \
  &rtems_shell_SYSCTL_Command, \
  &rtems_shell_VMSTAT_Command

#include <rtems/shellconfig.h>
#include <rtems/confdefs.h>
#include <machine/rtems-bsd-config.h>
