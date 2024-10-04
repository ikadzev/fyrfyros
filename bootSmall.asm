[BITS 16]
	cli
	xor bx, bx
	mov ss, bx
	mov sp, 0x7C00
	sti

	mov ax, 0x7C0
	mov ds, ax

driver_read: 

;mov di, 0

        mov cx, 0 
        mov dh, 0
        mov si, 0x1fe0
        mov es, si
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
        mov ax, 0x0201        
        int 0x13
;mov di,cx 
;shr di, 8
;call print
;mov di, dx
;shr di, 8
;call print
;mov di, cx
;shl di, 8
;shr di, 8
;call print
;jc .end
        cmp ch, 22
        jnz .loop
       
.end:
	jmp .end

;%include 'print.asm'

times 510-($-$$) db 0
dw 0xAA55
times 393216-($-$$) db 0xff

