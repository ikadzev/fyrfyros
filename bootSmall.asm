[BITS 16]
	cli
	xor bx, bx
	mov ss, bx
	mov sp, 0x7C00
	sti

	mov ax, 0x7C0
	mov ds, ax

        mov di, 100

driver_read: ;input: cx -- адрес памяти начиная с которого грузим ядро
             ;       di -- количество загружаеммых секторов
        mov cx, 1 ; номер сектора[0] 1-18
        xor dh, dh; номер головки[1] 0-1
        mov si, 0x1fe0
        mov es, si
.loop:
        add si, 0x20
        cmp di, 0
        jz .end
        
        inc cl
        cmp cl, 19
        jnz .post
        mov cl, 1
        inc dh
        cmp dh, 2
        jnz .post
        mov dh, 0
        cmp ch, 79
        jz .end
        inc ch   
.post:      
        mov es, si
        mov ah, 2
        mov al, 1        
        int 0x13
        dec di
        jmp .loop
.end:
	jmp .end

times 510-($-$$) db 0
dw 0xAA55

times 393214-($-$$) db 0xff

