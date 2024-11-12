//
// Created by modnick on 08.11.2024.
//

#ifndef FYRFYROS_TRAMPLINS_H
#define FYRFYROS_TRAMPLINS_H

#include "kernel_allocator.h"
#include "printf.h"
#include "vga_driver.h"

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

static gate_descriptor *generate_idt();
static gate_descriptor generate_gate_descriptor(void* tramplin_ptr, enum gate_type type, enum descriptor_privilege_level level);
static void create_lidt();
static void panic_handler(unsigned char vector);

static void tramplin_00() { panic_handler(0x00); }
static void tramplin_01() { panic_handler(0x01); }
static void tramplin_02() { panic_handler(0x02); }
static void tramplin_03() { panic_handler(0x03); }
static void tramplin_04() { panic_handler(0x04); }
static void tramplin_05() { panic_handler(0x05); }
static void tramplin_06() { panic_handler(0x06); }
static void tramplin_07() { panic_handler(0x07); }
static void tramplin_08() { panic_handler(0x08); }
static void tramplin_09() { panic_handler(0x09); }
static void tramplin_0A() { panic_handler(0x0A); }
static void tramplin_0B() { panic_handler(0x0B); }
static void tramplin_0C() { panic_handler(0x0C); }
static void tramplin_0D() { panic_handler(0x0D); }
static void tramplin_0E() { panic_handler(0x0E); }
static void tramplin_0F() { panic_handler(0x0F); }
static void tramplin_10() { panic_handler(0x10); }
static void tramplin_11() { panic_handler(0x11); }
static void tramplin_12() { panic_handler(0x12); }
static void tramplin_13() { panic_handler(0x13); }
static void tramplin_14() { panic_handler(0x14); }
static void tramplin_15() { panic_handler(0x15); }
static void tramplin_16() { panic_handler(0x16); }
static void tramplin_17() { panic_handler(0x17); }
static void tramplin_18() { panic_handler(0x18); }
static void tramplin_19() { panic_handler(0x19); }
static void tramplin_1A() { panic_handler(0x1A); }
static void tramplin_1B() { panic_handler(0x1B); }
static void tramplin_1C() { panic_handler(0x1C); }
static void tramplin_1D() { panic_handler(0x1D); }
static void tramplin_1E() { panic_handler(0x1E); }
static void tramplin_1F() { panic_handler(0x1F); }
static void tramplin_20() { panic_handler(0x20); }
static void tramplin_21() { panic_handler(0x21); }
static void tramplin_22() { panic_handler(0x22); }
static void tramplin_23() { panic_handler(0x23); }
static void tramplin_24() { panic_handler(0x24); }
static void tramplin_25() { panic_handler(0x25); }
static void tramplin_26() { panic_handler(0x26); }
static void tramplin_27() { panic_handler(0x27); }
static void tramplin_28() { panic_handler(0x28); }
static void tramplin_29() { panic_handler(0x29); }
static void tramplin_2A() { panic_handler(0x2A); }
static void tramplin_2B() { panic_handler(0x2B); }
static void tramplin_2C() { panic_handler(0x2C); }
static void tramplin_2D() { panic_handler(0x2D); }
static void tramplin_2E() { panic_handler(0x2E); }
static void tramplin_2F() { panic_handler(0x2F); }
static void tramplin_30() { panic_handler(0x30); }
static void tramplin_31() { panic_handler(0x31); }
static void tramplin_32() { panic_handler(0x32); }
static void tramplin_33() { panic_handler(0x33); }
static void tramplin_34() { panic_handler(0x34); }
static void tramplin_35() { panic_handler(0x35); }
static void tramplin_36() { panic_handler(0x36); }
static void tramplin_37() { panic_handler(0x37); }
static void tramplin_38() { panic_handler(0x38); }
static void tramplin_39() { panic_handler(0x39); }
static void tramplin_3A() { panic_handler(0x3A); }
static void tramplin_3B() { panic_handler(0x3B); }
static void tramplin_3C() { panic_handler(0x3C); }
static void tramplin_3D() { panic_handler(0x3D); }
static void tramplin_3E() { panic_handler(0x3E); }
static void tramplin_3F() { panic_handler(0x3F); }
static void tramplin_40() { panic_handler(0x40); }
static void tramplin_41() { panic_handler(0x41); }
static void tramplin_42() { panic_handler(0x42); }
static void tramplin_43() { panic_handler(0x43); }
static void tramplin_44() { panic_handler(0x44); }
static void tramplin_45() { panic_handler(0x45); }
static void tramplin_46() { panic_handler(0x46); }
static void tramplin_47() { panic_handler(0x47); }
static void tramplin_48() { panic_handler(0x48); }
static void tramplin_49() { panic_handler(0x49); }
static void tramplin_4A() { panic_handler(0x4A); }
static void tramplin_4B() { panic_handler(0x4B); }
static void tramplin_4C() { panic_handler(0x4C); }
static void tramplin_4D() { panic_handler(0x4D); }
static void tramplin_4E() { panic_handler(0x4E); }
static void tramplin_4F() { panic_handler(0x4F); }
static void tramplin_50() { panic_handler(0x50); }
static void tramplin_51() { panic_handler(0x51); }
static void tramplin_52() { panic_handler(0x52); }
static void tramplin_53() { panic_handler(0x53); }
static void tramplin_54() { panic_handler(0x54); }
static void tramplin_55() { panic_handler(0x55); }
static void tramplin_56() { panic_handler(0x56); }
static void tramplin_57() { panic_handler(0x57); }
static void tramplin_58() { panic_handler(0x58); }
static void tramplin_59() { panic_handler(0x59); }
static void tramplin_5A() { panic_handler(0x5A); }
static void tramplin_5B() { panic_handler(0x5B); }
static void tramplin_5C() { panic_handler(0x5C); }
static void tramplin_5D() { panic_handler(0x5D); }
static void tramplin_5E() { panic_handler(0x5E); }
static void tramplin_5F() { panic_handler(0x5F); }
static void tramplin_60() { panic_handler(0x60); }
static void tramplin_61() { panic_handler(0x61); }
static void tramplin_62() { panic_handler(0x62); }
static void tramplin_63() { panic_handler(0x63); }
static void tramplin_64() { panic_handler(0x64); }
static void tramplin_65() { panic_handler(0x65); }
static void tramplin_66() { panic_handler(0x66); }
static void tramplin_67() { panic_handler(0x67); }
static void tramplin_68() { panic_handler(0x68); }
static void tramplin_69() { panic_handler(0x69); }
static void tramplin_6A() { panic_handler(0x6A); }
static void tramplin_6B() { panic_handler(0x6B); }
static void tramplin_6C() { panic_handler(0x6C); }
static void tramplin_6D() { panic_handler(0x6D); }
static void tramplin_6E() { panic_handler(0x6E); }
static void tramplin_6F() { panic_handler(0x6F); }
static void tramplin_70() { panic_handler(0x70); }
static void tramplin_71() { panic_handler(0x71); }
static void tramplin_72() { panic_handler(0x72); }
static void tramplin_73() { panic_handler(0x73); }
static void tramplin_74() { panic_handler(0x74); }
static void tramplin_75() { panic_handler(0x75); }
static void tramplin_76() { panic_handler(0x76); }
static void tramplin_77() { panic_handler(0x77); }
static void tramplin_78() { panic_handler(0x78); }
static void tramplin_79() { panic_handler(0x79); }
static void tramplin_7A() { panic_handler(0x7A); }
static void tramplin_7B() { panic_handler(0x7B); }
static void tramplin_7C() { panic_handler(0x7C); }
static void tramplin_7D() { panic_handler(0x7D); }
static void tramplin_7E() { panic_handler(0x7E); }
static void tramplin_7F() { panic_handler(0x7F); }
static void tramplin_80() { panic_handler(0x80); }
static void tramplin_81() { panic_handler(0x81); }
static void tramplin_82() { panic_handler(0x82); }
static void tramplin_83() { panic_handler(0x83); }
static void tramplin_84() { panic_handler(0x84); }
static void tramplin_85() { panic_handler(0x85); }
static void tramplin_86() { panic_handler(0x86); }
static void tramplin_87() { panic_handler(0x87); }
static void tramplin_88() { panic_handler(0x88); }
static void tramplin_89() { panic_handler(0x89); }
static void tramplin_8A() { panic_handler(0x8A); }
static void tramplin_8B() { panic_handler(0x8B); }
static void tramplin_8C() { panic_handler(0x8C); }
static void tramplin_8D() { panic_handler(0x8D); }
static void tramplin_8E() { panic_handler(0x8E); }
static void tramplin_8F() { panic_handler(0x8F); }
static void tramplin_90() { panic_handler(0x90); }
static void tramplin_91() { panic_handler(0x91); }
static void tramplin_92() { panic_handler(0x92); }
static void tramplin_93() { panic_handler(0x93); }
static void tramplin_94() { panic_handler(0x94); }
static void tramplin_95() { panic_handler(0x95); }
static void tramplin_96() { panic_handler(0x96); }
static void tramplin_97() { panic_handler(0x97); }
static void tramplin_98() { panic_handler(0x98); }
static void tramplin_99() { panic_handler(0x99); }
static void tramplin_9A() { panic_handler(0x9A); }
static void tramplin_9B() { panic_handler(0x9B); }
static void tramplin_9C() { panic_handler(0x9C); }
static void tramplin_9D() { panic_handler(0x9D); }
static void tramplin_9E() { panic_handler(0x9E); }
static void tramplin_9F() { panic_handler(0x9F); }
static void tramplin_A0() { panic_handler(0xA0); }
static void tramplin_A1() { panic_handler(0xA1); }
static void tramplin_A2() { panic_handler(0xA2); }
static void tramplin_A3() { panic_handler(0xA3); }
static void tramplin_A4() { panic_handler(0xA4); }
static void tramplin_A5() { panic_handler(0xA5); }
static void tramplin_A6() { panic_handler(0xA6); }
static void tramplin_A7() { panic_handler(0xA7); }
static void tramplin_A8() { panic_handler(0xA8); }
static void tramplin_A9() { panic_handler(0xA9); }
static void tramplin_AA() { panic_handler(0xAA); }
static void tramplin_AB() { panic_handler(0xAB); }
static void tramplin_AC() { panic_handler(0xAC); }
static void tramplin_AD() { panic_handler(0xAD); }
static void tramplin_AE() { panic_handler(0xAE); }
static void tramplin_AF() { panic_handler(0xAF); }
static void tramplin_B0() { panic_handler(0xB0); }
static void tramplin_B1() { panic_handler(0xB1); }
static void tramplin_B2() { panic_handler(0xB2); }
static void tramplin_B3() { panic_handler(0xB3); }
static void tramplin_B4() { panic_handler(0xB4); }
static void tramplin_B5() { panic_handler(0xB5); }
static void tramplin_B6() { panic_handler(0xB6); }
static void tramplin_B7() { panic_handler(0xB7); }
static void tramplin_B8() { panic_handler(0xB8); }
static void tramplin_B9() { panic_handler(0xB9); }
static void tramplin_BA() { panic_handler(0xBA); }
static void tramplin_BB() { panic_handler(0xBB); }
static void tramplin_BC() { panic_handler(0xBC); }
static void tramplin_BD() { panic_handler(0xBD); }
static void tramplin_BE() { panic_handler(0xBE); }
static void tramplin_BF() { panic_handler(0xBF); }
static void tramplin_C0() { panic_handler(0xC0); }
static void tramplin_C1() { panic_handler(0xC1); }
static void tramplin_C2() { panic_handler(0xC2); }
static void tramplin_C3() { panic_handler(0xC3); }
static void tramplin_C4() { panic_handler(0xC4); }
static void tramplin_C5() { panic_handler(0xC5); }
static void tramplin_C6() { panic_handler(0xC6); }
static void tramplin_C7() { panic_handler(0xC7); }
static void tramplin_C8() { panic_handler(0xC8); }
static void tramplin_C9() { panic_handler(0xC9); }
static void tramplin_CA() { panic_handler(0xCA); }
static void tramplin_CB() { panic_handler(0xCB); }
static void tramplin_CC() { panic_handler(0xCC); }
static void tramplin_CD() { panic_handler(0xCD); }
static void tramplin_CE() { panic_handler(0xCE); }
static void tramplin_CF() { panic_handler(0xCF); }
static void tramplin_D0() { panic_handler(0xD0); }
static void tramplin_D1() { panic_handler(0xD1); }
static void tramplin_D2() { panic_handler(0xD2); }
static void tramplin_D3() { panic_handler(0xD3); }
static void tramplin_D4() { panic_handler(0xD4); }
static void tramplin_D5() { panic_handler(0xD5); }
static void tramplin_D6() { panic_handler(0xD6); }
static void tramplin_D7() { panic_handler(0xD7); }
static void tramplin_D8() { panic_handler(0xD8); }
static void tramplin_D9() { panic_handler(0xD9); }
static void tramplin_DA() { panic_handler(0xDA); }
static void tramplin_DB() { panic_handler(0xDB); }
static void tramplin_DC() { panic_handler(0xDC); }
static void tramplin_DD() { panic_handler(0xDD); }
static void tramplin_DE() { panic_handler(0xDE); }
static void tramplin_DF() { panic_handler(0xDF); }
static void tramplin_E0() { panic_handler(0xE0); }
static void tramplin_E1() { panic_handler(0xE1); }
static void tramplin_E2() { panic_handler(0xE2); }
static void tramplin_E3() { panic_handler(0xE3); }
static void tramplin_E4() { panic_handler(0xE4); }
static void tramplin_E5() { panic_handler(0xE5); }
static void tramplin_E6() { panic_handler(0xE6); }
static void tramplin_E7() { panic_handler(0xE7); }
static void tramplin_E8() { panic_handler(0xE8); }
static void tramplin_E9() { panic_handler(0xE9); }
static void tramplin_EA() { panic_handler(0xEA); }
static void tramplin_EB() { panic_handler(0xEB); }
static void tramplin_EC() { panic_handler(0xEC); }
static void tramplin_ED() { panic_handler(0xED); }
static void tramplin_EE() { panic_handler(0xEE); }
static void tramplin_EF() { panic_handler(0xEF); }
static void tramplin_F0() { panic_handler(0xF0); }
static void tramplin_F1() { panic_handler(0xF1); }
static void tramplin_F2() { panic_handler(0xF2); }
static void tramplin_F3() { panic_handler(0xF3); }
static void tramplin_F4() { panic_handler(0xF4); }
static void tramplin_F5() { panic_handler(0xF5); }
static void tramplin_F6() { panic_handler(0xF6); }
static void tramplin_F7() { panic_handler(0xF7); }
static void tramplin_F8() { panic_handler(0xF8); }
static void tramplin_F9() { panic_handler(0xF9); }
static void tramplin_FA() { panic_handler(0xFA); }
static void tramplin_FB() { panic_handler(0xFB); }
static void tramplin_FC() { panic_handler(0xFC); }
static void tramplin_FD() { panic_handler(0xFD); }
static void tramplin_FE() { panic_handler(0xFE); }
static void tramplin_FF() { panic_handler(0xFF); }

