CC := arm-none-eabi-gcc
LD := arm-none-eabi-ld
AS := arm-none-eabi-as
AR := arm-none-eabi-ar -cr
OBJCOPY := arm-none-eabi-objcopy

TARGET := image.hex

OBJS := startup.o $(patsubst %.c,%.o,$(wildcard *.c))

CFLAGS := -mcpu=arm7tdmi-s -g3 -Wall -I.
AS_FLAGS := -mcpu=arm7tdmi-s -g3

LD_FLAGS := -Wl,-Map,$(TARGET:%.hex=%).map -nostartfiles

LD_SCRIPT := lpc2138.ld

$(TARGET) : $(TARGET:%.hex=%)
	$(OBJCOPY) -O ihex $< $@

$(TARGET:%.hex=%) : $(OBJS)
	$(CC) -o $@ -T $(LD_SCRIPT) $(OBJS) $(LD_FLAGS)

startup.o : startup.s
	$(AS) $(AS_FLAGS) -o $@ $<

%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean :
	rm -rf $(TARGET) $(TARGET:%.hex=%) $(TARGET:%.hex=%).map *.o
