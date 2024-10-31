#include "source/headers/vga_driver.h"
#include "source/headers/va_list.h"
#include "source/headers/printf.h"

void test(int, ...);

void kernel_entry() {
    vga_init();
    //print_int(12);
    //print_int(345);
    //print_int(6789);
    // "test %d and %d %d and   m\0"
    print_fyr("test %d and %d %d and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234502 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234503 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234504 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234505 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234506 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234507 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234508 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234509 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234510 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234511 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234512 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234513 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234514 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234515 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234516 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234517 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234518 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234519 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234520 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234521 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234522 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234523 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvvv"
              "\n\n12345678901234524 and  kffsdsfnnfsfsnfddfdsfsfdsktvjbkdvrg r vfgkvgkvg kv vvv"
              "\0", 1666, 45, 34);
//    vga_shift_up_line();
    carriage_inc();

    for (;;);
}

void test(int n, ...){
    va_list te;
    va_start(te, n);
    for (int i = 0; i < n; ++i) {
        char y = va_arg(te, char);
        vga_print_char(y, white_f,  black_b, 0,0);
    }
}
