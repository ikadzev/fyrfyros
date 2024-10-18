all: clear build clean boot
build: vbr kernel img
clr: clear clean

clear:
	touch boot.img
	rm boot.img

vbr:
	nasm -fbin boot.asm -o boot.bin

kernel:
	gcc -m32 -ffreestanding -fno-pie -c -o kernel.o kernel.c
	ld -m i386pe -o kernel.tmp -Ttext=0x20200 kernel.o
	objcopy -I pe-i386 -O binary kernel.tmp kernel.bin

img:
	dd if=/dev/zero of=boot.img bs=1024 count=1440
	dd if=boot.bin of=boot.img conv=notrunc
	dd if=kernel.bin of=boot.img conv=notrunc seek=1

boot:
	qemu-system-i386 -fda boot.img -monitor stdio

clean:
	rm *.bin
	rm kernel.o
	rm kernel.tmp
