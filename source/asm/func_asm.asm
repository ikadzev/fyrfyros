global outb
global inb
global set_CR3
global get_CR3
global expose_bit_CR4
global clear_bit_CR4
global expose_bit_CR0
global clear_bit_CR0
global cli
global sti


cli:
    cli
    ret

sti:
    sti
    ret

set_CR3:
    mov eax, [esp + 4]
    mov cr3, eax
    ret

get_CR3:
    mov eax, cr3
    ret

expose_bit_CR4:
    mov eax, cr4
    mov edx, 1
    mov ecx, [esp + 4]
    dec ecx
    shl edx, cl
    or eax, edx
    mov cr4, eax
    ret

clear_bit_CR4:
    mov eax, cr4
    mov edx, 1
    mov ecx, [esp + 4]
    dec ecx
    shl edx, cl
    xor edx, -1
    and eax, edx
    mov cr4, eax
    ret

expose_bit_CR0:
    mov eax, cr0
    mov edx, 1
    mov ecx, [esp + 4]
    dec ecx
    shl edx, cl
    or eax, edx
    mov cr0, eax
    ret

clear_bit_CR0:
    mov eax, cr0
    mov edx, 1
    mov ecx, [esp + 4]
    dec ecx
    shl edx, cl
    xor edx, -1
    and eax, edx
    mov cr0, eax
    ret

outb:
    mov edx, [esp + 4]
    mov eax, [esp + 8]
    out dx, al
    ret

inb:
    mov edx, [esp + 4]
    mov eax, -1
    in ax, dx
    ret
