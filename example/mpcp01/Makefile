#
#  RTEMS_MAKEFILE_PATH is typically set in an environment variable
#

PGM=${ARCH}/hello.exe

# optional managers required
MANAGERS=all

# C source names
CSRCS = init.c
COBJS = $(CSRCS:%.c=${ARCH}/%.o)

#include inc/rtems_config.h
include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
include $(RTEMS_CUSTOM)
include $(PROJECT_ROOT)/make/leaf.cfg

CPU_DEFINES += -Iinc

OBJS= $(COBJS) $(CXXOBJS) $(ASOBJS)

all:    ${ARCH} $(PGM)

$(PGM): $(OBJS)
	$(make-exe)
