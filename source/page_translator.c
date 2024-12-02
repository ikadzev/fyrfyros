//
// Created by rostyan on 03.12.2024.
//

#include "headers/page_translator.h"


void init_virtual_address() {

}

void init_virtual_kernel() {

}

void create_page_directory(u32 start_frame) {

}

u32* create_page_table() {
    void* base_page = kernel_malloc(SIZE_TABLE);
}


void create_page_directory_with_pse(u32 start_frame, u32 count_list);
void create_page_directory_without_pse(u32 start_frame, u32 count_list);
