TOOLCHAIN_PREFIX:=arm-none-eabi-
CC := $(TOOLCHAIN_PREFIX)gcc
LD := $(TOOLCHAIN_PREFIX)ld
AS := $(TOOLCHAIN_PREFIX)as
AR := $(TOOLCHAIN_PREFIX)ar -cr
OBJCOPY := $(TOOLCHAIN_PREFIX)objcopy

RM := rm -f

SRC_DIR := src
INC_DIR := include

TARGET := image.hex

OBJS := $(SRC_DIR)/startup.o $(patsubst %.c,%.o,$(wildcard $(SRC_DIR)/*.c))

CFLAGS := -mcpu=arm7tdmi-s -g3 -Wall -I$(INC_DIR) -gdwarf-2

AS_FLAGS := -mcpu=arm7tdmi-s -g3 -gdwarf-2

LD_FLAGS := -Wl,-Map,$(TARGET:%.hex=%).map -nostartfiles

LD_SCRIPT := $(SRC_DIR)/lpc2138.ld

all : $(TARGET)

$(TARGET) : $(TARGET:%.hex=%.elf)
	@echo "\tHEX\t$@"
	@$(OBJCOPY) -O ihex $< $@

$(TARGET:%.hex=%.elf) : $(OBJS)
	@echo "\tLD\t$@"
	@$(CC) -o $@ -T $(LD_SCRIPT) $(OBJS) $(LD_FLAGS)

$(SRC_DIR)/startup.o : $(SRC_DIR)/startup.s
	@echo "\tAS\t$@"
	@$(AS) $(AS_FLAGS) -o $@ $<

$(SRC_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "\tCC\t$@"
	@$(CC) -c $(CFLAGS) -o $@ $<

clean :
	$(RM) $(TARGET) $(TARGET:%.hex=%.elf) $(TARGET:%.hex=%).map $(SRC_DIR)/*.o
