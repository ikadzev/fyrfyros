TARGET := boot
KERNEL := kernel

BUILD_DIR = ./bin
SOURCE_DIR = ./source
SRCS = $(shell find $(SOURCE_DIR) -name '*.c')
OBJS := $(SRCS:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)

CFLAGS := -m32 -ffreestanding -fno-pie -c
LDFLAGS := -m i386pe -Ttext=0x20200
OBJFLAGS := -I pe-i386 -O binary

execute: $(TARGET).img
	qemu-system-i386 -fda $< -monitor stdio

$(TARGET).img: $(BUILD_DIR)/$(KERNEL).bin $(BUILD_DIR)/$(TARGET).bin
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$(BUILD_DIR)/$(TARGET).bin of=$@ conv=notrunc
	dd if=$(BUILD_DIR)/$(KERNEL).bin of=$@ conv=notrunc seek=1

$(BUILD_DIR)/$(TARGET).bin: $(TARGET).asm
	nasm -fbin $< -o $@

$(BUILD_DIR)/$(KERNEL).bin: $(BUILD_DIR)/$(KERNEL).o $(OBJS)
	echo $(OBJS)
	ld $(LDFLAGS) -o $(BUILD_DIR)/$(KERNEL).tmp $^
	objcopy $(OBJFLAGS) $(BUILD_DIR)/$(KERNEL).tmp $(BUILD_DIR)/$(KERNEL).bin

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) -o $@ $<

$(BUILD_DIR)/$(KERNEL).o: $(KERNEL).c
	mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) -o $@ $(KERNEL).c

clean:
	rm -r $(BUILD_DIR)
