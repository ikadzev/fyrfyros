//
// Created by modnick on 23.11.2024.
//

#include "headers/handler_interupt.h"
#include "headers/intel8259A.h"

u32 GLOBAL_COUNTER_TIMER = 0x0;

void return_ie_flag() {
    __asm__ __volatile__ (
            ".intel_syntax noprefix\n\t"
            "sti\n\t"
            ".att_syntax prefix\n\t"
            );
}

void interrupt_handler(context* ctx) {
    print_context(ctx);
    switch (ctx->vector) {
        case 0x20:
            timer_interrupt(ctx);
            outb(0x20, 0x20);
            break;
        default:
            if (ctx->vector < 0x20) {
                return_ie_flag();
            } else if (ctx->vector < 0x30) {
                if (ctx->vector >= 0x28) {
                    outb(0xA0, 0x20);
                }
                outb(0x20, 0x20);
            }
            panic_handler(ctx->vector);
            // for (;;);
            break;
    }
}

void print_context(context* ctx) {
    vga_clear_screen();
    print_fyr("Kernel panic: unhandled interrupt %x, interrupted process context:\r\n", ctx->vector);
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
    print_fyr("SS  = %x ", ctx->ss);
    print_fyr("EIP = %x\r\n", ctx->eip);
    print_fyr("  EFLAGS (interrupted) = %x\r\n", ctx->eflags);
    print_fyr("  error code = %x\r\n", ctx->error_code);
}

void panic_handler(byte vector) {
    vga_init();
    print_fyr("unhandled interrupt %x", vector);
    for (;;) {}
}

static void timer_interrupt(context* ctx) {
    print_fyr("GLOBAL_COUNTER_TIMER = %d\r\n", GLOBAL_COUNTER_TIMER++);
}