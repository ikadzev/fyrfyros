//
// Created by modnick on 20.11.2024.
//
#include "headers/intel8259A.h"
#include "headers/printf.h"

void configure_intel8259(u16 command_port, u16 data_port, enum intel8259_type type) {
    byte icw1 = 0b00010001;
    byte icw2 = type == master ? START_VECTOR_MASTER : START_VECTOR_SLAVE;
    byte icw3 = type == master ? 0b00000100: 0x2;
    byte icw4 = 0b00000001;

    outb(command_port, icw1);
    outb(DIAGNOSTIC_PORT_BIOS, MAGIC_CONST);

    outb(data_port, icw2);
    outb(DIAGNOSTIC_PORT_BIOS, MAGIC_CONST);

    outb(data_port, icw3);
    outb(DIAGNOSTIC_PORT_BIOS, MAGIC_CONST);

    outb(data_port, icw4);
    outb(DIAGNOSTIC_PORT_BIOS, MAGIC_CONST);
}

void configure_intel8258A_all() {
    configure_intel8259(COMMAND_PORT_MASTER, DATA_PORT_MASTER, master);
    configure_intel8259(COMMAND_PORT_SLAVE, DATA_PORT_SLAVE, slave);
    configure_intel8259_mask(master, 0b11111001);
    configure_intel8259_mask(slave, 0);
}

void configure_intel8259_mask(enum intel8259_type type, byte mask) {
    if (type == master) {
        outb(DATA_PORT_MASTER, mask);
    } else {
        outb(DATA_PORT_SLAVE, mask);
    }
}