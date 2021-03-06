#/*
#    FreeRTOS V8.2.3 - Copyright (C) 2015 Real Time Engineers Ltd.
#	
#
#    ***************************************************************************
#     *                                                                       *
#     *    FreeRTOS tutorial books are available in pdf and paperback.        *
#     *    Complete, revised, and edited pdf reference manuals are also       *
#     *    available.                                                         *
#     *                                                                       *
#     *    Purchasing FreeRTOS documentation will not only help you, by       *
#     *    ensuring you get running as quickly as possible and with an        *
#     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
#     *    the FreeRTOS project to continue with its mission of providing     *
#     *    professional grade, cross platform, de facto standard solutions    *
#     *    for microcontrollers - completely free of charge!                  *
#     *                                                                       *
#     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
#     *                                                                       *
#     *    Thank you for using FreeRTOS, and thank you for your support!      *
#     *                                                                       *
#    ***************************************************************************
#
#
#    This file is part of the FreeRTOS distribution and was contributed
#    to the project by Technolution B.V. (www.technolution.nl,
#    freertos-riscv@technolution.eu) under the terms of the FreeRTOS
#    contributors license.
#
#    FreeRTOS is free software; you can redistribute it and/or modify it under
#    the terms of the GNU General Public License (version 2) as published by the
#    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
#    >>>NOTE<<< The modification to the GPL is included to allow you to
#    distribute a combined work that includes FreeRTOS without being obliged to
#    provide the source code for proprietary components outside of the FreeRTOS
#    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
#    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
#    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
#    more details. You should have received a copy of the GNU General Public
#    License and the FreeRTOS license exception along with FreeRTOS; if not it
#    can be viewed here: http://www.freertos.org/a00114.html and also obtained
#    by writing to Richard Barry, contact details for whom are available on the
#    FreeRTOS WEB site.
#
#    1 tab == 4 spaces!
#
#    http://www.FreeRTOS.org - Documentation, latest information, license and
#    contact details.
#
#    http://www.SafeRTOS.com - A version that is certified for use in safety
#    critical systems.
#
#    http://www.OpenRTOS.com - Commercial support, development, porting,
#    licensing and training services.
#*/

include ../Common/Makefile.inc

# Root of RISC-V tools installation. Note that we expect to find the spike
# simulator header files here under $(RISCV)/include/spike .
RISCV ?= /opt/riscv

FREERTOS_SRC = \
	$(FREERTOS_SOURCE_DIR)/croutine.c \
	$(FREERTOS_SOURCE_DIR)/list.c \
	$(FREERTOS_SOURCE_DIR)/queue.c \
	$(FREERTOS_SOURCE_DIR)/tasks.c \
	$(FREERTOS_SOURCE_DIR)/timers.c \
	$(FREERTOS_SOURCE_DIR)/event_groups.c \
	$(FREERTOS_SOURCE_DIR)/portable/MemMang/heap_2.c \
	$(FREERTOS_SOURCE_DIR)/string.c


PORT_SRC = $(FREERTOS_SOURCE_DIR)/portable/GCC/RISCV/port.c
PORT_ASM = $(FREERTOS_SOURCE_DIR)/portable/GCC/RISCV/portasm.S

DEMO_SRC = \
	../arch/clib.c \
	../arch/systemPort.c \
	../Common/FreeRTOS-openocd.c \
	../Common/main.c

INCLUDES = \
	-I. \
	-I../arch \
	-I.. \
	-I./conf \
	-I./include \
	-I$(FREERTOS_SOURCE_DIR)/include \
	-I../Common/include \
	-I$(FREERTOS_SOURCE_DIR)/portable/GCC/RISCV

CFLAGS = \
	$(WARNINGS) $(INCLUDES) \
	-fomit-frame-pointer -fno-strict-aliasing -fno-builtin \
	-D__gracefulExit -mcmodel=medany \
        -march=$(ARCH)  -mabi=ilp32 -g -${OPT}

ifeq ($(PRINT_ENABLE),yes)
	CFLAGS += -DPRINT_ENABLE
endif

GCCVER 	= $(shell $(GCC) --version | grep gcc | cut -d" " -f9)

#
# Define all object files.
#
RTOS_OBJ = $(FREERTOS_SRC:.c=.o)
APP_OBJ  = $(APP_SRC:.c=.o)
PORT_OBJ = $(PORT_SRC:.c=.o)
DEMO_OBJ = $(DEMO_SRC:.c=.o)
PORT_ASM_OBJ = $(PORT_ASM:.S=.o)
CRT0_OBJ = $(CRT0:.S=.o)
OBJS = $(CRT0_OBJ) $(PORT_ASM_OBJ) $(PORT_OBJ) $(RTOS_OBJ) $(DEMO_OBJ) $(APP_OBJ)

LDFLAGS	 = -g -T ../arch/link.ld -nostartfiles -static -nostdlib -march=$(ARCH)
LIBS	 = -L$(CCPATH)/lib/gcc/$(TARGET)/$(GCCVER) \
		   -L$(CCPATH)/$(TARGET)/lib \
		   -lc -lgcc

%.o: %.c
	@echo "    CC $<"
	$(GCC) -c $(CFLAGS) -o $@ $<

%.o: %.S
	@echo "    CC $<"
	$(GCC) -c $(CFLAGS) -o $@ $<

all: bin/$(PROG).elf

bin/$(PROG).elf  : $(OBJS) Makefile 
	@echo Linking....
	@mkdir -p bin
	@$(GCC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) -o bin/$(PROG).elf	
	@$(OBJDUMP) -S -d bin/$(PROG).elf > bin/$(PROG).asm	
	@$(OBJCOPY) -O ihex bin/$(PROG).elf bin/$(PROG).hex 
	@echo Completed $@ ${ARCH}


clean :
	@rm -f $(OBJS)
	@rm -f bin/$(PROG).elf 
	@rm -f bin/$(PROG).map
	@rm -f bin/$(PROG).asm
	@rm -f bin/$(PROG).hex

force_true:
	@true