static void* tramplins[] = {tramplin_00, tramplin_01, tramplin_02, tramplin_03, tramplin_04,
                            tramplin_05, tramplin_06, tramplin_07, tramplin_08, tramplin_09,
                            tramplin_0A, tramplin_0B, tramplin_0C, tramplin_0D, tramplin_0E,
                            tramplin_0F, tramplin_10, tramplin_11, tramplin_12, tramplin_13,
                            tramplin_14, tramplin_15, tramplin_16, tramplin_17, tramplin_18,
                            tramplin_19, tramplin_1A, tramplin_1B, tramplin_1C, tramplin_1D,
                            tramplin_1E, tramplin_1F, tramplin_20, tramplin_21, tramplin_22,
                            tramplin_23, tramplin_24, tramplin_25, tramplin_26, tramplin_27,
                            tramplin_28, tramplin_29, tramplin_2A, tramplin_2B, tramplin_2C,
                            tramplin_2D, tramplin_2E, tramplin_2F, tramplin_30, tramplin_31,
                            tramplin_32, tramplin_33, tramplin_34, tramplin_35, tramplin_36,
                            tramplin_37, tramplin_38, tramplin_39, tramplin_3A, tramplin_3B,
                            tramplin_3C, tramplin_3D, tramplin_3E, tramplin_3F, tramplin_40,
                            tramplin_41, tramplin_42, tramplin_43, tramplin_44, tramplin_45,
                            tramplin_46, tramplin_47, tramplin_48, tramplin_49, tramplin_4A,
                            tramplin_4B, tramplin_4C, tramplin_4D, tramplin_4E, tramplin_4F,
                            tramplin_50, tramplin_51, tramplin_52, tramplin_53, tramplin_54,
                            tramplin_55, tramplin_56, tramplin_57, tramplin_58, tramplin_59,
                            tramplin_5A, tramplin_5B, tramplin_5C, tramplin_5D, tramplin_5E,
                            tramplin_5F, tramplin_60, tramplin_61, tramplin_62, tramplin_63,
                            tramplin_64, tramplin_65, tramplin_66, tramplin_67, tramplin_68,
                            tramplin_69, tramplin_6A, tramplin_6B, tramplin_6C, tramplin_6D,
                            tramplin_6E, tramplin_6F, tramplin_70, tramplin_71, tramplin_72,
                            tramplin_73, tramplin_74, tramplin_75, tramplin_76, tramplin_77,
                            tramplin_78, tramplin_79, tramplin_7A, tramplin_7B, tramplin_7C,
                            tramplin_7D, tramplin_7E, tramplin_7F, tramplin_80, tramplin_81,
                            tramplin_82, tramplin_83, tramplin_84, tramplin_85, tramplin_86,
                            tramplin_87, tramplin_88, tramplin_89, tramplin_8A, tramplin_8B,
                            tramplin_8C, tramplin_8D, tramplin_8E, tramplin_8F, tramplin_90,
                            tramplin_91, tramplin_92, tramplin_93, tramplin_94, tramplin_95,
                            tramplin_96, tramplin_97, tramplin_98, tramplin_99, tramplin_9A,
                            tramplin_9B, tramplin_9C, tramplin_9D, tramplin_9E, tramplin_9F,
                            tramplin_A0, tramplin_A1, tramplin_A2, tramplin_A3, tramplin_A4,
                            tramplin_A5, tramplin_A6, tramplin_A7, tramplin_A8, tramplin_A9,
                            tramplin_AA, tramplin_AB, tramplin_AC, tramplin_AD, tramplin_AE,
                            tramplin_AF, tramplin_B0, tramplin_B1, tramplin_B2, tramplin_B3,
                            tramplin_B4, tramplin_B5, tramplin_B6, tramplin_B7, tramplin_B8,
                            tramplin_B9, tramplin_BA, tramplin_BB, tramplin_BC, tramplin_BD,
                            tramplin_BE, tramplin_BF, tramplin_C0, tramplin_C1, tramplin_C2,
                            tramplin_C3, tramplin_C4, tramplin_C5, tramplin_C6, tramplin_C7,
                            tramplin_C8, tramplin_C9, tramplin_CA, tramplin_CB, tramplin_CC,
                            tramplin_CD, tramplin_CE, tramplin_CF, tramplin_D0, tramplin_D1,
                            tramplin_D2, tramplin_D3, tramplin_D4, tramplin_D5, tramplin_D6,
                            tramplin_D7, tramplin_D8, tramplin_D9, tramplin_DA, tramplin_DB,
                            tramplin_DC, tramplin_DD, tramplin_DE, tramplin_DF, tramplin_E0,
                            tramplin_E1, tramplin_E2, tramplin_E3, tramplin_E4, tramplin_E5,
                            tramplin_E6, tramplin_E7, tramplin_E8, tramplin_E9, tramplin_EA,
                            tramplin_EB, tramplin_EC, tramplin_ED, tramplin_EE, tramplin_EF,
                            tramplin_F0, tramplin_F1, tramplin_F2, tramplin_F3, tramplin_F4,
                            tramplin_F5, tramplin_F6, tramplin_F7, tramplin_F8, tramplin_F9,
                            tramplin_FA, tramplin_FB, tramplin_FC, tramplin_FD, tramplin_FE,
                            tramplin_FF};

