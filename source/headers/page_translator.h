//
// Created by rostyan on 03.12.2024.
//

#ifndef FYRFYROS_PAGE_TRANSLATOR_H
#define FYRFYROS_PAGE_TRANSLATOR_H

#include "macroses.h"
#include "page_allocator.h"
#include "kernel_allocator.h"

#define SIZE_TABLE 0x1000
#define PSE_MOD

void init_virtual_address();  // инициализация всех виртуальных адресов
void init_virtual_kernel();  // инициализация виртуального ядра

void create_page_directory(u32 start_frame);
u32* create_page_table();
#ifdef PSE_MOD
void create_page_directory_with_pse(u32 start_frame, u32 count_list);
#else
void create_page_directory_without_pse(u32 start_frame, u32 count_list);
#endif

#endif //FYRFYROS_PAGE_TRANSLATOR_H
