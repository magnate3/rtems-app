#
#  Makefile
#

#
#  RTEMS_MAKEFILE_PATH is typically set in an environment variable
#

EXEC=messageQueue.exe
PGM=${ARCH}/$(EXEC)

# optional managers required
MANAGERS=all

# C source names
CSRCS = messageQueue.c
COBJS_ = $(CSRCS:.c=.o)
COBJS = $(COBJS_:%=${ARCH}/%)

# C++ source names
CXXSRCS =
CXXOBJS_ = $(CXXSRCS:.cc=.o)
CXXOBJS = $(CXXOBJS_:%=${ARCH}/%)

# AS source names
ASSRCS =
ASOBJS_ = $(ASSRCS:.s=.o)
ASOBJS = $(ASOBJS_:%=${ARCH}/%)

# Libraries
LIBS = -lrtemsall -lc

include $(RTEMS_MAKEFILE_PATH)/Makefile.inc

include $(RTEMS_CUSTOM)
include $(PROJECT_ROOT)/make/leaf.cfg

OBJS= $(COBJS) $(CXXOBJS) $(ASOBJS)

all:    ${ARCH} $(PGM)

$(PGM): $(OBJS)
	$(make-exe)
	#mcopy -o $(PGM) x:


j:
	@echo $(CFLAGS_DEBUG_V)
	@echo $(RTEMS_USE_GCC272)
