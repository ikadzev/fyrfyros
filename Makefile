TARGET := boot
KERNEL := kernel

BUILD_DIR = ./bin
SOURCE_DIR = ./source
HEADERS_DIR = $(SOURCE_DIR)/headers
SRCS = $(shell find $(SOURCE_DIR) -name '*.c')
SRCS_ASM = $(shell find $(SOURCE_DIR)/asm -name '*.asm')
OBJS := $(SRCS:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJS_ASM := $(SRCS_ASM:$(SOURCE_DIR)/asm/%.asm=$(BUILD_DIR)/%_asm.o)
HEADS := $(shell find $(HEADERS_DIR) -name '*.h')

CFLAGS := -m32 -ffreestanding -fno-pie -c
LDFLAGS := -m elf_i386 -Ttext=0x20200
OBJFLAGS := -I pe-i386 -O binary

.PHONY: execute build clean
execute: $(TARGET).img
	qemu-system-i386 -drive file=boot.img,index=0,if=floppy -monitor stdio -boot a

build: $(TARGET).img

clean:
	rm -r $(BUILD_DIR)

log:
	git log --oneline --all --graph

$(TARGET).img: $(BUILD_DIR)/$(KERNEL).bin $(BUILD_DIR)/$(TARGET).bin
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$(BUILD_DIR)/$(TARGET).bin of=$@ conv=notrunc
	dd if=$(BUILD_DIR)/$(KERNEL).bin of=$@ conv=notrunc seek=1

$(BUILD_DIR)/$(TARGET).bin: $(TARGET).asm
	nasm -fbin $< -o $@

$(BUILD_DIR)/$(KERNEL).bin: $(BUILD_DIR)/$(KERNEL).o $(OBJS) $(OBJS_ASM)
	ld $(LDFLAGS) -o $(BUILD_DIR)/$(KERNEL).tmp $^ 
	objcopy $(OBJFLAGS) $(BUILD_DIR)/$(KERNEL).tmp $(BUILD_DIR)/$(KERNEL).bin

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c $(HEADS)
	mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%_asm.o: $(SOURCE_DIR)/asm/%.asm
	mkdir -p $(BUILD_DIR)
	nasm -felf $< -o $@

$(BUILD_DIR)/$(KERNEL).o: $(KERNEL).c $(HEADS)
	mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) -o $@ $(KERNEL).c

