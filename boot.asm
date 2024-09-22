[BITS 16]

mov ax, 0x7C0
mov ds, ax
mov ah, 0xE
xor bx, bx

loop:
	mov al, [bx + data]
	cmp al, 0 
	jz end
	int 0x10
	inc bx
	jmp loop
	
end:
	jmp end

data:
        db "Hello World!", 0x0A, 0x0D, 0 

times 510-($-$$) db 0
dw 0xAA55

