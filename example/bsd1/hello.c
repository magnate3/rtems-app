#include <rtems.h>
#include <bsp.h>
#include <rtems/bsd/bsd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <machine/rtems-bsd-commands.h>
#include <sysexits.h>
#include <rtems/shell.h>
#include <machine/rtems-bsd-rc-conf.h>
#include <errno.h>

void
POSIX_Init(rtems_task_argument ignored)
{
    
    int exit_code;
    char ip[] = "164.54.8.169";
    char gateway[] = "164.54.8.1";
    char ifname[] = "tsec2";
    char netmask[] = "255.255.252.0";
    char hostname[] = "iocanj1";

    int sc = rtems_bsd_initialize();
    assert(sc == RTEMS_SUCCESSFUL);

#if 0
    printf("ipaddr = %s\n", bsp_uboot_getenv("ipaddr"));
    printf("gatewayip = %s\n", bsp_uboot_getenv("gatewayip"));
    printf("netmask = %s\n", bsp_uboot_getenv("netmask"));
#endif

    rtems_bsd_setlogpriority("debug");

    rtems_bsd_ifconfig_lo0();


#if 0
	
    exit_code = rtems_bsd_ifconfig(ifname, ip, netmask, gateway);

    
    if (exit_code != EX_OK) {
	perror("rtems_bsd_command_ifconfig() failed to set up network.");
    }


    char * dflt_route[] = {
	"route", "add",
	"-host", gateway,
	"-iface", ifname,
	NULL
    };


    char * dflt_route2[] = {
	"route", "add", "default", gateway, NULL
    };

    exit_code = rtems_bsd_command_route(RTEMS_BSD_ARGC(dflt_route), dflt_route);
    if (exit_code != EX_OK) {
	perror("rtems_bsd_command_route failed to set up static route to gw.");
    }
	
    exit_code = rtems_bsd_command_route(RTEMS_BSD_ARGC(dflt_route2), dflt_route2);
    if (exit_code != EX_OK) {
	perror("rtems_bsd_command_route failed to set up default route.");
    }
#else
    size_t const RC_SIZE = 256;
    char rc_conf[RC_SIZE];
    
    sc = snprintf(rc_conf, RC_SIZE,
		  "# /etc/rc.conf\n" \
		  "hostname=\"%s\"\n" \
		  "ifconfig_%s=\"inet %s netmask %s\"\n" \
		  "defaultrouter=\"%s\"\n" \
		  "telnetd_enable=\"YES\"\n",
		  hostname, ifname, ip, netmask, gateway);
    assert(sc < RC_SIZE); // ensure rc_conf buffer is large enough

    FILE *rc;
    int   r;

    /*
     * Create the /etc/rc,conf, assume /etc exists.
     */
    rc = fopen("/etc/rc.conf", "w");
    if (rc_conf == NULL) {
	printf("error: cannot create /etc/rc.conf\n");
	exit(1);
    }

    fprintf(rc, rc_conf);
    fclose(rc);

    /*
     * Arguments are timeout and trace
     */
    r = rtems_bsd_run_etc_rc_conf(30, false);
    if (r < 0) {
	printf("error: loading /etc/rc.conf failed: %s\n",strerror(errno));
	exit(1);
    }
#endif
    
    const char* ifconfg_args[] = {
	"ifconfig", NULL
    };
    const char* netstat_args[] = {
	"netstat", "-rn", NULL
    };

    
    printf("-------------- IFCONFIG -----------------\n");
    rtems_bsd_command_ifconfig(1, (char**) ifconfg_args);
    printf("-------------- NETSTAT ------------------\n");
    rtems_bsd_command_netstat(2, (char**) netstat_args);
    
    // Start an rtems shell to test and see if ping etc work
    rtems_shell_init("SHLL", RTEMS_MINIMUM_STACK_SIZE * 4,
                     100, "/dev/console",
                     false, true,
                     NULL);
    exit(0);
}
