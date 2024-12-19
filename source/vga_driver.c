//
// Created by modnick on 25.10.2024.
// Update by RostyanYandexLyceumCheeeeck on 01.11.2024.
//

#include "headers/vga_driver.h"
#include "headers/kernel_allocator.h"

carriage carriage_kernel;
u16 GLOBAL_QWE = 0;

window window_create() {
    window wind;
    u16* display = NULL;
    while (display == NULL) display = (u16*) kernel_calloc(SIZE_X_DISPLAY * SIZE_Y_DISPLAY, sizeof(u16));

    wind.x = WINDOW_MIN_X;
    wind.y = WINDOW_MIN_Y;
    wind.size_x = WINDOW_MAX_SIZE_X;
    wind.size_y = WINDOW_MAX_SIZE_Y;
//    wind.carriage_window = (carr) {0, 0, 0};
    wind.frame_window = (frame) {'#', green_f, gray_b, FRAME_MIN_WIDTH};
    wind.open = TRUE;
    wind.display = display;

    window_draw_frame(&wind);
    return wind;
}

void carriage_inc() {
    carriage_kernel.x++;
    carriage_kernel.y += carriage_kernel.x / SIZE_X_DISPLAY;
    carriage_kernel.x %= SIZE_X_DISPLAY;

    while (carriage_kernel.y >= SIZE_Y_DISPLAY) {
        carriage_kernel.y--;
        carriage_shift_down_line();
    }
}

void window_carriage_inc(window* wind) {
    wind->carriage_window.x++;
    wind->carriage_window.y += wind->carriage_window.x / wind->size_x;
    wind->carriage_window.x %= wind->size_x;

    while (wind->carriage_window.y >= wind->size_y) {
        window_carriage_shift_down_line(wind);
//        wind->carriage_window.y--;
    }
}

void carriage_shift(i32 shift) {
    if ( shift < 0) {
        i32 x_temp = (i32) carriage_kernel.x + shift % SIZE_X_DISPLAY;
        i32 y_temp = (i32) carriage_kernel.y + shift / SIZE_X_DISPLAY - (i32)(x_temp < 0);

        carriage_kernel.y = (u16)(y_temp < 0 ? 0 : y_temp);
        carriage_kernel.x = (u16)(x_temp < 0 ? SIZE_X_DISPLAY + x_temp : x_temp);
        carriage_kernel.x = (u16)(y_temp < 0 ? 0 : carriage_kernel.x);
    } else {
        carriage_kernel.x += shift - 1;
        carriage_inc();
    }
}

void window_carriage_shift(window* wind, i32 shift) {
    if ( shift < 0) {
        i32 x_temp = (i32) wind->carriage_window.x + shift % wind->size_x;
        i32 y_temp = (i32) wind->carriage_window.y + shift / wind->size_x - (i32)(x_temp < 0);

        wind->carriage_window.y = (u16)(y_temp < 0 ? 0 : y_temp);
        wind->carriage_window.x = (u16)(x_temp < 0 ? wind->size_x + x_temp : x_temp);
        wind->carriage_window.x = (u16)(y_temp < 0 ? 0 : wind->carriage_window.x);
    } else {
        wind->carriage_window.x += shift - 1;
        window_carriage_inc(wind);
    }
}

void carriage_dec() {
    if (!carriage_kernel.x && !carriage_kernel.y) {
        return;
    }
    carriage_kernel.y -= (carriage_kernel.x == 0 && carriage_kernel.y);
    carriage_kernel.x = (carriage_kernel.x ? carriage_kernel.x : SIZE_X_DISPLAY) - 1;
}

void window_carriage_dec(window* wind) {
    if ((!wind->carriage_window.x) && (!wind->carriage_window.y)) {
        return;
    }
    wind->carriage_window.y -= (wind->carriage_window.x == 0 && wind->carriage_window.y);
    wind->carriage_window.x = (wind->carriage_window.x ? wind->carriage_window.x : wind->size_x) - 1;
}

void carriage_start_line() {
    carriage_kernel.x = 0;
}

void window_carriage_start_line(window* wind) {
    wind->carriage_window.x = 0;
}

void carriage_new_line() {
    carriage_kernel.x--;
    carriage_kernel.y++;
    carriage_inc();
}

void window_carriage_new_line(window* wind) {
    wind->carriage_window.x--;
    wind->carriage_window.y++;
    window_carriage_inc(wind);
}

