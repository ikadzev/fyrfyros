#include "source/headers/vga_driver.h"
#include "source/headers/printf.h"
#include "source/headers/kernel_allocator.h"
#include "source/headers/tramplins.h"
#include "source/headers/intel8259A.h"
#include "source/headers/handler_interupt.h"
#include "source/headers/page_translator.h"
#include "source/headers/page_allocator.h"

void print_logo();

void window_test_resize_x();
void window_test_resize_y();
void window_test_resize_all();

void window_test_frame_1();
void window_test_frame_2();
void window_test_frame_all();

void window_print_logo(window* wind);

#define sleep(n) for (int j = 0; j < n; j++) for (int i = 0; i < 200000000; i++);

void kernel_entry() {
    cli();
    kernel_start_allocator();
    page_start_allocator();
    init_virtual_address();
    create_lidt();
    configure_intel8258A_all();
    vga_clear_screen();
    sti();
    window_test_frame_all();
    for (;;);
}

void print_logo() {
    vga_clear_screen();
    print_fyr(
            "\r\n"
            "\r\n"
            "                                        *@%%,                             \r\n"
            "                                *&&@@&@&**&@@@&(  &&&                    \r\n"
            "                       #&&&&&&&@@%%*,&&@@@@@@@@@@@&&@@@@&                 \r\n"
            "                           (&@@@@@@@@@@@@@@@@@@@@@@@@@@@@&%%              \r\n"
            "                 %%&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@&@%%((%%@@&&&&&&@@&     \r\n"
            "                    #&@@@@@@@@@@@@@@@@@@@@@@@@@@&/       **     //%%@&\\   \r\n"
            "                *&@&&@@@@@@@@@@@@@@@@@@@@@@@@@@@&/       @@@        *&&  \r\n"
            "          *@&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&*                  %%&#   \r\n"
            "       %%&&&@&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&                 /&@    \r\n"
            "            &&@@@@@@@@@@@@@@@@@@@@@@@@@&&.    .&&%%              &@&*     \r\n"
            "         &&@@@@@@@@@@@@@@@@@@@@@@@@@&(            .         #&@&/        \r\n"
            "     .&@@@@@@@@@@@@@@@@@@@@@@@@@@@                    *@&@@*             \r\n"
            "     @&&&&&@@@@@@@@@%%**@@@@@@@@&&                  #@@@#                 \r\n"
            "          &@@@@@&,      @@@@@@.                .@@@&                     \r\n"
            "        /&@@@@@*       &&#,                  #@&(@@                      \r\n"
            "        @@@@@@&,                            ,&@  &&/                     \r\n"
            "      @@&,@@@#          @&&@@@&&%%         #@%%   @&                       \r\n"
            "          @&&,      .@@@   &&*  &&&.     /&@    @&                       \r\n"
            "           @&*    ,&@@,   &&*     #@@    @@&/  ,@@                       \r\n"
            "            &@@&&@&/ /&@&&%%         @@@@@@  &&@&&     ");
}

