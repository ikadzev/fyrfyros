#include "headers/kernel_allocator.h"

void kernel_start_allocator() {
    kernel_init_allocator(&KERNEL_ALLOCATOR, KERNEL_COUNT_ARENAS - 1);
}

void kernel_init_allocator(KERNEL_PullAllocator* allocator, size_t N) {
    allocator->data = (void*)KERNEL_START_ALLOCATE;
    for (u32 i = 0; i < KERNEL_COUNT_ARENAS; ++i) {
        allocator->ptrs[i] = NULL;
        allocator->lens[i] = 0;
    }
    allocator->N = N;
}

void* kernel_malloc(size_t size) {
    size = KERNEL_alignUpTo_SIZE_ADDRESS(size);
    if (!size || size > KERNEL_BLOCK_SIZE)
        return NULL;

    size_t data_ind = size / KERNEL_SIZE_ADDRESS - 1;
    if (data_ind >= KERNEL_ALLOCATOR.N) {
        size = KERNEL_BLOCK_SIZE;
        data_ind = KERNEL_ALLOCATOR.N;
    }

    if (KERNEL_ALLOCATOR.ptrs[data_ind] == NULL) {
        if (KERNEL_ALLOCATOR.lens[data_ind] != KERNEL_ARENA_SIZE / size) {
            size_t offset = data_ind * KERNEL_ARENA_SIZE + size * KERNEL_ALLOCATOR.lens[data_ind]++;
            return &((byte*) KERNEL_ALLOCATOR.data)[offset];
        } else {
            return NULL;
        }
    } else {
        void* res = KERNEL_ALLOCATOR.ptrs[data_ind];
        KERNEL_ALLOCATOR.ptrs[data_ind] = *((void**) res);
        return res;
    }
}

void* kernel_calloc(size_t num, size_t size) {
    void* ptr = kernel_malloc(num * size);
    if (ptr == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < num * size; ++i) {
        ((byte*)ptr)[i] = 0;
    }
    return ptr;
}

void* kernel_realloc(void* ptr, size_t new_size) {
    if (ptr == NULL)
        return kernel_malloc(new_size);

    new_size = KERNEL_alignUpTo_SIZE_ADDRESS(new_size);
    size_t old_size = kernel_get_size_block(ptr, KERNEL_ALLOCATOR.data) * KERNEL_SIZE_ADDRESS + KERNEL_SIZE_ADDRESS;

    if (new_size > KERNEL_ALLOCATOR.N * KERNEL_SIZE_ADDRESS)
        new_size = KERNEL_BLOCK_SIZE;
    if (old_size > KERNEL_ALLOCATOR.N * KERNEL_SIZE_ADDRESS)
        old_size = KERNEL_BLOCK_SIZE;

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

    size_t data_ind = kernel_get_size_block(ptr, KERNEL_ALLOCATOR.data);
    *((void**) ptr) = KERNEL_ALLOCATOR.ptrs[data_ind];
    KERNEL_ALLOCATOR.ptrs[data_ind] = ptr;
}

void kernel_memcpy(void* in, void* out, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        ((byte*)in)[i] = ((byte*)out)[i];
    }
}

size_t kernel_get_size_block(void* finish, void* start) {
    return (size_t) ((byte*) finish - (byte*) start) / KERNEL_ARENA_SIZE;
}