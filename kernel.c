#include "source/headers/vga_driver.h"
#include "source/headers/va_list.h"
#include "source/headers/printf.h"

void test(int, ...);

void kernel_entry() {
    vga_init();
    //print_int(12);
    //print_int(345);
    //print_int(6789);
    print_fyr("test %d and %d %d and   m\0", 1666, 45, 34);
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
