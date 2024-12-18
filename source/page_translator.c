//
// Created by rostyan on 03.12.2024.
//

#include "headers/page_translator.h"
#include "headers/page_allocator.h"
#include "headers/asm_fync.h"


void init_virtual_address() {
#ifdef PSE_MODE
    create_virtual_kernel_with_pse();
#else
    create_virtual_kernel_without_pse();
#endif
}

#ifdef PSE_MODE
void create_virtual_kernel_with_pse() {
    u32* page_dir = kernel_calloc(SIZE_TABLE, sizeof(u32));
    for (int i = 0; i < KERNEL_SIZE_PD; ++i) {
        page_dir[i] = create_pde_with_pse(1,0);
    }
    set_CR3(page_dir);
    expose_bit_CR4(5);
    expose_bit_CR0(32);
}
u32 create_pde_with_pse(byte write_mode, byte user_mode) {
    u32 pde = 1;
    u32 address = page_malloc(1);
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
    page_free(ptr_pde);
}
#else
void create_virtual_kernel_without_pse() {
    u32* page_dir = kernel_calloc(SIZE_TABLE, sizeof(u32));
    for (int i = 0; i < KETNEL_SIZE_PD; ++i) {
        page_dir[i] = create_pde_without_pse(1,0);
        u32* ptr = (u32*)((page_dir[i] >> 12) << 12);
        for (u32 j = 0; j < SIZE_TABLE; ++j){
            ptr[j] = create_pte_without_pse(1,0);
        }
    }
    set_CR3(page_dir);
    clear_bit_CR4(5);
    expose_bit_CR0(32);
}
u32 create_pde_without_pse(byte write_mode, byte user_mode) {
    u32* address = kernel_calloc(SIZE_TABLE, sizeof(u32));
    u32 pde = 1;
    pde |= (write_mode & 1) << 1;
    pde |= (user_mode & 1) << 2;
    pde |= ((u32)address);
    return pde;
}
void delete_pde_without_pse(u32 pde) {
    u32* ptr_pde = (u32*)((pde << 12) >> 12);
    for (int i = 0; i < SIZE_TABLE; ++i) {
        delete_pte_without_pse(ptr_pde[i]);
    }
    kernel_free(ptr_pde);
}
u32 create_pte_without_pse(byte write_mode, byte user_mode) {
    u32 pte = 1;
    u32 address = page_malloc(1);
    address = (address - PAGE_START_ALLOCATE) >> 2;
    pte |= (write_mode & 1) << 1;
    pte |= (user_mode & 1) << 2;
    pte |= (address << 12);
    return pte;
}
void delete_pte_without_pse(u32 pte) {
    u32 ptr_pte = pte >> 12;
    ptr_pte = (ptr_pte * 4) + PAGE_START_ALLOCATE;
    page_free(ptr_pte);
}
#endif

