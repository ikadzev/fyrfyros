//
// Created by modnick on 20.11.2024.
//

#ifndef FYRFYROS_INTEL8259A_H

#include "macroses.h"

#define magic_const 0xAD

#define data_port_slave 0xA1
#define data_port_master 0x21
#define command_port_slave 0xA0
#define command_port_master 0x20
#define diagnostic_port_bios 0x80

#define start_vector_slave 0x28
#define start_vector_master 0x20

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
