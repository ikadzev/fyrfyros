#include "source/headers/vga_driver.h"
#include "source/headers/printf.h"
#include "source/headers/kernel_allocator.h"

void print_logo();

void kernel_entry() {
    kernel_start_allocator();
    vga_clear_screen();
    int* t = kernel_malloc(sizeof(int) * 10);
    t[0] = 12;
    t[1] = 13;
    t[2] = 14;
    t[3] = 15;
    t[4] = 16;
    t[5] = 17;
    print_int(*(t++));
    print_int(*(t++));
    print_int(*(t++));
    print_int(*(t++));
    print_int(*(t++));
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