void carriage_set_position(u16 x, u16 y) {
    if ((x >= SIZE_X_DISPLAY) || (y >= SIZE_Y_DISPLAY)) {
        vga_error();
        return;
    }
    carriage_kernel.x = x;
    carriage_kernel.y = y;
}

void window_carriage_set_position(window* wind, u16 x, u16 y) {
    if ((x >= wind->size_x) || (y >= wind->size_y)) {
//        vga_error();
//        1/0;
        return;
    }
    wind->carriage_window.x = x;
    wind->carriage_window.y = y;
}

u32 carriage_get_position() {
    return (((u32) carriage_kernel.x) << 16 ) | carriage_kernel.y;
}

u32 window_carriage_get_position(window* wind) {
    return (((u32) wind->carriage_window.x) << 16 ) | wind->carriage_window.y;
}

void carriage_shift_up_line() {
    vga_scroll_line(0);
}

void window_carriage_shift_up_line(window* wind) {
    window_vga_scroll_line(wind, 0);
}

void carriage_shift_down_line() {
    vga_scroll_line(1);
}

void window_carriage_shift_down_line(window* wind) {
    window_vga_scroll_line(wind, 1);
}

void vga_init() {
    vga_clear_screen();
}

void window_vga_init(window* wind) {
    window_vga_clear_screen(wind);
}

void vga_clear_screen() {
    for (unsigned long i = START_DISPLAY_ADDRESS; i < END_DISPLAY_ADDRESS; i += 2) {
        *((u16*) i) = black_f + black_b;
    }
    carriage_kernel.x = 0;
    carriage_kernel.y = 0;
    carriage_kernel.now_char = 0;
}

void window_clear_screen(window* wind) {
    for (u16 i = wind->y; i < wind->size_y + wind->y; i++) {
        for (u16 j = wind->x; j < wind->size_x + wind->x; j++) {
            wind->display[i * SIZE_X_DISPLAY + j] = ' ' + black_f + black_b;
        }
    }

    window_carriage_set_position(wind, 0, 0);
    wind->carriage_window.now_char = 0;
    window_vga_clear_screen(wind);
}

void window_vga_clear_screen(window* wind) {
    if (!wind->open) {
        return;
    }
    for (u16 i = wind->y; i < wind->size_y + wind->y; i++) {
        for (u16 j = wind->x; j < wind->size_x + wind->x; j++) {
            *((u16*)(START_DISPLAY_ADDRESS + SIZE_X_DISPLAY * 2 * i + 2* j)) = ' ' + black_f + black_b;
        }
    }

    window_carriage_set_position(wind, 0, 0);
    wind->carriage_window.now_char = 0;
}

void vga_print_char(char sym, color_front front, color_back back, u16 x, u16 y) {
    carriage_set_position(x, y);
    vga_print_char_carriage(sym, front, back);
}

void window_vga_print_char(window* wind, byte sym, color_front front, color_back back, u16 x, u16 y) {
    window_carriage_set_position(wind, x, y);
    window_vga_print_char_carriage(wind, sym, front, back);
}

