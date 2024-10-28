//
// Created by modnick on 28.10.2024.
//

#include "headers/printf.h"
#include "headers/va_list.h"
#include "headers/vga_driver.h"

void print_fyr(char* str, ...) {
    va_list list;
    va_start(list, str);
    for (int i = 0;str[i] != 0; ++i) {
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
            }

        } else {
            vga_print_char_carriage(str[i], white_f, black_b);
        }
    }
}

void print_int(int number) {
    char t[10];
    if (number < 0) {
        vga_print_char_carriage('-', white_f, black_b);
        number *= -1;
    }
    int size = 0;
    int vremen = number;
    while (vremen != 0) {
        vremen = vremen / 10;
        size += 1;
    }
    carriage_shift(size - 1);
    for (int i = 0; i < size; ++i) {
        vga_print_char_carriage((char)(number % 10 + '0'), white_f, black_b);
        carriage_shift(-2);
        number /= 10;
    }
    carriage_shift(size + 1);
}

void print_hex(int number) {
    if (number < 0) {
        vga_print_char_carriage('-', white_f, black_b);
        number *= -1;
    }
    vga_print_char_carriage('0', white_f, black_b);
    vga_print_char_carriage('x', white_f, black_b);
    int size = 0;
    int vremen = number;
    while (vremen != 0) {
        vremen = vremen / 16;
        size += 1;
    }
    carriage_shift(size - 1);
    for (int i = 0; i < size; ++i) {
        char print_ch = (char)(number % 16);
        if (print_ch < 10) {
            print_ch += '0';
        } else {
            print_ch += 'a' - 10;
        }
        vga_print_char_carriage(print_ch, white_f, black_b);
        carriage_shift(-2);
        number /= 16;
    }
}

void print_str(char *anInt) {
    for (int i = 0; anInt[i] != 0; ++i) {
        vga_print_char_carriage(anInt[i], white_f, black_b);
    }
}
