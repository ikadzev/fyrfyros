//
// Created by rostyan on 03.12.2024.
//

#ifndef FYRFYROS_PAGE_ALLOCATOR_H
#define FYRFYROS_PAGE_ALLOCATOR_H

#include "macroses.h"

#define PAGE_SIZE_ADDRESS 4
#define PAGE_COUNT_ARENAS 1
#define PAGE_BLOCK_SIZE 4                                        // 4B
#define PAGE_ARENA_SIZE 0x400000                                 // 4MB
#define PAGE_START_ALLOCATE 0x100000                             // 1MB
#define PAGE_END_ALLOCATE PAGE_START_ALLOCATE + PAGE_ARENA_SIZE  // 5MB

#define PAGE_alignUpTo_SIZE_ADDRESS(a) (((a) + PAGE_SIZE_ADDRESS - 1) / PAGE_SIZE_ADDRESS * PAGE_SIZE_ADDRESS)

typedef unsigned long size_t;
typedef struct {
    void* data;
    void* ptrs[PAGE_COUNT_ARENAS];
    size_t lens[PAGE_COUNT_ARENAS];
    size_t N;
} PAGE_PullAllocator;
static PAGE_PullAllocator PAGE_ALLOCATOR;

void page_start_allocator();
void page_init_allocator(PAGE_PullAllocator* allocator, size_t N);
void* page_malloc(size_t size);
void* page_calloc(size_t num, size_t size);
void* page_realloc(void* ptr, size_t new_size);
void page_free(void* ptr);
void page_memcpy(void* in, void* out, size_t size);
size_t page_get_size_block(void* finish, void* start);

#endif //FYRFYROS_PAGE_ALLOCATOR_H