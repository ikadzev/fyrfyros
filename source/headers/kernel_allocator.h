//
// Created by modnick on 08.11.2024.
//

#ifndef FYRFYROS_KERNEL_ALLOCATOR_H
#define FYRFYROS_KERNEL_ALLOCATOR_H

#include "macroses.h"

#define TRUE 1
#define FALSE 0
#define NULL 0
#define DEBUG_MODE 0
#define SIZE_ADDRESS 4
#define COUNT_ARENAS 8
#define START_ALLOCATE 0x100000

#define ARENA_SIZE (384 * (1 << 10)) // 384KB
#define BLOCK_SIZE (8 * (1 << 10)) // 8KB

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define alignUpTo4(a) (((a) + SIZE_ADDRESS - 1) / SIZE_ADDRESS * SIZE_ADDRESS)

typedef unsigned long size_t;
typedef struct {
    void* data;
    void* ptrs[COUNT_ARENAS];
    size_t lens[COUNT_ARENAS];
    size_t N;
} PullAllocator;
static PullAllocator ALLOCATOR;

void kernel_start_allocator();
void kernel_init_allocator(PullAllocator* allocator, size_t N);
void* kernel_malloc(size_t size);
void* kernel_calloc(size_t num, size_t size);
void* kernel_realloc(void* ptr, size_t new_size);
void kernel_free(void* ptr);
void kernel_memcpy(void* in, void* out, size_t size);
size_t get_size_block(void* finish, void* start);

#endif //FYRFYROS_KERNEL_ALLOCATOR_H
