//
// Created by rostyan on 03.12.2024.
//

#include "headers/page_translator.h"
#include "headers/page_allocator.h"
#include "headers/asm_fync.h"
#include "headers/vga_driver.h"


void init_virtual_address() {
#ifdef PSE_MODE
    create_virtual_kernel_with_pse();
#else
    create_virtual_kernel_without_pse();
#endif
}

#ifdef PSE_MODE
void create_virtual_kernel_with_pse() {
    u32* page_dir = kernel_calloc(1024, sizeof(u32));
    page_dir[0] = create_pde_with_pse(1,0);
    page_dir[1] = create_pde_with_pse(1,0);
    set_CR3(page_dir);
    expose_bit_CR4(5);
    expose_bit_CR0(32);
}
u32 create_pde_with_pse(byte write_mode, byte user_mode) {
    u32 pde = 1;
    u32 address = (u32)page_malloc(sizeof(u32));
    address = (address - PAGE_START_ALLOCATE) / 4;
    u32 address_high = address >> 10;
    address = address - (address_high << 10);
    pde |= (write_mode & 1) << 1;
    pde |= (user_mode & 1) << 2;
    pde |= 1 << 7;
    pde |= (address_high << 13);
    pde |= (address << 22);
    return pde;
}
void delete_pde_with_pse(u32 pde){
    u32 ptr_pde = pde >> 22;
    ptr_pde |= (pde >> 13 ) << 24 >> 14;
    ptr_pde = (ptr_pde * 4) + PAGE_START_ALLOCATE;
    page_free((u32*)ptr_pde);
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

#ifdef PSE_MODE

#else
void create_page_directory_without_pse(u32 start_frame, u32 count_list);
#endif
