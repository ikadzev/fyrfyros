//
// Created by modnick on 23.11.2024.
//

#include "headers/handler_interupt.h"
#include "headers/intel8259A.h"

u32 GLOBAL_COUNTER_TIMER = 0x0;


void cli() {
    __asm__ __volatile__ (
            ".intel_syntax noprefix\n\t"
            "cli\n\t"
            ".att_syntax prefix\n\t"
            );
}

void sti() {
    __asm__ __volatile__ (
            ".intel_syntax noprefix\n\t"
            "sti\n\t"
            ".att_syntax prefix\n\t"
            );
}

void eoi(enum intel8259_type cont) {
    outb(cont == master ? 0x20 : 0xA0, 0x20);
}

void interrupt_handler(context* ctx) {
    switch (ctx->vector) {
        case 0x20:
            timer_interrupt(ctx);
            eoi(master);
            break;
        default:
            if (ctx->vector < start_vector_master) {
                trap_handler(ctx);
            } else if (ctx->vector < 0x30) {
                if (ctx->vector >= start_vector_slave) {
                    eoi(slave);
                }
                eoi(master);
            }
            panic_handler(ctx);
            break;
    }
}

void trap_handler(context* ctx) {
    print_context(ctx);
    for (;;);
}

void print_context(context* ctx) {
    vga_clear_screen();
    print_fyr("\r\nKernel panic: unhandled interrupt %x, interrupted process context:\r\n", ctx->vector);
    print_fyr("  EAX = %x ", ctx->eax);
    print_fyr("ECX = %x ", ctx->ecx);
    print_fyr("EDX = %x ", ctx->edx);
    print_fyr("EBX = %x\r\n", ctx->ebx);
    print_fyr("  ESP = %x ", ctx->esp);
    print_fyr("EBP = %x ", ctx->ebp);
    print_fyr("ESI = %x ", ctx->esi);
    print_fyr("EDI = %x\r\n", ctx->edi);
    print_fyr("  DS  = %x ", ctx->ds);
    print_fyr("ES  = %x ", ctx->es);
    print_fyr("FS  = %x ", ctx->fs);
    print_fyr("GS  = %x\r\n", ctx->gs);
    print_fyr("  CS  = %x ", ctx->cs);
    print_fyr("EIP = %x ", ctx->eip);
    print_fyr("EFLAGS = %x\r\n", ctx->eflags);
    print_fyr("  error code = %x\r\n", ctx->error_code);
}

void panic_handler(context* ctx) {
    print_context(ctx);
    for (;;);
}

static void timer_interrupt(context* ctx) {
    u32 pos_carr = carriage_get_position();

    u16 len = 1;
    for (u32 i = GLOBAL_COUNTER_TIMER / 10; i > 0; i /= 10) len++;

    carriage_set_position(0, SIZE_Y_DISPLAY - 3);
    print_fyr("+");
    for (u16 i = 0; i < len + 2; i++) print_fyr("-");
    print_fyr("+");

    carriage_set_position(0, SIZE_Y_DISPLAY - 2);
    print_fyr("| %d |", GLOBAL_COUNTER_TIMER++);

    carriage_set_position(0, SIZE_Y_DISPLAY - 1);
    print_fyr("+");
    for (u16 i = 0; i < len + 2; i++) print_fyr("-");
    print_fyr("+");

    carriage_set_position(pos_carr >> 16, (u16)pos_carr);
    carriage_set_position(0, 0);
}