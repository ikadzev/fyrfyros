//
// Created by modnick on 08.11.2024.
//

#ifndef FYRFYROS_KERNEL_ALLOCATOR_H
#define FYRFYROS_KERNEL_ALLOCATOR_H

#include "_flags.h"
#include "macroses.h"

#define KERNEL_SIZE_ADDRESS 4
#define KERNEL_COUNT_ARENAS 8
#define KERNEL_START_ALLOCATE 0x500000

#define KERNEL_ARENA_SIZE (384 * (1 << 10)) // 384KB
#define KERNEL_BLOCK_SIZE (8 * (1 << 10)) // 8KB

#define KERNEL_alignUpTo_SIZE_ADDRESS(a) (((a) + KERNEL_SIZE_ADDRESS - 1) / KERNEL_SIZE_ADDRESS * KERNEL_SIZE_ADDRESS)

typedef unsigned long size_t;
typedef struct {
    void* data;
    void* ptrs[KERNEL_COUNT_ARENAS];
    size_t lens[KERNEL_COUNT_ARENAS];
    size_t N;
} KERNEL_PullAllocator;
static KERNEL_PullAllocator KERNEL_ALLOCATOR;

void kernel_start_allocator();
void kernel_init_allocator(KERNEL_PullAllocator* allocator, size_t N);
void* kernel_malloc(size_t size);
void* kernel_calloc(size_t num, size_t size);
void* kernel_realloc(void* ptr, size_t new_size);
void kernel_free(void* ptr);
void kernel_memcpy(void* in, void* out, size_t size);
size_t kernel_get_size_block(void* finish, void* start);

#endif //FYRFYROS_KERNEL_ALLOCATOR_H