static gate_descriptor* generate_idt(){
    gate_descriptor* ans = kernel_malloc(COUNT_INTERRUPT * sizeof(gate_descriptor));
    for (int i = 0; i < COUNT_INTERRUPT; ++i) {
        ans[i] = generate_gate_descriptor(tramplins[i], interrupt_gate, kernel);
    }
    return ans;
}

static gate_descriptor generate_gate_descriptor(void* tramplin_ptr, enum gate_type type, enum descriptor_privilege_level level) {
    gate_descriptor gate;
    gate.shift_low = (unsigned short)tramplin_ptr;
    __asm __volatile__( ".intel_syntax noprefix\n\t"
           "mov %0, cs\n\t"
           ".att_syntax prefix\n\t"
            : "=r"(gate.selector_segment)
            );
    gate.reserve1 = 0;
    gate.gate_type = type;
    gate.reserve2 = 0;
    gate.dpl = level;
    gate.reserve3 = 1;
    gate.shift_height = (unsigned short)((int)tramplin_ptr >> 16);
    return gate;
}

static void create_lidt() {
    gate_descriptor* descriptor = generate_idt();
    table_gate_descriptor* table = kernel_malloc(sizeof (table_gate_descriptor));
    table->size = COUNT_INTERRUPT * sizeof(gate_descriptor) - 1;
    table->address = (unsigned int)descriptor;
    __asm__ __volatile__(
            "lidt (%0)"
            :
            : "r" (table)
            : "memory"
            );
}

static void panic_handler(unsigned char vector){
    vga_clear_screen();
    print_fyr("unhandled interrupt %x", vector);
    for (;;) {

    }
};


#endif //FYRFYROS_TRAMPLINS_H
