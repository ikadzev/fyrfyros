//
// Created by modnick on 28.10.2024 and Anqeliccom on 30.12.2024, 24.11.2024
//
#include "headers/printf.h"
#include "headers/va_list.h"
#include "headers/vga_driver.h"

void print_fyr(char* str, ...) {
    va_list list;
    va_start(list, str);
    for (i32 i = 0; str[i] != 0; ++i) {
        if (str[i] == '%') {
            i++;
            switch (str[i]) {
                case 'd': {
                    i32 number = va_arg(list, i32);
                    print_int(number);
                    break;
                }
                case 'x': {
                    i32 number = va_arg(list, i32);
                    print_hex(number);
                    break;
                }
                case 's': {
                    char* string = va_arg(list, char*);
                    print_str(string);
                    break;
                }
                case '%': {
                    vga_print_char_carriage('%', white_f, black_b);
                    break;
                }
            }
        } else {
            vga_print_char_carriage(str[i], white_f, black_b);
        }
    }
}

void print_int(i32 number) {
    if (number < 0) {
        vga_print_char_carriage('-', white_f, black_b);
        number = -number;
    }

    if (number == 0) {
        vga_print_char_carriage('0', white_f, black_b);
        return;
    }

    char buffer[10];
    i32 i = 0;

    while (number > 0) {
        buffer[i++] = (char)((number % 10) + '0');
        number /= 10;
    }

    for (i32 j = i - 1; j >= 0; j--) {
        vga_print_char_carriage(buffer[j], white_f, black_b);
    }
}

void print_hex(i32 number) {
    if (number < 0) {
        vga_print_char_carriage('-', white_f, black_b);
        number = -number;
    }

    vga_print_char_carriage('0', white_f, black_b);
    vga_print_char_carriage('x', white_f, black_b);

    char buffer[8] = {'0', '0', '0', '0', '0', '0', '0', '0'};
    i32 i = 0;

    while (number > 0) {
        i32 remainder = number % 16;
        buffer[i++] = (char)(remainder < 10 ? remainder + '0' : remainder - 10 + 'A');
        number /= 16;
    }

    i = 8;
    for (i32 j = i - 1; j >= 0; j--) {
        vga_print_char_carriage(buffer[j], white_f, black_b);
    }
}

void print_unsigned_hex(i32 number) {
    u32 unsigned_number = (u32)number;

    vga_print_char_carriage('0', white_f, black_b);
    vga_print_char_carriage('x', white_f, black_b);

    if (unsigned_number == 0) {
        vga_print_char_carriage('0', white_f, black_b);
        return;
    }

    char buffer[8] = {'0', '0', '0', '0', '0', '0', '0', '0'};
    i32 i = 0;

    while (unsigned_number > 0) {
        u32 remainder = unsigned_number % 16;
        buffer[i++] = (char)(remainder < 10 ? remainder + '0' : remainder - 10 + 'A');
        unsigned_number /= 16;
    }

    i = 8;
    for (i32 j = i - 1; j >= 0; j--) {
        vga_print_char_carriage(buffer[j], white_f, black_b);
    }
}

void print_str(char *str) {
    for (i32 i = 0; str[i] != 0; ++i) {
        vga_print_char_carriage(str[i], white_f, black_b);
    }
}
