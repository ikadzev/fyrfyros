//
// Created by rostyan on 03.12.2024.
//

#include "headers/page_translator.h"


void init_virtual_address() {

}

void init_virtual_kernel() {
    create_virtual_kernel();
}
#ifdef PSE_MODE
void create_virtual_kernel() {
    for (u32 i = 0; i < 1024; i++) {
        *((u32*)(OFFSET_PAGE_DIR + i * 4)) = 0;
    }
    *((u32*)(OFFSET_PAGE_DIR)) =  0b0000000000000010000111;
    *((u32*)(OFFSET_PAGE_DIR + 4)) = (1 << 22) | 0b0000000000000010000111;
    __asm__ __volatile__ (
            ".intel_syntax noprefix\n\t"
            "push eax\n\t"
            "mov eax, 0x1000\n\t"
            "mov cr3, eax\n\t"
            "mov eax, cr4\n\t"
            "or eax, 0b00000000000000000000000000010000\n\t"
            "mov cr4, eax\n\t"
            "mov eax, cr0\n\t"
            "or eax, 0b10000000000000000000000000000000\n\t"
            "mov cr0, eax\n\t"
            "pop eax\n\t"
            ".att_syntax prefix\n\t"
            );
}
#else
void create_virtual_kernel() {
    for (u32 i = 0; i < 1024; i++) {
        *((u32*)(OFFSET_PAGE_DIR + i * 4)) = 0;
    }
    u32* base_page = kernel_malloc(SIZE_TABLE);
    *((u32*)(OFFSET_PAGE_DIR)) = (u32)base_page + 0b111;
    for (u32 i = 0; i < 1024; i++){
        if(i == 2) {
            *(base_page + i) = 0;
        } else {
            *(base_page + i) = i * 0x1000 + 0b111;
            //print_fyr("%x ", *(base_page + i));
        }
    }
    base_page = kernel_malloc(SIZE_TABLE);
    print_hex((u32)base_page);
    *((u32*)(OFFSET_PAGE_DIR + 4)) = (u32)base_page + 0b111;
    for (u32 i = 0; i < 1024; i++){
        *(base_page + i) = 0x400000 + i * 0x1000 + 0b111;
    }
    __asm__ __volatile__ (
            ".intel_syntax noprefix\n\t"
            "push eax\n\t"
            "mov eax, 0x1000\n\t"
            "mov cr3, eax\n\t"
            "mov eax, cr4\n\t"
            "and eax, 0b11111111111111111111111111101111\n\t"
            "mov cr4, eax\n\t"
            "mov eax, cr0\n\t"
            "or eax, 0b10000000000000000000000000000000\n\t"
            "mov cr0, eax\n\t"
            "pop eax\n\t"
            ".att_syntax prefix\n\t"
            );
}
#endif

u32* create_page_table() {
    void* base_page = kernel_malloc(SIZE_TABLE);
}

#ifdef PSE_MODE
void create_page_directory_with_pse(u32 start_frame, u32 count_list);
#else
void create_page_directory_without_pse(u32 start_frame, u32 count_list);
#endif
