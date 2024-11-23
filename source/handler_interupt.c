//
// Created by modnick on 23.11.2024.
//

#include "headers/handler_interupt.h"

u32 GLOBAL_COUNTER_TIMER = 0;

void interrupt_handler(context* ctx) {
    print_context(ctx);
    switch (ctx->vector) {
        case 0x20:
            timer_interrupt(ctx);
            break;
        default:
            panic_handler(ctx->vector);
            break;
    }
}

void print_context(context* ctx) {
    vga_clear_screen();
    print_fyr("edi: %x\t", ctx->edi);
    print_fyr("esi: %x\t", ctx->esi);
    print_fyr("ebp: %x\t", ctx->ebp);
    print_fyr("esp: %x\r\n", ctx->esp);
    print_fyr("ebx: %x\t", ctx->ebx);
    print_fyr("edx: %x\t", ctx->edx);
    print_fyr("ecx: %x\t", ctx->ecx);
    print_fyr("eax: %x\r\n", ctx->eax);
    print_fyr("gs: %x\t", ctx->gs & 0x00FF);
    print_fyr("fs: %x\t", ctx->fs & 0x00FF);
    print_fyr("es: %x\t", ctx->es & 0x00FF);
    print_fyr("ds: %x\r\n", ctx->ds & 0x00FF);
    print_fyr("vector: %x\t", ctx->vector);
    print_fyr("error code: %x\t", ctx->error_code);
    print_fyr("eip: %x\r\n", ctx->eip);
    print_fyr("cs: %x \r\n", ctx->cs & 0x00FF);
    print_fyr("eflags: %x\r\n", ctx->eflags);
}

void panic_handler(unsigned char vector) {
    vga_init();
    print_fyr("unhandled interrupt %x", vector);
    for (;;) {

    }
}

static void timer_interrupt(context* ctx) {
    //print_int(GLOBAL_COUNTER_TIMER++);
    for (;;) {

    }
}