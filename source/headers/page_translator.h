//
// Created by rostyan on 03.12.2024.
//

#ifndef FYRFYROS_PAGE_TRANSLATOR_H
#define FYRFYROS_PAGE_TRANSLATOR_H

#include "_flags.h"
#include "macroses.h"
#include "kernel_allocator.h"
#include "printf.h"


#define SIZE_TABLE 0x1000

void init_virtual_address();  // инициализация всех виртуальных адресов

void create_page_directory(u32 start_frame);
u32* create_page_table();
#ifdef PSE_MODE
void create_virtual_kernel_with_pse();
u32 create_pde_with_pse(byte write_mode, byte user_mode);
void delete_pde_with_pse(u32 pde);
#else
void create_virtual_kernel_with_pse();
//void create_page_directory_with_pse(u32 count_list);
void create_page_list_with_pse();
#endif

#endif //FYRFYROS_PAGE_TRANSLATOR_H
