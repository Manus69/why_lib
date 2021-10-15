
#ifndef WHY_HEAP_INTERFACE_H
#define WHY_HEAP_INTERFACE_H

#include "why_definitions.h"

#define H_CAPACITY_DEFAULT (1 << 5)

typedef struct Array Heap;

#ifdef __cplusplus
    extern "C" {
#endif

Heap*   heap_create_with_capacity(void* (*copy)(), void (*destroy)(), int_signed (*compare)(), int_signed capacity);
Heap*   heap_create(void* (*copy)(), void (*destroy)(), int_signed (*compare)());
void    heap_destroy(Heap* heap);

bool    heap_push(Heap* heap, const void* item);
void*   heap_pop_root(Heap* heap);
void    heap_map(Heap* heap, void (*function)());
void    heap_sort(Heap* heap);

#ifdef __cplusplus
    }
#endif

#endif