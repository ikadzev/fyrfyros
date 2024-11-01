//
// Created by modnick on 25.10.2024.
//

#ifndef FYRFYROS_VGA_DRIVER_H
#define FYRFYROS_VGA_DRIVER_H

#define START_DISPLAY_ADDRESS 0xB8000
#define END_DISPLAY_ADDRESS 0xB8FA0
#define SIZE_X_DISPLAY 80
#define SIZE_Y_DISPLAY 25

typedef enum color_front {
    black_f       = 0x0000,
    blue_f        = 0x0100,
    green_f       = 0x0200,
    cyan_f        = 0x0300,
    red_f         = 0x0400,
    purple_f      = 0x0500,
    brown_f       = 0x0600,
    gray_f        = 0x0700,
    dark_green_f  = 0x0800,
    light_blue_f  = 0x0900,
    light_green_f = 0x0a00,
    light_cyan_f  = 0x0b00,
    light_red_f   = 0x0c00,
    light_purple_f= 0x0d00,
    yellow_f      = 0x0e00,
    white_f       = 0x0f00
} color_front;

typedef enum color_back {
    black_b       = 0x0000,
    blue_b        = 0x1000,
    green_b       = 0x2000,
    cyan_b        = 0x3000,
    red_b         = 0x4000,
    purple_b      = 0x5000,
    brown_b       = 0x6000,
    gray_b        = 0x7000,
} color_back;

void carriage_inc(); // сдвигает каретку вправо
void carriage_shift(int shift); //сдвигает каретку на shift вправо
void carriage_dec(); // сдвигает каретку влево
void carriage_start(); //сдвигает каретку в начало строки
void carriage_new_line(); //переводит каретку на новую строку
void carriage_set_position(unsigned short x, unsigned short y); //задаёт позицию каретки

void vga_init();
void vga_clear_screen();
void vga_print_char(char sym, color_front, color_back, unsigned short, unsigned short);
void vga_print_char_carriage(char sym, color_front, color_back);
void vga_scroll_line(char flag_down);
void vga_shift_down_line();
void vga_shift_up_line();
void vga_error();

#endif //FYRFYROS_VGA_DRIVER_H