void window_print_logo(window* wind) {
    window_vga_clear_screen(wind);
    window_print_fyr(wind,
                     "0023456789abcdefghij9876543210qwertyuio0023456789abcdefghij9876543210qwertyuiop\r\n"
                     "0123456789abcdefghij9876543210qwertyuio0123456789abcdefghij9876543210qwertyuiop\r\n"
                     "0223456789abcdefghij9876543210qwertyuio0223456789abcdefghij9876543210qwertyuiop\r\n"
                     "0323456789abcdefghij9876543210qwertyuio0323456789abcdefghij9876543210qwertyuiop\r\n"
                     "0423456789abcdefghij9876543210qwertyuio0423456789abcdefghij9876543210qwertyuiop\r\n"
                     "0523456789abcdefghij9876543210qwertyuio0523456789abcdefghij9876543210qwertyuiop\r\n"
                     "0623456789abcdefghij9876543210qwertyuio0623456789abcdefghij9876543210qwertyuiop\r\n"
                     "0723456789abcdefghij9876543210qwertyuio0723456789abcdefghij9876543210qwertyuiop\r\n"
                     "0823456789abcdefghij9876543210qwertyuio0823456789abcdefghij9876543210qwertyuiop\r\n"
                     "0923456789abcdefghij9876543210qwertyuio0923456789abcdefghij9876543210qwertyuiop\r\n"
                     "1023456789abcdefghij9876543210qwertyuio1023456789abcdefghij9876543210qwertyuiop\r\n"
                     "1123456789abcdefghij9876543210qwertyuio1123456789abcdefghij9876543210qwertyuiop\r\n"
                     "1223456789abcdefghij9876543210qwertyuio1223456789abcdefghij9876543210qwertyuiop\r\n"
                     "1323456789abcdefghij9876543210qwertyuio1323456789abcdefghij9876543210qwertyuiop\r\n"
                     "1423456789abcdefghij9876543210qwertyuio1423456789abcdefghij9876543210qwertyuiop\r\n"
                     "1523456789abcdefghij9876543210qwertyuio1523456789abcdefghij9876543210qwertyuiop\r\n"
                     "1623456789abcdefghij9876543210qwertyuio1623456789abcdefghij9876543210qwertyuiop\r\n"
                     "1723456789abcdefghij9876543210qwertyuio1723456789abcdefghij9876543210qwertyuiop\r\n"
                     "1823456789abcdefghij9876543210qwertyuio1823456789abcdefghij9876543210qwertyuiop\r\n"
                     "1923456789abcdefghij9876543210qwertyuio1923456789abcdefghij9876543210qwertyuiop\r\n"
                     "2023456789abcdefghij9876543210qwertyuio2023456789abcdefghij9876543210qwertyuiop\r\n"
                     "2123456789abcdefghij9876543210qwertyuio2123456789abcdefghij9876543210qwertyuiop\r\n"
                     "2223456789abcdefghij9876543210qwertyuio2223456789abcdefghij9876543210qwertyuiop\r\n"
                     "2323456789abcdefghij9876543210qwertyuio2323456789abcdefghij9876543210qwertyuiop\r\n"
                     "2423456789abcdefghij9876543210qwertyuio2423456789abcdefghij9876543210qwertyuiop\r\n"
                     "2523456789abcdefghij9876543210qwertyuio2523456789abcdefghij9876543210qwertyuiop\r\n"
                     "2623456789abcdefghij9876543210qwertyuio2623456789abcdefghij9876543210qwertyuiop\r\n"
                     "2723456789abcdefghij9876543210qwertyuio2723456789abcdefghij9876543210qwertyuiop\r\n"
                     "2823456789abcdefghij9876543210qwertyuio2823456789abcdefghij9876543210qwertyuiop\r\n"
                     "2923456789abcdefghij9876543210qwertyuio2923456789abcdefghij9876543210qwertyuiop\r\n"
                     "3023456789abcdefghij9876543210qwertyuio3023456789abcdefghij9876543210qwertyuiop\r\n"
                     "3123456789abcdefghij9876543210qwertyuio3123456789abcdefghij9876543210qwertyuiop\r\n"
                     "3223456789abcdefghij9876543210qwertyuio3223456789abcdefghij9876543210qwertyuiop\r\n"
                     "3323456789abcdefghij9876543210qwertyuio3323456789abcdefghij9876543210qwertyuiop\r\n"
                     "3423456789abcdefghij9876543210qwertyuio3423456789abcdefghij9876543210qwertyuiop\r\n"
                     "3523456789abcdefghij9876543210qwertyuio3523456789abcdefghij9876543210qwertyuiop\r\n"
                     "3623456789abcdefghij9876543210qwertyuio3623456789abcdefghij9876543210qwertyuiop\r\n"
                     "3723456789abcdefghij9876543210qwertyuio3723456789abcdefghij9876543210qwertyuiop\r\n"
                     "3823456789abcdefghij9876543210qwertyuio3823456789abcdefghij9876543210qwertyuiop\r\n"
                     "3923456789abcdefghij9876543210qwertyuio3923456789abcdefghij9876543210qwertyuiop\r\n"
                     "4023456789abcdefghij9876543210qwertyuio4023456789abcdefghij9876543210qwertyuiop\r\n"
                     "4123456789abcdefghij9876543210qwertyuio4123456789abcdefghij9876543210qwertyuiop\r\n"
                     "4223456789abcdefghij9876543210qwertyuio4223456789abcdefghij9876543210qwertyuiop\r\n"
                     "4323456789abcdefghij9876543210qwertyuio4323456789abcdefghij9876543210qwertyuiop\r\n"
                     "4423456789abcdefghij9876543210qwertyuio4423456789abcdefghij9876543210qwertyuiop\r\n"
                     "4523456789abcdefghij9876543210qwertyuio4523456789abcdefghij9876543210qwertyuiop\r\n"
                     "4623456789abcdefghij9876543210qwertyuio4623456789abcdefghij9876543210qwertyuiop\r\n"
                     "4723456789abcdefghij9876543210qwertyuio4723456789abcdefghij9876543210qwertyuiop\r\n"
                     "4823456789abcdefghij9876543210qwertyuio4823456789abcdefghij9876543210qwertyuiop\r\n"
                     "4923456789abcdefghij9876543210qwertyuio4923456789abcdefghij9876543210qwertyuiop\r\n"
    );
}

