//
// Created by modnick on 20.11.2024.
//

#ifndef FYRFYROS_INTEL8259A_H

#include "macroses.h"

enum intel8259_type {
    slave,
    master
};

byte inb(u16 port);
void outb(u16 port, byte data);


void configurate_intel8259(u16 command_port, u16 data_port, enum intel8259_type type);
void configurate_intel8258A_all();
void configurate_intel8259_mask(enum intel8259_type type, byte mask);

#define FYRFYROS_INTEL8259A_H

#endif //FYRFYROS_INTEL8259A_H
