//
// Created by modnick on 28.10.2024 and Anqeliccom on 30.12.2024
//
#include "headers/printf.h"
#include "headers/va_list.h"
#include "headers/vga_driver.h"

void print_fyr(char* str, ...) {
    va_list list;
    va_start(list, str);
    for (int i = 0; str[i] != 0; ++i) {
        if (str[i] == '%') {
            i++;
            switch (str[i]) {
                case 'd': {
                    int number = va_arg(list, int);
                    print_int(number);
                    break;
                }
                case 'x': {
                    int number = va_arg(list, int);
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

void print_int(int number) {
    if (number < 0) {
        vga_print_char_carriage('-', white_f, black_b);
        number = -number;
    }

    if (number == 0) {
        vga_print_char_carriage('0', white_f, black_b);
        return;
    }

    char buffer[10];
    int i = 0;

    while (number > 0) {
        buffer[i++] = (char)((number % 10) + '0');
        number /= 10;
    }

    for (int j = i - 1; j >= 0; j--) {
        vga_print_char_carriage(buffer[j], white_f, black_b);
    }
}

void print_hex(int number) {
    if (number < 0) {
        vga_print_char_carriage('-', white_f, black_b);
        number = -number;
    }

    vga_print_char_carriage('0', white_f, black_b);
    vga_print_char_carriage('x', white_f, black_b);

    if (number == 0) {
        vga_print_char_carriage('0', white_f, black_b);
        return;
    }

    char buffer[8];
    int i = 0;

    while (number > 0) {
        int remainder = number % 16;
        buffer[i++] = (char)(remainder < 10 ? remainder + '0' : remainder - 10 + 'a');
        number /= 16;
    }

    for (int j = i - 1; j >= 0; j--) {
        vga_print_char_carriage(buffer[j], white_f, black_b);
    }
}

void print_str(char *str) {
    for (int i = 0; str[i] != 0; ++i) {
        vga_print_char_carriage(str[i], white_f, black_b);
    }
}
