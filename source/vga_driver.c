//
// Created by modnick on 25.10.2024.
// Update by RostyanYandexLyceumCheeeeck on 01.11.2024.
//

#include "headers/vga_driver.h"

struct {
    u16 x;
    u16 y;
    u16 now_char;
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

void carriage_shift(i32 shift) {
    if ( shift < 0) {
        i32 x_temp = (i32) carriage.x + shift % SIZE_X_DISPLAY;
        i32 y_temp = (i32) carriage.y + shift / SIZE_X_DISPLAY - (i32)(x_temp < 0);

        carriage.y = (u16)(y_temp < 0 ? 0 : y_temp);
        carriage.x = (u16)(x_temp < 0 ? SIZE_X_DISPLAY + x_temp : x_temp);
        carriage.x = (u16)(y_temp < 0 ? 0 : carriage.x);
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

void carriage_set_position(u16 x, u16 y) {
    if ((x >= SIZE_X_DISPLAY) || (y >= SIZE_Y_DISPLAY)) {
        vga_error();
        return;
    }
    carriage.x = x;
    carriage.y = y;
}

u32 carriage_get_position() {
    return (((u32) carriage.x) << 16 ) | carriage.y;
}

void carriage_shift_up_line() {
    vga_scroll_line(0);
}

void carriage_shift_down_line() {
    vga_scroll_line(1);
}

void vga_init() {
    vga_clear_screen();
}

void vga_clear_screen() {
    for (unsigned long i = START_DISPLAY_ADDRESS; i < END_DISPLAY_ADDRESS; i += 2) {
        *((u16*) i) = black_f + black_b;
    }
    carriage.x = 0;
    carriage.y = 0;
    carriage.now_char = 0;
}

void vga_print_char(char sym, color_front front, color_back back, u16 x, u16 y) {
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
            *((u16*) pos) = (front + back + (u16)sym);
            carriage_inc();
        }
    }
}

void vga_scroll_line(char flag_down) {
    i16 step = (flag_down ? SIZE_X_DISPLAY : -SIZE_X_DISPLAY);
    u16 start_coord = (flag_down ? 0 : SIZE_X_DISPLAY * (SIZE_Y_DISPLAY - 1));
    u16 end_coord = (flag_down ? SIZE_X_DISPLAY * (SIZE_Y_DISPLAY - 1) : 0);

    for (i32 j = 0; j < SIZE_X_DISPLAY; ++j) {
        u16* input_address = (u16*)(START_DISPLAY_ADDRESS + 2 * (start_coord + j));
        u16* output_address = input_address + step;
        for (i32 i = 0; i < SIZE_Y_DISPLAY - 1; ++i) {
            *input_address = *output_address;
            input_address = output_address;
            output_address += step; // !!!
        }
    }

    for (i32 j = 0; j < SIZE_X_DISPLAY; ++j) {
        *(u16*)(START_DISPLAY_ADDRESS + 2 * (end_coord + j)) = black_f + black_f;
    }
}

void vga_error() {
    *((i16*) 0xB8000) = 0x4F00 + (i32) 'E';
    *((i16*) 0xB8002) = 0x4F00 + (i32) 'R';
    *((i16*) 0xB8004) = 0x4F00 + (i32) 'R';
    *((i16*) 0xB8006) = 0x4F00 + (i32) 'O';
    *((i16*) 0xB8008) = 0x4F00 + (i32) 'R';
}
