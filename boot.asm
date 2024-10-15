[BITS 16]
	cli
	xor bx, bx
	mov ss, bx
	mov sp, 0x7C00
	sti

;	mov ax, 0x7C0
;	mov ds, ax

driver_read:
	push bx 
        pop cx 
        mov dh, 0
        mov si, 0x1fe0
.loop:
        add si, 0x20
        inc cl
        cmp cl, 19
        jnz .post
        mov cl, 1
        add ch, dh
        xor dh, 1   
.post:      
        mov es, si
        mov di, 4
.return:
        mov ax, 0x0201        
        int 0x13
        jc .error
        cmp si, 0x7fe0
        jnz .loop
        jmp .end
.error:
        sub di, 1
        jnz .return
.end:
	jmp .end

times 510-($-$$) db 0
dw 0xAA55

