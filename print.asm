print:
    ; Число находится в регистре CX
    ; Преобразуем число в строку ASCII
    push ax
    push bx
    push dx
    push si
    mov bx, 10                 ; для деления на 10
    mov ax, di                 ; переносим CX в AX для деления
    mov si, 0                  ; SI счётчик цифр

.convert_loop:
    xor dx, dx                 ; очищаем DX перед делением
    div bx                     ; AX = AX / 10, остаток (цифра) в DX, частное в AX
    add dl, '0'                ; преобразуем остаток в символ ASCII
    push dx                    ; сохраняем цифру на стеке
    inc si                     ; увеличиваем счётчик цифр
    cmp ax, 0                  ; если частное 0, все цифры обработаны
    jne .convert_loop           ; если AX не 0, продолжаем деление

    ; Выводим число на экран, начиная с последней цифры
.print_loop:
    pop dx                    ; извлекаем цифру с конца
    mov al, dl
    mov ah,0xE                 ; функция BIOS для вывода символа
    int 0x10                    ; выводим символ
    dec si                     ; уменьшаем счётчик цифр
    jnz .print_loop             ; если ещё есть цифры, повторяем цикл
    mov al, 0xA
    mov ah,0xE
    int 0x10
    mov al, 0x0D
    mov ah,0xE
    int 0x10
    pop si
    pop dx
    pop bx
    pop ax
	ret

print_str: ;input: di 
    push ax
    push bx
    mov ah, 0xE
    xor bx, bx
.loop:
    mov al, [bx + di]
    cmp al, 0 
    jz .end
    int 0x10
    inc bx
    jmp .loop
.end:
    pop bx
    pop ax
    ret

