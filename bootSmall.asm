[BITS 16]
	cli
	xor bx, bx
	mov ss, bx
	mov sp, 0x7C00
	sti

	mov ax, 0x7C0
	mov ds, ax

driver_read: 
        mov cx, 1 
        xor dh, dh
        mov si, 0x1fc0
        mov es, si
.loop:
        add si, 0x40
        inc cl
        cmp cl, 19
        jnz .post
        mov cl, 1
        inc ch   
.post:      
        mov es, si
        mov ax, 0x0202        
        ;----
        ;mov di, 1111
        ;call print
        ;mov di, ax
        ;shr di, 8 
        ;call print
        ;mov di, ax
        ;shl di, 8
        ;shr di, 8 
        ;call print
        ;mov di, bx
        ;shr di, 8 
        ;call print
        ;mov di, bx
        ;shl di, 8
        ;shr di, 8 
        ;call print
        ;mov di, cx
        ;shr di, 8 
        ;call print
        ;mov di, cx
        ;shl di, 8
        ;shr di, 8 
        ;call print
        ;mov di, dx
        ;shr di, 8 
        ;call print
        ;mov di, dx
        ;shl di, 8
        ;shr di, 8 
        ;call print
        ;mov di, cx
        ;shr di, 8 
        ;call print
        ;----
        int 0x13
  ;      jc .error
        cmp ch, 21
        jnz .loop
        
 ;       mov di, ok
 ;       call print_str
.end:
	jmp .end


;.error:
;    mov di, fault
;    call print_str
;    jmp .end
;
;print_all:
;
;%include 'print.asm'
;
;new_line:
;        db 0xA
;ok:
;        db "OK", 0x0A, 0x0D, 0
        
;fault:
;        db "FAULT", 0x0A, 0x0D, 0
       
times 510-($-$$) db 0
dw 0xAA55
z
times 393214-($-$$) db 0xff

