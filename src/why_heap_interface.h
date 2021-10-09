
#ifndef WHY_HEAP_INTERFACE_H
#define WHY_HEAP_INTERFACE_H

#include "why_definitions.h"

#define H_CAPACITY_DEFAULT (1 << 1)

typedef struct Array Heap;

#ifdef __cplusplus
    extern "C" {
#endif

Heap*   heap_create(void* (*copy)(), void (*destroy)(), int_signed (*compare)());
void    heap_destroy(Heap* heap);

bool    heap_push(Heap* heap, void* item);
void*   heap_pop_root(Heap* heap);
void    heap_map(Heap* heap, void (*function)());
void    heap_sort(Heap* heap);

#ifdef __cplusplus
    }
#endif

#endif