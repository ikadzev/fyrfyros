#include "source/headers/vga_driver.h"
#include "source/headers/printf.h"
#include "source/headers/kernel_allocator.h"
#include "source/headers/tramplins.h"
#include "source/headers/intel8259A.h"
#include "source/headers/handler_interupt.h"
#include "source/headers/page_translator.h"
#include "source/headers/page_allocator.h"
#include "source/headers/floppy_driver.h"
#include "source/headers/loger.h"

void print_logo();

void kernel_entry() {
    cli();
    kernel_start_allocator();
    page_start_allocator();
    //init_virtual_address();
    create_lidt();
    configure_intel8258A_all();
    vga_clear_screen();
    //floppy_print_MSR();
    //floppy_print_DOR();
    sti();
    floppy_init();
    //log_massage("DONE", -1, 0);
    byte* test = (byte*)0x2000;
    floppy_read_block(38, test, 1);
    floppy_read_block(1, test, 1);
    log_warning("stop", -1,0);
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