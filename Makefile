TOOLCHAIN_PREFIX:=arm-none-eabi-
CC := $(TOOLCHAIN_PREFIX)gcc
LD := $(TOOLCHAIN_PREFIX)ld
AS := $(TOOLCHAIN_PREFIX)as
AR := $(TOOLCHAIN_PREFIX)ar -cr
OBJCOPY := $(TOOLCHAIN_PREFIX)objcopy

ifeq ($(OS),Windows_NT)
RM := del
else
RM := rm -f
endif

TARGET := image.hex

OBJS := startup.o $(patsubst %.c,%.o,$(wildcard *.c))

CFLAGS := -mcpu=arm7tdmi-s -g3 -Wall -I. -gdwarf-2
AS_FLAGS := -mcpu=arm7tdmi-s -g3 -gdwarf-2

LD_FLAGS := -Wl,-Map,$(TARGET:%.hex=%).map -nostartfiles

LD_SCRIPT := lpc2138.ld

all	:	$(TARGET)

$(TARGET) : $(TARGET:%.hex=%.elf)
	$(OBJCOPY) -O ihex $< $@

$(TARGET:%.hex=%.elf) : $(OBJS)
	$(CC) -o $@ -T $(LD_SCRIPT) $(OBJS) $(LD_FLAGS)

startup.o : startup.s
	$(AS) $(AS_FLAGS) -o $@ $<

%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean :
	$(RM) $(TARGET) $(TARGET:%.hex=%.elf) $(TARGET:%.hex=%).map *.o
