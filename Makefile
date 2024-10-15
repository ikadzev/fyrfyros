all: clear asm1 checkSize asm2 clean boot checkAnswer

clear:
	touch boot.img
	rm boot.img

asm:
	nasm -fbin boot.asm -o boot.bin
	nasm -fbin foo.asm -o foo.bin

checkSize:
	if [ "$(shell wc -c "foo.bin")" != "392704 foo.bin" ]; then echo "File size \"foo.bin\" not equal 384kb !"; exit 1; fi

asm2:
	dd if=/dev/zero of=boot.img bs=1024 count=1440
	dd if=boot.bin of=boot.img conv=notrunc
	dd if=foo.bin of=boot.img conv=notrunc seek=1

boot:
	qemu-system-i386 -fda boot.img -monitor stdio # manual "memsave 0x20000 0x60000 dump.img"

checkAnswer:
	python3 checksum.py dump.img
	python3 checksum.py boot.img

clean:
	rm boot.bin
