//
// Created by modnick on 25.10.2024.
//

#ifndef FYRFYROS_VGA_DRIVER_H
#define FYRFYROS_VGA_DRIVER_H

#include "_flags.h"
#include "macroses.h"

#define START_DISPLAY_ADDRESS 0xB8000
#define END_DISPLAY_ADDRESS 0xB8FA0
#define SIZE_X_DISPLAY 80
#define SIZE_Y_DISPLAY 25

#define FRAME_MIN_WIDTH 1
#define WINDOW_MIN_X FRAME_MIN_WIDTH
#define WINDOW_MIN_Y FRAME_MIN_WIDTH
#define WINDOW_MIN_SIZE_X 6
#define WINDOW_MIN_SIZE_Y 1
#define WINDOW_MAX_SIZE_X (SIZE_X_DISPLAY - WINDOW_MIN_X - FRAME_MIN_WIDTH)
#define WINDOW_MAX_SIZE_Y (SIZE_Y_DISPLAY - WINDOW_MIN_Y - FRAME_MIN_WIDTH)
#define WINDOW_MAX_X (SIZE_X_DISPLAY - WINDOW_MIN_SIZE_X)
#define WINDOW_MAX_Y (SIZE_Y_DISPLAY - WINDOW_MIN_SIZE_Y)

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

typedef struct {
    u16 x;
    u16 y;
    u16 now_char;
} carriage;

typedef struct {
    char symbol;
    color_front front;
    color_back back;
    u16 width;
} frame;

typedef struct {
    u16 x;
    u16 y;
    u16 size_x;
    u16 size_y;
    carriage carriage_window;
    frame frame_window;
    byte open;
    u16* display; // [80*25];
} window;

window window_create();

void carriage_inc();                       // сдвигает каретку вправо
void carriage_shift(i32 shift);            // сдвигает каретку на shift вправо
void carriage_dec();                       // сдвигает каретку влево
void carriage_start_line();                // сдвигает каретку в начало строки
void carriage_new_line();                  // переводит каретку на новую строку
void carriage_set_position(u16 x, u16 y);  // задаёт позицию каретки
u32 carriage_get_position();               // выдаёт координаты каретки (старшие 16 бит координаты по х, младшие 16 -- по у).
void carriage_shift_down_line();
void carriage_shift_up_line();

void vga_init();
void vga_clear_screen();
void vga_print_char(char sym, color_front, color_back, u16, u16);
void vga_print_char_carriage(char sym, color_front, color_back);
void vga_scroll_line(byte flag_down);
void vga_error();

void window_carriage_inc(window* wind);                         // сдвигает каретку вправо
void window_carriage_shift(window* wind, i32 shift);            // сдвигает каретку на shift вправо
void window_carriage_dec(window* wind);                         // сдвигает каретку влево
void window_carriage_start_line(window* wind);                  // сдвигает каретку в начало строки
void window_carriage_new_line(window* wind);                    // переводит каретку на новую строку
void window_carriage_set_position(window* wind, u16 x, u16 y);  // задаёт позицию каретки
u32 window_carriage_get_position(window* wind);                 // выдаёт координаты каретки (старшие 16 бит координаты по х, младшие 16 -- по у).
void window_carriage_shift_down_line(window* wind);             //
void window_carriage_shift_up_line(window* wind);


void window_vga_init(window* wind);
void window_clear_screen(window* wind);
void window_vga_clear_screen(window* wind);
void window_vga_print_char(window* wind, byte sym, color_front, color_back, u16, u16);
void window_vga_print_char_carriage(window* wind, byte sym, color_front, color_back);
void window_vga_scroll_line(window* wind, byte flag_down);

void window_set_position(window* wind, u16 pos_y, u16 pos_x);
void window_show(window* wind);
void window_open(window* wind);
void window_close(window* wind);
void window_resize_x(window* wind, u16 resize);
void window_resize_y(window* wind, u16 resize);
void window_draw_frame(window* wind);
void window_close_frame(window* wind);
void window_delete_frame(window* wind);

#endif //FYRFYROS_VGA_DRIVER_H