void vga_print_char_carriage(char sym, color_front front, color_back back) {
    unsigned long pos = START_DISPLAY_ADDRESS + 2*(SIZE_X_DISPLAY * carriage_kernel.y + carriage_kernel.x);
    switch (sym) {
        case '\t': {
            do {
                vga_print_char_carriage(' ', front, back);
            } while (carriage_kernel.x % 8);
            break;
        }
        case '\r': {
            carriage_start_line();
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

void window_vga_print_char_carriage(window* wind, byte sym, color_front front, color_back back) {
    u16 frame_width = wind->frame_window.width;
    u32 pos_carr =  wind->carriage_window.y * SIZE_X_DISPLAY + wind->carriage_window.x;
    u32 pos_vga = 2 * (pos_carr + (wind->y) * SIZE_X_DISPLAY + wind->x) + START_DISPLAY_ADDRESS;
    u16 res = (front | back | (u16)sym);
    switch (sym) {
        case '\t': {
            do {
                window_vga_print_char_carriage(wind, ' ', front, back);
            } while (wind->carriage_window.x % 8);
            break;
        }
        case '\r': {
            window_carriage_start_line(wind);
            break;
        }
        case '\n': {
            window_carriage_new_line(wind);
            break;
        }
        case '\0': {
            break;
        }
        default: {
            *((u16*) pos_vga) = res;
            wind->display[pos_carr] = res;
            window_carriage_inc(wind);
            break;
        }
    }
}

void vga_scroll_line(byte flag_down) {
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
    carriage_set_position(0, SIZE_Y_DISPLAY - 1);
}

void window_vga_scroll_line(window* wind, byte flag_down) {
    i16 step = (flag_down ? SIZE_X_DISPLAY : -SIZE_X_DISPLAY);
    u16 last_window_y = wind->y + wind->size_y - 1;
    u16 last_window_x = wind->x;
    u16 start_coord = (flag_down ? wind->y * SIZE_X_DISPLAY + wind->x : SIZE_X_DISPLAY * last_window_y + last_window_x);
    u16 end_coord = (flag_down ? SIZE_X_DISPLAY * last_window_y + last_window_x : wind->y * SIZE_X_DISPLAY + wind->x);

    for (i32 j = 0; j < wind->size_x; j++) {
        u16* input_address = (u16*)(START_DISPLAY_ADDRESS + 2 * (start_coord + j));
        u16* output_address = input_address + step;
        u16 first_address = (flag_down ? 0 : wind->size_y - 1) * SIZE_X_DISPLAY + j;
        for (i32 i = 0; i < wind->size_y - 1; i++) {
            wind->display[first_address] = wind->display[first_address + step];
            first_address += step;
            *input_address = *output_address;
            input_address = output_address;
            output_address += step; // !!!
        }
    }

    u16 first_address = (flag_down ? (wind->size_y - 1) : 0) * SIZE_X_DISPLAY;
    for (i32 j = 0; j < wind->size_x; ++j) {
        *(u16*)(START_DISPLAY_ADDRESS + 2 * (end_coord + j)) = black_b + black_f;
        wind->display[first_address + j] = ' ' + black_b + black_f;
    }
    window_carriage_set_position(wind, 0, wind->size_y - 1);
}

void vga_error() {
    *((i16*) 0xB8000) = 0x4F00 + (i32) 'E';
    *((i16*) 0xB8002) = 0x4F00 + (i32) 'R';
    *((i16*) 0xB8004) = 0x4F00 + (i32) 'R';
    *((i16*) 0xB8006) = 0x4F00 + (i32) 'O';
    *((i16*) 0xB8008) = 0x4F00 + (i32) 'R';
}

void window_set_position(window* wind, u16 pos_y, u16 pos_x) {
    if (!(pos_y < SIZE_Y_DISPLAY && pos_x < SIZE_X_DISPLAY)) {
        return;
    }
    if (!wind->open) {
        wind->y = pos_y;
        wind->x = pos_x;
        return;
    }
    window_close(wind);
    wind->y = pos_y;
    wind->x = pos_x;
    window_open(wind);
}

u32 window_get_position(window* wind) {
    return (((u32)wind->x) << 16) + wind->y;
}

void window_show(window* wind) {
    if (!wind->open) {
        return;
    }
    u32 coords = window_carriage_get_position(wind);
    u16 copy_now_char = wind->carriage_window.now_char;
    window_carriage_set_position(wind, 0, 0);
    for (u16 i = 0; i < wind->size_y; i++) {
        for (u16 j = 0; j < wind->size_x; j++) {
            u16 data = wind->display[i * SIZE_X_DISPLAY + j];
            *(u16*)(START_DISPLAY_ADDRESS + (2*i + 2*wind->y) * SIZE_X_DISPLAY + 2*j + 2*wind->x) = (data & 0xF0FF) | (blue_f + (GLOBAL_QWE << 8));
        }
    }
    GLOBAL_QWE++;
    window_carriage_set_position(wind, coords >> 16, coords);
    wind->carriage_window.now_char = copy_now_char;
    window_draw_frame(wind);
}

void window_open(window* wind) {
    wind->open = TRUE;
    window_show(wind);
}

void window_close(window* wind) {
    carriage copy_carr = wind->carriage_window;
    window_vga_clear_screen(wind);
    window_close_frame(wind);

    wind->carriage_window = copy_carr;
    wind->open = FALSE;
}

void window_resize_x(window* wind, u16 resize) {
    u16 new_size = wind->size_x + resize;
    u16 frame_width = wind->frame_window.width;

    new_size = ((new_size >= (1<<15)) ? WINDOW_MIN_SIZE_X : new_size);
    new_size = MIN(new_size, SIZE_X_DISPLAY - wind->x - frame_width);
    new_size = MAX(new_size, WINDOW_MIN_SIZE_X);

    if (!wind->open) {
        wind->size_x = new_size;
        return;
    }
    window_close(wind);
    wind->size_x = new_size;
    window_open(wind);
 }

void window_resize_y(window* wind, u16 resize) {
    u16 new_size = wind->size_y + resize;
    u16 frame_width = wind->frame_window.width;

    new_size = ((new_size >= (1<<15)) ? WINDOW_MIN_SIZE_Y : new_size);
    new_size = MIN(new_size, SIZE_Y_DISPLAY - wind->y - frame_width);
    new_size = MAX(new_size, WINDOW_MIN_SIZE_Y);

    if (!wind->open) {
        wind->size_y = new_size;
        return;
    }
    window_close(wind);
    wind->size_y = new_size;
    window_open(wind);
}

void window_draw_frame(window* wind) {
    if ((!wind->open) || (!wind->frame_window.width)) {
        return;
    }

    u16 width_frame = wind->frame_window.width;
    u16 save_now_char = wind->carriage_window.now_char;
    u32 save_coord = window_carriage_get_position(wind);

    for (u16 i = 0; i < wind->size_x + 2*width_frame; i++) {
        for (u16 j = 1; j < width_frame; j++) {
            vga_print_char(wind->frame_window.symbol, wind->frame_window.front, wind->frame_window.back,
                           wind->x + i - width_frame,
                           wind->y - width_frame + j); // top
            vga_print_char(wind->frame_window.symbol, wind->frame_window.front, wind->frame_window.back,
                           wind->x + i - width_frame,
                           wind->y + wind->size_y + width_frame - j - 1); // bot
        }
    }

    for (u16 i = 0; i < wind->size_y + 2*width_frame; i++) {
        for (u16 j = 1; j < width_frame; j++) {
            vga_print_char(wind->frame_window.symbol, wind->frame_window.front, wind->frame_window.back,
                           wind->x - width_frame + j,
                           wind->y + i - width_frame);  // left column
            vga_print_char(wind->frame_window.symbol, wind->frame_window.front, wind->frame_window.back,
                           wind->x + wind->size_x + width_frame - j - 1,
                           wind->y + i - width_frame); // right column
        }
    }

    // заполняем линии
    for (u16 i = 0; i < wind->size_x; i++) {
        vga_print_char(wind->frame_window.symbol, wind->frame_window.front, wind->frame_window.back,
                       wind->x + i,
                       wind->y - width_frame); // top
        vga_print_char(wind->frame_window.symbol, wind->frame_window.front, wind->frame_window.back,
                       wind->x + i,
                       wind->y + wind->size_y + width_frame - 1); // bot
    }
    for (u16 i = 0; i < wind->size_y; i++) {
        vga_print_char(wind->frame_window.symbol, wind->frame_window.front, wind->frame_window.back,
                       wind->x - width_frame,
                       wind->y + i); // left
        vga_print_char(wind->frame_window.symbol, wind->frame_window.front, wind->frame_window.back,
                       wind->x + wind->size_x + width_frame - 1,
                       wind->y + i); // right
    }

    // четыре недостающих угла
    u16 res = wind->frame_window.symbol | wind->frame_window.front | wind->frame_window.back;
    *((u16*) START_DISPLAY_ADDRESS + wind->x - width_frame + SIZE_X_DISPLAY * (wind->y - width_frame)) = res;
    *((u16*) START_DISPLAY_ADDRESS + wind->x - width_frame + SIZE_X_DISPLAY * (wind->y + wind->size_y + width_frame - 1)) = res;
    *((u16*) START_DISPLAY_ADDRESS + wind->x + wind->size_x + width_frame - 1 + SIZE_X_DISPLAY * (wind->y - width_frame)) = res;
    *((u16*) START_DISPLAY_ADDRESS + wind->x + wind->size_x + width_frame - 1 + SIZE_X_DISPLAY * (wind->y + wind->size_y + width_frame - 1)) = res;

    window_carriage_set_position(wind, save_coord >> 16, save_coord);
    wind->carriage_window.now_char = save_now_char;
}

void window_close_frame(window* wind) {
    if  ((!wind->open) || (!wind->frame_window.width)) {
        return;
    }
    frame copy_frame = wind->frame_window;
    wind->frame_window = (frame) {' ', black_f, black_b, copy_frame.width};
    window_draw_frame(wind);
    wind->frame_window = copy_frame;
}

void window_delete_frame(window* wind) {
    window_close_frame(wind);
    wind->frame_window = (frame) {' ', black_f, black_b, 0};
}