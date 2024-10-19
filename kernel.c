void vga_clear_screen();
void vga_print_char(char, int, int);
void vga_print_str(char*, int, int);
void vga_error();

void kernel_entry() {
    vga_clear_screen();
    vga_print_str("AWESOME", 76, 23);
    for (;;);
}

void vga_clear_screen() {
    for (int i = 0xB8000; i < 0xB8FA0; i += 2) {
        *((short int*) i) = 0x0000;
    }
}

void vga_print_char(char sym, int x, int y) {
    if ((x >= 80) || (y >= 25)) {
        vga_error();
        return;
    }
    int pos = 0xB8000 + 2*(80 * y + x);
    *((short int*) pos) = 0x0F00 + (int) sym;
}

void vga_print_str(char* str, int x, int y) {
    if ((x >= 80) || (y >= 25)) {
        vga_error();
        return;
    }
    int pos = 0xB8000 + 2*(80 * y + x);
    for (int i = 0; (str[i] != 0) & (pos < 0xB8FA0); i++) {
        *((short int*) pos) = 0x0F00 + (int) str[i];
        pos += 2;
    }
}

void vga_error() {
    *((short int*) 0xB8000) = 0x4F00 + (int) 'E';
    *((short int*) 0xB8002) = 0x4F00 + (int) 'R';
    *((short int*) 0xB8004) = 0x4F00 + (int) 'R';
    *((short int*) 0xB8006) = 0x4F00 + (int) 'O';
    *((short int*) 0xB8008) = 0x4F00 + (int) 'R';
}