[BITS 16]
	cli
	xor bx, bx
	mov ss, bx
	mov sp, 0x7C00
	sti

	mov ax, 0x7C0
	mov ds, ax

        mov di, 1;768
        call driver_read
        mov di, ok
        call print_str
end:
	jmp end

driver_read: ;input: cx -- адрес памяти начиная с которого грузим ядро
             ;       di -- количество загружаеммых секторов
        mov cx, 0 ; номер сектора[0] 1-18
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
        cmp ch, 1
        jz .end
        inc ch   
.post:      
        mov es, si
        mov ah, 2
        mov al, 1        
        int 0x13
        jc error
        dec di
        jmp .loop
.end:
       ret
        
error:
    mov di, fault
    call print_str
jmp end


ok:
        db "OK", 0x0A, 0x0D, 0
        
fault:
        db "FAULT", 0x0A, 0x0D, 0

%include 'print.asm'

times 510-($-$$) db 0
dw 0xAA55


