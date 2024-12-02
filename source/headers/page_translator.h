//
// Created by rostyan on 03.12.2024.
//

#ifndef FYRFYROS_PAGE_TRANSLATOR_H
#define FYRFYROS_PAGE_TRANSLATOR_H

#include "macroses.h"
//#include "page_allocator.h"
#include "kernel_allocator.h"
#include "printf.h"

#define OFFSET_PAGE_DIR 0x1000

#define SIZE_TABLE 0x1000
#define PSE_MODE

void init_virtual_address();  // инициализация всех виртуальных адресов
void init_virtual_kernel();  // инициализация виртуального ядра

void create_virtual_kernel();
void create_page_directory(u32 start_frame);
u32* create_page_table();
#ifdef PSE_MODE
void create_page_directory_with_pse(u32 start_frame, u32 count_list);
#else
void create_page_directory_without_pse(u32 start_frame, u32 count_list);
#endif

#endif //FYRFYROS_PAGE_TRANSLATOR_H
