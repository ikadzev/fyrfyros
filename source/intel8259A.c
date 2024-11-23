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
    byte iwc1 = 0b00010001;
    byte iwc2 = type == master ? 0x20 : 0x28;
    byte iwc3 = type == master ? 0b00000100: 0x2;
    byte iwc4 = 0b00000001;
    outb(command_port, iwc1);
    outb(0x80, 0xAD);
    outb(data_port, iwc2);
    outb(0x80, 0xAD);
    outb(data_port, iwc3);
    outb(0x80, 0xAD);
    outb(data_port, iwc4);
    outb(0x80, 0xAD);
}

void configure_intel8258A_all() {
    configure_intel8259(0x20, 0x21, master);
    configure_intel8259(0xA0, 0xA1, slave);
    configure_intel8259_mask(master, 0b11111110);
    configure_intel8259_mask(slave, 0b11111111);
}

void configure_intel8259_mask(enum intel8259_type type, byte mask) {
    if (type == master) {
        outb(0x21, mask);
    } else {
        outb(0xA1, mask);
    }
}