void window_print_logo1(window* wind) {
    window_vga_clear_screen(wind);
    window_print_fyr(wind,
            "                                                                             \r\n"
            "                                                                             \r\n"
            "                                        *@%%,                                 \r\n"
            "                                *&&@@&@&**&@@@&(  &&&                        \r\n"
            "                       #&&&&&&&@@%%*,&&@@@@@@@@@@@&&@@@@&                     \r\n"
            "                           (&@@@@@@@@@@@@@@@@@@@@@@@@@@@@&%%                  \r\n"
            "                 %%&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@&@%%((%%@@&&&&&&@@&        \r\n"
            "                    #&@@@@@@@@@@@@@@@@@@@@@@@@@@&/       **     //%%@&\\       \r\n"
            "                *&@&&@@@@@@@@@@@@@@@@@@@@@@@@@@@&/       @@@        *&&      \r\n"
            "          *@&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&*                  %%&#       \r\n"
            "       %%&&&@&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&                 /&@        \r\n"
            "            &&@@@@@@@@@@@@@@@@@@@@@@@@@&&.    .&&%%              &@&*         \r\n"
            "         &&@@@@@@@@@@@@@@@@@@@@@@@@@&(            .         #&@&/            \r\n"
            "     .&@@@@@@@@@@@@@@@@@@@@@@@@@@@                    *@&@@*                 \r\n"
            "     @&&&&&@@@@@@@@@%%**@@@@@@@@&&                  #@@@#                     \r\n"
            "          &@@@@@&,      @@@@@@.                .@@@&                         \r\n"
            "        /&@@@@@*       &&#,                  #@&(@@                          \r\n"
            "        @@@@@@&,                            ,&@  &&/                         \r\n"
            "      @@&,@@@#          @&&@@@&&%%         #@%%   @&                           \r\n"
            "          @&&,      .@@@   &&*  &&&.     /&@    @&                           \r\n"
            "           @&*    ,&@@,   &&*     #@@    @@&/  ,@@                           \r\n"
            "            &@@&&@&/ /&@&&%%         @@@@@@  &&@&&");
}


void window_test_resize_x() {
    window wind = window_create();

    window_print_logo(&wind);
    sleep(1);

    window_resize_x(&wind, -40);
    sleep(2);

    window_print_logo(&wind);
    sleep(3);

    window_set_position(&wind, 0, 40);
    sleep(2);

    window_print_logo(&wind);
    sleep(1);

    window_show(&wind);
    sleep(2);

    window_set_position(&wind, 0, 0);
    sleep(3);

    window_show(&wind);
    sleep(1);

    window_show(&wind);
    sleep(1);

    window_show(&wind);
    sleep(3);

    window_resize_x(&wind, 40);
    sleep(3);

    window_print_logo(&wind);
    sleep(2);
}

void window_test_resize_y() {
    window wind = window_create();

    window_print_logo(&wind);
    sleep(1);

    window_resize_y(&wind, -13);
    sleep(1);

    window_print_logo(&wind);
    sleep(1);

    window_set_position(&wind, 13, 0);
    sleep(1);

    window_print_logo(&wind);
    sleep(1);

    window_show(&wind);
    sleep(1);

    window_set_position(&wind, 0, 0);
    sleep(3);

    window_show(&wind);
    sleep(1);

    window_show(&wind);
    sleep(1);

    window_show(&wind);
    sleep(3);

    window_resize_y(&wind, 13);
    sleep(2);

//    window_vga_print_char(&wind, 'Q', red_f, green_b, 0, SIZE_Y_DISPLAY - 1);
//    window_vga_print_char(&wind, 'W', red_f, green_b, 1, SIZE_Y_DISPLAY - 1);
//    window_vga_print_char(&wind, 'E', red_f, green_b, 2, SIZE_Y_DISPLAY - 1);

    window_print_logo(&wind);
}

void window_test_resize_all() {
    window_test_resize_x();
    window_test_resize_y();
}

void window_test_frame_1() {
    window wind = window_create();

    window_print_logo(&wind);
    sleep(1);

    window_resize_x(&wind, -40);
    sleep(1);

    window_print_logo(&wind);
    sleep(2);

    window_set_position(&wind, FRAME_MIN_WIDTH, 40 + FRAME_MIN_WIDTH);
    sleep(3);

    window_print_logo(&wind);
    sleep(1);

    window_show(&wind);
    sleep(1);

    window_set_position(&wind, FRAME_MIN_WIDTH, FRAME_MIN_WIDTH);
    sleep(3);

    window_show(&wind);
    sleep(1);

    window_show(&wind);
    sleep(1);

    window_show(&wind);
    sleep(3);

    window_resize_x(&wind, 40);
    sleep(3);

    window_print_logo(&wind);
}

void window_test_frame_2() {
        window wind = window_create();

        window_print_logo(&wind);
        sleep(1);

        window_resize_y(&wind, -13);
        sleep(1);

        window_print_logo(&wind);
        sleep(1);

        window_set_position(&wind, 13 + FRAME_MIN_WIDTH, FRAME_MIN_WIDTH);
        sleep(1);

        window_print_logo(&wind);
        sleep(1);

        window_show(&wind);
        sleep(1);

        window_set_position(&wind, 10, FRAME_MIN_WIDTH);
        sleep(3);

        window_show(&wind);
        sleep(1);

        window_show(&wind);
        sleep(1);

        window_show(&wind);
        sleep(3);

        window_resize_y(&wind, 13);
        sleep(2);

//    window_vga_print_char(&wind, 'Q', red_f, green_b, 0, SIZE_Y_DISPLAY - 1);
//    window_vga_print_char(&wind, 'W', red_f, green_b, 1, SIZE_Y_DISPLAY - 1);
//    window_vga_print_char(&wind, 'E', red_f, green_b, 2, SIZE_Y_DISPLAY - 1);
        window_print_logo(&wind);
}

void window_test_frame_all() {
    window_test_frame_1();
    window_test_frame_2();
}