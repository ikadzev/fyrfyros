//
// Created by rostyan on 03.12.2024.
//

#include "headers/page_allocator.h"

void page_start_allocator() {
    page_init_allocator(&PAGE_ALLOCATOR, PAGE_COUNT_ARENAS - 1);
}

void page_init_allocator(PAGE_PullAllocator* allocator, size_t N) {
    allocator->data = (void*)PAGE_START_ALLOCATE;
    for (u32 i = 0; i < PAGE_COUNT_ARENAS; ++i) {
        allocator->ptrs[i] = NULL;
        allocator->lens[i] = 0;
    }
    allocator->N = N;
}

u32 page_malloc(size_t size) {
    size = PAGE_alignUpTo_SIZE_ADDRESS(4 * size);
    if (!size || size > PAGE_BLOCK_SIZE)
        return NULL;

    size_t data_ind = size / PAGE_SIZE_ADDRESS - 1;
    if (data_ind >= PAGE_ALLOCATOR.N) {
        size = PAGE_BLOCK_SIZE;
        data_ind = PAGE_ALLOCATOR.N;
    }

    if (PAGE_ALLOCATOR.ptrs[data_ind] == NULL) {
        if (PAGE_ALLOCATOR.lens[data_ind] != PAGE_ARENA_SIZE / size) {
            size_t offset = data_ind * PAGE_ARENA_SIZE + size * PAGE_ALLOCATOR.lens[data_ind]++;
            return (u32)&((byte*) PAGE_ALLOCATOR.data)[offset];
        } else {
            return NULL;
        }
    } else {
        void* res = PAGE_ALLOCATOR.ptrs[data_ind];
        PAGE_ALLOCATOR.ptrs[data_ind] = *((void**) res);
        return (u32)res;
    }
}

u32 page_calloc(size_t num, size_t size) {
    u32 ptr = page_malloc(num * 4);
    if (ptr == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < num * size; ++i) {
        ((byte*)ptr)[i] = 0;
    }
    return ptr;
}

void page_free(u32 ptr) {
    if (ptr == NULL)
        return;

    size_t data_ind = page_get_size_block((void*)ptr, PAGE_ALLOCATOR.data);
    *((void**) ptr) = PAGE_ALLOCATOR.ptrs[data_ind];
    PAGE_ALLOCATOR.ptrs[data_ind] = (void*)ptr;
}

void page_memcpy(void* in, void* out, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        ((byte*)in)[i] = ((byte*)out)[i];
    }
}

size_t page_get_size_block(void* finish, void* start) {
    return (size_t) ((byte*) finish - (byte*) start) / PAGE_ARENA_SIZE;
}