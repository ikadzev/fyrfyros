//
// Created by modnick on 23.11.2024.
//

#ifndef FYRFYROS_HANDLER_INTERUPT_H
#define FYRFYROS_HANDLER_INTERUPT_H

#include "vga_driver.h"
#include "printf.h"
//#include "macroses.h"

#pragma pack(push, 1)
typedef struct context {
    u32 edi;
    u32 esi;
    u32 ebp;
    u32 esp;
    u32 ebx;
    u32 edx;
    u32 ecx;
    u32 eax;
    u16 gs;
    u16 padding_1;
    u16 fs;
    u16 padding_2;
    u16 es;
    u16 padding_3;
    u16 ds;
    u16 padding_4;
    u32 vector;
    u32 error_code;
    u32 eip;
    u16 cs;
    u16 padding_5;
    u32 eflags;
} context;
#pragma pack(pop)

void return_ie_flag();

void interrupt_handler(context* ctx);

void print_context(context* ctx);

void panic_handler(byte vector);

static void timer_interrupt(context* ctx);

#endif //FYRFYROS_HANDLER_INTERUPT_H
