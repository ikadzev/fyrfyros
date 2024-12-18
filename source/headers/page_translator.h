//
// Created by rostyan on 03.12.2024.
//

#ifndef FYRFYROS_PAGE_TRANSLATOR_H
#define FYRFYROS_PAGE_TRANSLATOR_H

#include "_flags.h"
#include "macroses.h"
#include "kernel_allocator.h"
#include "printf.h"


#define SIZE_TABLE 1024
#define KERNEL_SIZE_PD 4

void init_virtual_address();  // инициализация всех виртуальных адресов

#ifdef PSE_MODE
void create_virtual_kernel_with_pse();
u32 create_pde_with_pse(byte write_mode, byte user_mode);
void delete_pde_with_pse(u32 pde);
#else
void create_virtual_kernel_without_pse();
u32 create_pde_without_pse(byte write_mode, byte user_mode);
void delete_pde_without_pse(u32 pde);
u32 create_pte_without_pse(byte write_mode, byte user_mode);
void delete_pte_without_pse(u32 pte);
#endif

#endif //FYRFYROS_PAGE_TRANSLATOR_H
