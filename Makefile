all: clear asm1 checkSize asm2 clean boot checkAnswer

clear:
	touch boot.img
	touch foo.img
	rm boot.img
	rm foo.img

asm1:
	nasm -fbin bootSmall.asm -o boot.bin
	nasm -fbin foo.asm -o foo.bin

checkSize:
	if [ $(wc -c "foo.bin" | awk '{print $1}') != 392716 ]; then echo "File size \"foo.bin\" not equal 384kb !"; exit 1; fi

asm2:
	dd if=/dev/zero of=boot.img bs=1024 count=1440
	dd if=boot.bin of=boot.img conv=notrunc
	dd if=foo.bin of=boot.img conv=notrunc seek=1

boot:
	qemu-system-i386 -fda boot.img -monitor stdio 

checkAnswer:
	python3 checksum.py dump.img
	python3 checksum.py boot.img

clean:
	rm boot.bin
	rm foo.bin
