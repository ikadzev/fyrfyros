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

void* page_malloc(size_t size) {
    size = PAGE_alignUpTo_SIZE_ADDRESS(size);
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
            return &((byte*) PAGE_ALLOCATOR.data)[offset];
        } else {
            return NULL;
        }
    } else {
        void* res = PAGE_ALLOCATOR.ptrs[data_ind];
        PAGE_ALLOCATOR.ptrs[data_ind] = *((void**) res);
        return res;
    }
}

void* page_calloc(size_t num, size_t size) {
    void* ptr = page_malloc(num * size);
    if (ptr == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < num * size; ++i) {
        ((byte*)ptr)[i] = 0;
    }
    return ptr;
}

void* page_realloc(void* ptr, size_t new_size) {
    if (ptr == NULL)
        return page_malloc(new_size);

    new_size = PAGE_alignUpTo_SIZE_ADDRESS(new_size);
    size_t old_size = page_get_size_block(ptr, PAGE_ALLOCATOR.data) * PAGE_SIZE_ADDRESS + PAGE_SIZE_ADDRESS;

    if (new_size > PAGE_ALLOCATOR.N * PAGE_SIZE_ADDRESS)
        new_size = PAGE_BLOCK_SIZE;
    if (old_size > PAGE_ALLOCATOR.N * PAGE_SIZE_ADDRESS)
        old_size = PAGE_BLOCK_SIZE;

    if (new_size == old_size)
        return ptr;

    void* res = page_malloc(new_size);
    if (res == NULL)
        return NULL;

    page_memcpy(res, ptr, MIN(old_size, new_size));
    page_free(ptr);
    return res;
}

void page_free(void* ptr) {
    if (ptr == NULL)
        return;

    size_t data_ind = page_get_size_block(ptr, PAGE_ALLOCATOR.data);
    *((void**) ptr) = PAGE_ALLOCATOR.ptrs[data_ind];
    PAGE_ALLOCATOR.ptrs[data_ind] = ptr;
}

void page_memcpy(void* in, void* out, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        ((byte*)in)[i] = ((byte*)out)[i];
    }
}

size_t page_get_size_block(void* finish, void* start) {
    return (size_t) ((byte*) finish - (byte*) start) / PAGE_ARENA_SIZE;
}