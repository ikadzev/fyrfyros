boot.img:
	nasm -fbin boot.asm -o boot.bin
	dd if=/dev/zero of=boot.img bs=1024 count=1440
	dd if=boot.bin of=boot.img conv=notrunc

clean:
	rm boot.bin
