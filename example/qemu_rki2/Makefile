#
#  RTEMS_MAKEFILE_PATH is typically set in an environment variable
#

PGM=${ARCH}/hello.exe

# optional managers required
MANAGERS=all

# C source names
H_FILES= default-network-init.h
#CSRCS = shellconfig.c  test_main.c 
CSRCS = $(wildcard *.c)
CSRCS +=
COBJS = $(CSRCS:%.c=${ARCH}/%.o)
include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
include $(RTEMS_CUSTOM)
include $(PROJECT_ROOT)/make/leaf.cfg

CPU_DEFINES += -I ./inc
LD_LIBS   +=  -lftpd -lbsd -lm
OBJS= $(COBJS) $(CXXOBJS) $(ASOBJS)

all:    ${ARCH} $(PGM)

$(PGM): $(OBJS)
	$(make-exe)
