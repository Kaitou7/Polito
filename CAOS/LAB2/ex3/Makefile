CC =arm-none-eabi
AARCH = -mcpu=cortex-m4
CFLAGS = -c -Wall $(AARCH) -mthumb

LINKER = linker.ld
FLAG_LINKER = -T $(LINKER)
SRC_C = delay.c main.c usart.c
SRC_S = startup.s

OBJS_C =$(SRC_C:%.c=%.o)
OBJS_S =$(SRC_S:%.s=%.o)
OBJS_C_DEBUG = $(SRC_C:%.c=%_dbg.o)
OBJS_S_DEBUG = $(SRC_S:%.s=%_dbg.o)
DEPS = $(OBJS_C:%.o=%.d) $(OBJS_S:%.o=%.d)
DEPS_DEBUG = $(OBJS_C_DEBUG:%.o=%.d) $(OBJS_S_DEBUG:%.o=%.d)
TARGET = app
TARGET_DEBUG = app_debug.elf

qemu = qemu-system-arm -M netduinoplus2 -nographic -kernel
qemu_start = $(qemu) $(TARGET)
qemu_debug = $(qemu) $(TARGET_DEBUG) -s -S


all: $(TARGET)

run : $(TARGET)
	$(qemu_start)

qemu_debug_start:
	gdb-multiarch $(TARGET_DEBUG)

debug : $(TARGET_DEBUG)
	$(qemu_debug)

$(TARGET_DEBUG): $(OBJS_S_DEBUG)  $(OBJS_C_DEBUG) 
	$(CC)-ld $(FLAG_LINKER) $^ -o  $@

$(TARGET) : $(OBJS_S) $(OBJS_C)
	$(CC)-ld $(FLAG_LINKER) $^ -o $@

%_dbg.o : %.c 
	$(CC)-gcc -g $(CFLAGS) $< -o $@

%_dbg.o : %.s
	$(CC)-as $(AARCH) -g $< -o $@

%.o : %.c 
	$(CC)-gcc $(CFLAGS) -mcpu=cortex-m4 -mthumb $< -o $@

%.o : %.s
	$(CC)-as $(AARCH) $< -o $@

-include $(DEPS) $(DEPS_DEBUG)

clean:
	rm -f *.o *.d *.elf