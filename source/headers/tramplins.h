#include "macroses.h"
//
// Created by modnick on 08.11.2024.
//

#ifndef FYRFYROS_TRAMPLINS_H
#define FYRFYROS_TRAMPLINS_H

#define COUNT_INTERRUPT 256

enum gate_type {
    interrupt_gate = 0xE,
    trap_gate = 0xF
};

enum descriptor_privilege_level {
    kernel = 0,
    device_driver_1 = 1,
    device_driver_2 = 2,
    application = 3
};

#pragma pack(push, 1)
typedef struct gate_descriptor {
    unsigned short shift_low;
    unsigned short selector_segment;
    unsigned char reserve1;
    unsigned char gate_type : 4;
    unsigned char reserve2 : 1;
    unsigned char dpl : 2;
    unsigned char reserve3 : 1;
    unsigned short shift_height;
} gate_descriptor;
typedef struct table_gate_descriptor {
    unsigned short size;
    unsigned int address;
} table_gate_descriptor;
#pragma pack(pop)


typedef struct {
    u32 edi;
    u32 esi;
    u32 ebp;
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
} context;


static gate_descriptor *generate_idt();
static gate_descriptor generate_gate_descriptor(void* tramplin_ptr, enum gate_type type, enum descriptor_privilege_level level);
void create_lidt();
static void panic_handler(unsigned char vector);
static void timer_interrupt(context* ctx);
#endif //FYRFYROS_TRAMPLINS_H
