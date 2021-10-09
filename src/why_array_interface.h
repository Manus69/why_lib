#ifndef WHY_ARRAY_INTERFACE_H
#define WHY_ARRAY_INTERFACE_H

#include "why_definitions.h"

#define A_CAPACITY_DEFAULT (1 << 5)
#define A_CAPACITY_MIN (1 << 2)

typedef struct Array Array;

#ifdef __cplusplus
    extern "C" {
#endif

Array*      array_create(void* (*copy)(), void (*destroy_)());
Array*      array_create_with_capacity(void* (copy)(), void (*destroy)(), int_signed capacity);
Array*      array_copy(const Array* array);
Array*      array_copy_with(const Array* array, void* (*copy_function)());
Array*      array_concat(Array* lhs, const Array* rhs);
Array*      array_concatG(Array* lhs, const Array* rhs, void* (copy)());
bool        array_push(Array* array, void* item);
bool        array_pushG(Array* array, void* item, void* (*copy)());
bool        array_push_frontG(Array* array, void* item, void* (*copy)());
bool        array_push_front(Array* array, void* item);
int_signed  array_size(const Array* array);
int_signed  array_get_capacity(const Array* array);
void*       array_at(const Array* array, int_signed index);
void*       array_set(Array* array, void* item, int_signed index);
void*       array_pop(Array* array);
void        array_map(Array* array, void (*function)());
void        array_swap(Array* array, int_signed m, int_signed n);
void        array_destroy(Array* array);
void        array_destroy_no_content(Array* array);
void        array_sortM(Array* array, int_signed (*compare)());
void        array_sortH(Array* array, int_signed (*compare)());

#ifdef __cplusplus
    }
#endif

#endif
