[BITS 16]
	cli
	xor bx, bx
	mov ss, bx
	mov sp, 0x7C00
	sti

	mov ax, 0x7C0
	mov ds, ax

vbr_copy:
        ; TODO VBR copy to 0x20000

driver_read:
	push bx 
        pop cx 
        mov dh, 0
        mov si, 0x2000
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
        jmp protected_mode_enable
.error:
        sub di, 1
        jnz .return
.end:
        jmp .end

protected_mode_enable:
        cli
        lgdt [gdt_descriptor]
        jmp CODE_SEG:protected_mode_tramplin + 0x7C00

[BITS 32]
protected_mode_tramplin:
        mov eax, cr0
        or al, 1
        mov cr0, eax
        mov bx, DATA_SEG
        mov ds, bx
        mov ss, bx
        mov es, bx
        mov fs, bx
        mov gs, bx
        mov esp, 0x20000
        jmp CODE_SEG:0x20200

gdt_start:
        dq 0x0
gdt_code:
        dw 0xFFFF
        dw 0x0200
        dw 0x9A02
        dw 0x004F
gdt_data:
        dw 0xFFFF
        dw 0x0000
        dw 0x9200
        dw 0x00CF
gdt_end:

gdt_descriptor:
        dw gdt_end - gdt_start - 1
        dd gdt_start + 0x20000

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

times 510-($-$$) db 0
dw 0xAA55

