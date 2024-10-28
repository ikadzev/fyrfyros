//
// Created by modnick on 25.10.2024.
//

#ifndef FYRFYROS_VA_LIST_H
#define FYRFYROS_VA_LIST_H
typedef struct va_list {
    void* now_address;
} va_list;

#define va_start(va_l, last_arg)    va_l.now_address = &last_arg + 1
#define va_arg(va_l, type)          *((type*)va_l.now_address); \
                                    va_l.now_address = (void*)((char*)va_l.now_address + sizeof(type)  +  (sizeof(type) % 4 == 0 ? 0:4 - sizeof(type) % 4))
//#define va_end(va_l)
#endif //FYRFYROS_VA_LIST_H
