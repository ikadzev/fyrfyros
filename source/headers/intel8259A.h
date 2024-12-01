//
// Created by modnick on 20.11.2024.
//

#ifndef FYRFYROS_INTEL8259A_H

#include "macroses.h"

#define MAGIC_CONST 0xAD

#define DATA_PORT_SLAVE 0xA1
#define DATA_PORT_MASTER 0x21
#define COMMAND_PORT_SLAVE 0xA0
#define COMMAND_PORT_MASTER 0x20
#define DIAGNOSTIC_PORT_BIOS 0x80

#define START_VECTOR_SLAVE 0x28
#define START_VECTOR_MASTER 0x20

enum intel8259_type {
    slave,
    master
};

byte inb(u16 port);
void outb(u16 port, byte data);


void configure_intel8259(u16 command_port, u16 data_port, enum intel8259_type type);
void configure_intel8258A_all();
void configure_intel8259_mask(enum intel8259_type type, byte mask);

#define FYRFYROS_INTEL8259A_H

#endif //FYRFYROS_INTEL8259A_H
