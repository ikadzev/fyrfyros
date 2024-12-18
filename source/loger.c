//
// Created by modnick on 18.12.2024.
//

#include "headers/loger.h"
#include "headers/vga_driver.h"
#include "headers/printf.h"

void log_massage(char* comment_str, u32 hex, byte clear_mode){
#ifdef DEBUG_MODE
    if (clear_mode) {
        vga_clear_screen();
    }
    for (i32 i = 0; comment_str[i] != 0; ++i) {
        vga_print_char_carriage(comment_str[i], light_blue_f, black_b);
    }
    if (hex != -1) {
        print_unsigned_hex(hex);
    }
    print_fyr("\r\n");
#endif
}
void log_warning(char* comment_str, u32 hex, byte clear_mode){
#ifdef DEBUG_MODE
    if (clear_mode) {
        vga_clear_screen();
    }
#endif
    for (i32 i = 0; comment_str[i] != 0; ++i) {
        vga_print_char_carriage(comment_str[i], yellow_f, black_b);
    }
    if (hex != -1) {
        print_unsigned_hex(hex);
    }
    print_fyr("\r\n");
#ifdef DEBUG_MODE
    for(;;);
#endif
}
void log_expression(char* comment_str, u32 hex, byte clear_mode){
    if (clear_mode) {
        vga_clear_screen();
    }
    for (i32 i = 0; comment_str[i] != 0; ++i) {
        vga_print_char_carriage(comment_str[i], red_f, black_b);
    }
    if (hex != -1) {
        print_unsigned_hex(hex);
    }
    print_fyr("\r\n");
    for (;;);
}

void log_massage_cond(byte cond, char* comment_str, u32 hex, byte clear_mode) {
    if (cond) log_massage(comment_str, hex, clear_mode);
}
void log_warning_cond(byte cond, char* comment_str, u32 hex, byte clear_mode) {
    if (cond) log_warning(comment_str, hex, clear_mode);
}
void log_expression_cond(byte cond, char* comment_str, u32 hex, byte clear_mode) {
    if (cond) log_expression(comment_str, hex, clear_mode);
}