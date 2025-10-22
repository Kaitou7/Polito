# MyFirstOS_Simple — Ultra-minimal 2-task cooperative scheduler (no interrupts)
# Toolchain (override CROSS=arm-none-eabi if needed)
CROSS   ?= arm-none-eabi
AS      := $(CROSS)-as
CC      := $(CROSS)-gcc
LD      := $(CROSS)-ld
OBJCOPY := $(CROSS)-objcopy
OBJDUMP := $(CROSS)-objdump

CPU     := -mcpu=cortex-m4 -mthumb
CFLAGS  := $(CPU) -ffreestanding -fno-builtin -O2 -Wall -Wextra -MMD -MP
ASFLAGS := $(CPU)
LDFLAGS := -T linker.ld -nostdlib

SRCS_C  := main.c os.c library.c
SRCS_S  := startup.s context_switch.s
OBJS    := $(SRCS_C:.c=.o) $(SRCS_S:.s=.o)
DEPS    := $(OBJS:.o=.d)

ELF := myfirstos_simple.elf

.PHONY: all clean run dump

all: $(ELF)

$(ELF): $(OBJS) linker.ld
	$(LD) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

run: $(ELF)
	qemu-system-arm -M netduino2 -nographic -kernel $(ELF) -semihosting

dump: $(ELF)
	$(OBJDUMP) -d -S $(ELF) | less

clean:
	$(RM) -f $(OBJS) $(DEPS) $(ELF)

-include $(DEPS)
