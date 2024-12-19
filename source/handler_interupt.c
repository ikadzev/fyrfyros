//
// Created by modnick on 23.11.2024.
//

#include "headers/handler_interupt.h"
#include "headers/intel8259A.h"

extern void floppy_irq();

u32 GLOBAL_COUNTER_TIMER = 0x0;

void eoi(enum intel8259_type cont) {
    outb(cont == master ? 0x20 : 0xA0, 0x20);
}

void interrupt_handler(context* ctx) {
    switch (ctx->vector) {
        case 0x20:
            //timer_interrupt(ctx);
            eoi(master);
            break;
        case 0x26:
            floppy_irq();
            eoi(master);
            break;
        default:
            if (ctx->vector < START_VECTOR_MASTER) {
                trap_handler(ctx);
            } else if (ctx->vector < 0x30) {
                if (ctx->vector >= START_VECTOR_SLAVE) {
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
//    sti();
    for (;;);
}

void window_trap_handler(window* wind, context* ctx) {
    //window_print_context(wind, ctx);
    sti();
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

void window_print_context(window* wind, context* ctx) {
    window_vga_clear_screen(wind);
    window_print_fyr(wind, "\r\nKernel panic: unhandled interrupt %x, interrupted process context:\r\n", ctx->vector);
    window_print_fyr(wind, "  EAX = %x ", ctx->eax);
    window_print_fyr(wind, "ECX = %x ", ctx->ecx);
    window_print_fyr(wind, "EDX = %x ", ctx->edx);
    window_print_fyr(wind, "EBX = %x\r\n", ctx->ebx);
    window_print_fyr(wind, "  ESP = %x ", ctx->esp);
    window_print_fyr(wind, "EBP = %x ", ctx->ebp);
    window_print_fyr(wind, "ESI = %x ", ctx->esi);
    window_print_fyr(wind, "EDI = %x\r\n", ctx->edi);
    window_print_fyr(wind, "  DS  = %x ", ctx->ds);
    window_print_fyr(wind, "ES  = %x ", ctx->es);
    window_print_fyr(wind, "FS  = %x ", ctx->fs);
    window_print_fyr(wind, "GS  = %x\r\n", ctx->gs);
    window_print_fyr(wind, "  CS  = %x ", ctx->cs);
    window_print_fyr(wind, "EIP = %x ", ctx->eip);
    window_print_fyr(wind, "EFLAGS = %x\r\n", ctx->eflags);
    window_print_fyr(wind, "  error code = %x\r\n", ctx->error_code);
}

void panic_handler(context* ctx) {
    print_context(ctx);
    for (;;);
}

static void timer_interrupt(context* ctx) {
//    GLOBAL_COUNTER_TIMER++;
//    return;
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

static void window_timer_interrupt(window* wind, context* ctx) {
    u32 pos_carr = window_carriage_get_position(wind);

    u16 len = 1;
    for (u32 i = GLOBAL_COUNTER_TIMER / 10; i > 0; i /= 10) len++;

    window_carriage_set_position(wind, 0, wind->size_y - 3);
    window_print_fyr(wind, "+");
    for (u16 i = 0; i < len + 2; i++) window_print_fyr(wind, "-");
    window_print_fyr(wind, "+");

    window_carriage_set_position(wind, 0, wind->size_y - 2);
    window_print_fyr(wind, "| %d |", GLOBAL_COUNTER_TIMER++);

    window_carriage_set_position(wind, 0, wind->size_y - 1);
    window_print_fyr(wind, "+");
    for (u16 i = 0; i < len + 2; i++) window_print_fyr(wind, "-");
    window_print_fyr(wind, "+");

    window_carriage_set_position(wind, pos_carr >> 16, (u16)pos_carr);
    window_carriage_set_position(wind, 0, 0);
}