//
// Created by modnick on 28.10.2024.
//

#ifndef FYRFYROS_PRINTF_H
#define FYRFYROS_PRINTF_H

#include "macroses.h"
#include "vga_driver.h"

void print_fyr(char* str, ...);
void print_int(i32 number);
void print_hex(i32 number);
void print_unsigned_hex(i32 number);
void print_str(char *anInt);

void window_print_fyr(window* wind, char* str, ...);
void window_print_int(window* wind, i32 number);
void window_print_hex(window* wind, i32 number);
void window_print_unsigned_hex(window* wind, i32 number);
void window_print_str(window* wind, char *anInt);

#endif //FYRFYROS_PRINTF_H
