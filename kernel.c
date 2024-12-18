#include "source/headers/vga_driver.h"
#include "source/headers/printf.h"
#include "source/headers/kernel_allocator.h"
#include "source/headers/tramplins.h"
#include "source/headers/intel8259A.h"
#include "source/headers/handler_interupt.h"
#include "source/headers/page_translator.h"
#include "source/headers/page_allocator.h"
#include "source/headers/floppy_driver.h"

void print_logo();

void kernel_entry() {
    cli();
    kernel_start_allocator();
    page_start_allocator();
    init_virtual_address();
    create_lidt();
    configure_intel8258A_all();
    vga_clear_screen();
    //floppy_print_MSR();
    //floppy_print_DOR();
    sti();
    floppy_init();
    floppy_motor_start(0);
    //floppy_print_DOR();
    //floppy_print_MSR();
    byte * r = (byte *)0x1000;
    r[0] = 0x11;
    r = flpydsk_read_sector(1);
    print_hex((u32)r);
    for (int i = 0; i < 10; ++i) {
        print_unsigned_hex(r[i]);
    }
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