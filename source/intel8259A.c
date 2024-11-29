//
// Created by modnick on 20.11.2024.
//
#include "headers/intel8259A.h"
#include "headers/printf.h"


byte inb(u16 port) {
    byte answer = -1;
    __asm__ __volatile__ (
            ".intel_syntax noprefix\n\t"
             "in al, dx\n\t"
            ".att_syntax prefix\n\t"
         : "=a"(answer)
         : "d"(port)
         : //"eax", "edx", "memory"
            );
    return answer;
}

void outb(u16 port, byte data) {
    __asm__ __volatile__ (
            ".intel_syntax noprefix\n\t"
            "out dx, al\n\t"
            ".att_syntax prefix\n\t"
            :
            : "d"(port), "a"(data)
            : //"eax", "edx", "memory"
            );
}

void configure_intel8259(u16 command_port, u16 data_port, enum intel8259_type type) {
    byte icw1 = 0b00010001;
    byte icw2 = type == master ? start_vector_master : start_vector_slave;
    byte icw3 = type == master ? 0b00000100: 0x2;
    byte icw4 = 0b00000001;

    outb(command_port, icw1);
    outb(diagnostic_port_bios, magic_const);

    outb(data_port, icw2);
    outb(diagnostic_port_bios, magic_const);

    outb(data_port, icw3);
    outb(diagnostic_port_bios, magic_const);

    outb(data_port, icw4);
    outb(diagnostic_port_bios, magic_const);
}

void configure_intel8258A_all() {
    configure_intel8259(command_port_master, data_port_master, master);
    configure_intel8259(command_port_slave, data_port_slave, slave);
    configure_intel8259_mask(master, 0);
    configure_intel8259_mask(slave, 0);
}

void configure_intel8259_mask(enum intel8259_type type, byte mask) {
    if (type == master) {
        outb(data_port_master, mask);
    } else {
        outb(data_port_slave, mask);
    }
}