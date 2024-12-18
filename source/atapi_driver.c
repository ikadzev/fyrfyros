//
// Created by modnick on 07.12.2024.
//

#include "headers/atapi_driver.h"
#include "headers/asm_fync.h"
#include "headers/printf.h"
#include "headers/vga_driver.h"

pata_devise init_device(u16 start_ports) {
    pata_devise device;
    device.ports.data_port = start_ports;
    device.ports.features_error_port = start_ports + 1;
    device.ports.sector_count_port = start_ports + 2;
    device.ports.sector_number_port = start_ports + 3;
    device.ports.cylinder_low_port = start_ports + 4;
    device.ports.cylinder_high_port = start_ports + 5;
    device.ports.drive_head_port = start_ports + 6;
    device.ports.command_status_port = start_ports + 7;

    outb(device.ports.drive_head_port, 0xa0);
    outb(device.ports.sector_count_port, 0x0);
    outb(device.ports.sector_number_port, 0x0);
    outb(device.ports.cylinder_low_port, 0x0);
    outb(device.ports.cylinder_high_port, 0x0);

    vga_clear_screen();

    outb(device.ports.command_status_port, 0xEC);
    u32 out= 0;
    u16 b[256];
    while (TRUE){
        out = inb(device.ports.command_status_port);
        if (out == 0){
            vga_error();
            for (;;);
        };
        if ((out & 0x80) == 0) break;
    }
    for (int i = 0; i < 256; ++i) {
        b[i] = inb(device.ports.data_port);
        outb(0x80, 0);
    }

    for (int i = 0; i < 7; ++i) {
        print_fyr("%x \r\n", b[i]);
    }

    for (;;);
}