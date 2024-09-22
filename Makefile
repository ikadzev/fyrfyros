all: clear asm clean boot

clear:
	rm boot.img

asm:
	nasm -fbin boot.asm -o boot.bin
	dd if=/dev/zero of=boot.img bs=1024 count=1440
	dd if=boot.bin of=boot.img conv=notrunc

boot:
	qemu-system-x86_64 -hda boot.img -m 512

clean:
	rm boot.bin
