//
// Created by modnick on 08.11.2024.
//

#ifndef FYRFYROS_TRAMPLINS_H
#define FYRFYROS_TRAMPLINS_H

#include "macroses.h"

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
    u16 shift_low;
    u16 selector_segment;
    byte reserve1;
    byte gate_type : 4;
    byte reserve2 : 1;
    byte dpl : 2;
    byte reserve3 : 1;
    u16 shift_height;
} gate_descriptor;

typedef struct table_gate_descriptor {
    u16 size;
    u32 address;
} table_gate_descriptor;

static gate_descriptor *generate_idt();
static gate_descriptor generate_gate_descriptor(void* tramplin_ptr, enum gate_type type, enum descriptor_privilege_level level);
void create_lidt();
#endif //FYRFYROS_TRAMPLINS_H
