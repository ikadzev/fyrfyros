//
// Created by modnick on 07.12.2024.
//

#ifndef FYRFYROS_ASM_FYNC_H
#define FYRFYROS_ASM_FYNC_H

#include "_flags.h"
#include "macroses.h"

//extern from "asm/func_asm.asm"
extern u16 inb(u16 port);
extern void outb(u16 port, byte data);

extern void set_CR3(u32* ptr);
extern u32* get_CR3();

extern void expose_bit_CR4(byte shift);
extern void clear_bit_CR4(byte shift);

extern void expose_bit_CR0(byte shift);
extern void clear_bit_CR0(byte shift);

extern void cli();
extern void sti();


#endif //FYRFYROS_ASM_FYNC_H
