//
// Created by modnick on 25.10.2024.
//

#include "headers/vga_driver.h"

struct{
    unsigned short x;
    unsigned short y;
    unsigned short now_char;
} carriage;


void carriage_inc(){
//    if (carriage.x == SIZE_X_DISPLAY - 1) {
//        carriage.x = 0;
//        carriage.y++;
//    } else {
//        carriage.x++;
//    }
    carriage.x++;
    carriage.y += carriage.x / SIZE_X_DISPLAY;
    carriage.x %= SIZE_X_DISPLAY;

    if (carriage.y == SIZE_Y_DISPLAY - 1) {
        carriage.y--;
        vga_shift_down_line();
    }
    unsigned long pos = START_DISPLAY_ADDRESS + 2*(SIZE_X_DISPLAY * carriage.y + carriage.x);
    carriage.now_char = *((unsigned short*) pos);
    pos = START_DISPLAY_ADDRESS + 2*(SIZE_X_DISPLAY * carriage.y + carriage.x);
    *((unsigned short*) pos) = + 0xff00 + (unsigned short)('0');
}

void carriage_shift(int shift){
    for (int i = 0; i < shift; ++i) {
        carriage_inc();
    }
//    carriage.x += shift - 1;
//    carriage_inc();
}

void carriage_dec(){
    carriage.y -= (carriage.x == 0 && carriage.y);
    carriage.x = (carriage.x ? carriage.x - 1 : SIZE_X_DISPLAY - 1);
}

void vga_init() {
    carriage.x = 0;
    carriage.y = 0;
    carriage.now_char = 0;
    vga_clear_screen();
}

void vga_clear_screen() {
    for (unsigned long i = START_DISPLAY_ADDRESS; i < END_DISPLAY_ADDRESS; i += 2) {
        *((unsigned short*) i) = black_f + black_b;
    }
}

void vga_print_char(char sym, color_front front, color_back back, int x, int y) {
    if ((x >= SIZE_X_DISPLAY) || (y >= SIZE_Y_DISPLAY)) {
        vga_error();
        return;
    }
    carriage.x = x;
    carriage.y = y;
    vga_print_char_carriage(sym, front, back);
}

void vga_print_char_carriage(char sym, color_front front, color_back back){
    unsigned long pos = START_DISPLAY_ADDRESS + 2*(SIZE_X_DISPLAY * carriage.y + carriage.x);
    *((unsigned short*) pos) = + front + back + (unsigned short)sym;
    carriage_inc();
}

void vga_scroll_line(int flag_down){
    unsigned short step = (flag_down ? SIZE_X_DISPLAY : -SIZE_X_DISPLAY);
    unsigned short start_coord = (flag_down ? 0 : SIZE_X_DISPLAY * (SIZE_Y_DISPLAY - 1));
    unsigned short end_coord = (flag_down ? SIZE_X_DISPLAY * (SIZE_Y_DISPLAY - 1) : 0);

    for (int j = 0; j < SIZE_X_DISPLAY; ++j) {
        unsigned short* input_address = (unsigned short*)(START_DISPLAY_ADDRESS + 2 * (start_coord + j));
        unsigned short* output_address = input_address + step;
        for (int i = 0; i < SIZE_Y_DISPLAY - 1; ++i) {
            *input_address = *output_address;
            input_address = output_address;
            output_address += step; // !!!
        }
    }

    for (int j = 0; j < SIZE_X_DISPLAY; ++j) {
        *(unsigned short*)(START_DISPLAY_ADDRESS + 2 * (end_coord  + j)) = black_f + black_f;
    }
}

void vga_shift_up_line() {
    vga_scroll_line(0);
}

void vga_shift_down_line() {
    vga_scroll_line(1);
}


void vga_error() {
    *((short int*) 0xB8000) = 0x4F00 + (int) 'E';
    *((short int*) 0xB8002) = 0x4F00 + (int) 'R';
    *((short int*) 0xB8004) = 0x4F00 + (int) 'R';
    *((short int*) 0xB8006) = 0x4F00 + (int) 'O';
    *((short int*) 0xB8008) = 0x4F00 + (int) 'R';
}
//// перенос строки
//// шифт кареток
//// отображение каретки
//// ...
