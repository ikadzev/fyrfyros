#include "headers/kernel_allocator.h"

void kernel_start_allocator() {
    size_t N = 7;
    kernel_init_allocator(&ALLOCATOR, COUNT_ARENAS - 1);
}

void kernel_init_allocator(PullAllocator* allocator, size_t N) {
    allocator->data = (void*)START_ALLOCATE;
    for (int i = 0; i < COUNT_ARENAS; ++i) {
        allocator->ptrs[i] = NULL;
        allocator->lens[i] = 0;
    }
    allocator->N = N;
}

void* kernel_malloc(size_t size) {
    size = alignUpTo4(size);
    if (!size || size > BLOCK_SIZE)
        return NULL;

    size_t data_ind = size / SIZE_ADDRESS - 1;
    if (data_ind >= ALLOCATOR.N) {
        size = BLOCK_SIZE;
        data_ind = ALLOCATOR.N;
    }

    if (ALLOCATOR.ptrs[data_ind] == NULL) {
        if (ALLOCATOR.lens[data_ind] != ARENA_SIZE / size) {
            size_t offset = data_ind * ARENA_SIZE + size * ALLOCATOR.lens[data_ind]++;
            return &((char*) ALLOCATOR.data)[offset];
        } else {
            return NULL;
        }
    } else {
        void* res = ALLOCATOR.ptrs[data_ind];
        ALLOCATOR.ptrs[data_ind] = *((void**) res);
        return res;
    }
}

void* kernel_calloc(size_t num, size_t size){
    void* ptr = kernel_malloc(num * size);
    if (ptr == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < num * size; ++i) {
        ((char*)ptr)[i] = 0;
    }
    return ptr;
}

void* kernel_realloc(void* ptr, size_t new_size) {
    if (ptr == NULL)
        return kernel_malloc(new_size);

    new_size = alignUpTo4(new_size);
    size_t old_size = get_size_block(ptr, ALLOCATOR.data) * SIZE_ADDRESS + SIZE_ADDRESS;

    if (new_size > ALLOCATOR.N * SIZE_ADDRESS)
        new_size = BLOCK_SIZE;
    if (old_size > ALLOCATOR.N * SIZE_ADDRESS)
        old_size = BLOCK_SIZE;

    if (new_size == old_size)
        return ptr;

    void* res = kernel_malloc(new_size);
    if (res == NULL)
        return NULL;

    kernel_memcpy(res, ptr, MIN(old_size, new_size));
    kernel_free(ptr);
    return res;
}

void kernel_free(void* ptr) {
    if (ptr == NULL)
        return;

    size_t data_ind = get_size_block(ptr, ALLOCATOR.data);
    *((void**) ptr) = ALLOCATOR.ptrs[data_ind];
    ALLOCATOR.ptrs[data_ind] = ptr;
}

void kernel_memcpy(void* in, void* out, size_t size){
    for (size_t i = 0; i < size; ++i) {
        *((char*)in) = *((char*)out);
    }
}

size_t get_size_block(void* finish, void* start) {
    return (size_t) ((char*) finish - (char*) start) / ARENA_SIZE;
}