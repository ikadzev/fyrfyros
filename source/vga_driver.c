//
// Created by modnick on 25.10.2024.
// Update by RostyanYandexLyceumCheeeeck on 01.11.2024.
//

#include "headers/vga_driver.h"

struct{
    unsigned short x;
    unsigned short y;
    unsigned short now_char;
} carriage;

void carriage_inc() {
    carriage.x++;
    carriage.y += carriage.x / SIZE_X_DISPLAY;
    carriage.x %= SIZE_X_DISPLAY;

    while (carriage.y >= SIZE_Y_DISPLAY) {
        carriage.y--;
        carriage_shift_down_line();
    }
}

void carriage_shift(int shift) {
    if ( shift < 0) {
        int x_temp = (int) carriage.x + shift % SIZE_X_DISPLAY;
        int y_temp = (int) carriage.y + shift / SIZE_X_DISPLAY - (int)(x_temp < 0);

        carriage.y = (unsigned short)(y_temp < 0 ? 0 : y_temp);
        carriage.x = (unsigned short)(x_temp < 0 ? SIZE_X_DISPLAY + x_temp : x_temp);
        carriage.x = (unsigned short)(y_temp < 0 ? 0 : carriage.x);
    } else {
        carriage.x += shift - 1;
        carriage_inc();
    }
}

void carriage_dec() {
    carriage.y -= (carriage.x == 0 && carriage.y);
    carriage.x = (carriage.x ? carriage.x : SIZE_X_DISPLAY) - 1;
}

void carriage_start() {
    carriage.x = 0;
}

void carriage_new_line() {
    carriage.x--;
    carriage.y++;
    carriage_inc();
}

void carriage_set_position(unsigned short x, unsigned short y) {
    if ((x >= SIZE_X_DISPLAY) || (y >= SIZE_Y_DISPLAY)) {
        vga_error();
        return;
    }
    carriage.x = x;
    carriage.y = y;
}

void carriage_shift_up_line() {
    vga_scroll_line(0);
}

void carriage_shift_down_line() {
    vga_scroll_line(1);
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

void vga_print_char(char sym, color_front front, color_back back, unsigned short x, unsigned short y) {
    carriage_set_position(x, y);
    vga_print_char_carriage(sym, front, back);
}

void vga_print_char_carriage(char sym, color_front front, color_back back) {
    unsigned long pos = START_DISPLAY_ADDRESS + 2*(SIZE_X_DISPLAY * carriage.y + carriage.x);
    switch (sym) {
        case '\t': {
            do {
                vga_print_char_carriage(' ', front, back);
            } while (carriage.x % 8);
            break;
        }
        case '\r': {
            carriage_start();
            break;
        }
        case '\n': {
            carriage_new_line();
            break;
        }
        case '\0': {
            break;
        }
        default: {
            *((unsigned short*) pos) = (front + back + (unsigned short)sym);
            carriage_inc();
        }
    }
}

void vga_scroll_line(char flag_down) {
    short step = (flag_down ? SIZE_X_DISPLAY : -SIZE_X_DISPLAY);
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
        *(unsigned short*)(START_DISPLAY_ADDRESS + 2 * (end_coord + j)) = black_f + black_f;
    }
}

void vga_error() {
    *((short int*) 0xB8000) = 0x4F00 + (int) 'E';
    *((short int*) 0xB8002) = 0x4F00 + (int) 'R';
    *((short int*) 0xB8004) = 0x4F00 + (int) 'R';
    *((short int*) 0xB8006) = 0x4F00 + (int) 'O';
    *((short int*) 0xB8008) = 0x4F00 + (int) 'R';
}
