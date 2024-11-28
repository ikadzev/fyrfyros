#include "source/headers/vga_driver.h"
#include "source/headers/printf.h"
#include "source/headers/kernel_allocator.h"
#include "source/headers/tramplins.h"
#include "source/headers/intel8259A.h"
#include "source/headers/handler_interupt.h"

void print_logo();


void kernel_entry() {
    cli();
    vga_clear_screen();
    kernel_start_allocator();
    create_lidt();
    configure_intel8258A_all();
    sti();
    int a = 1/0;
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