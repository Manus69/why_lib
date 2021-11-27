#ifndef WHY_ARRAY_H
#define WHY_ARRAY_H

#include "why_lib.h"

struct Array
{
    void*       (*at)(const Array* array, int_signed n);
    void        (*set)(Array* array, const void* item, int_signed);
    void        (*swap)(Array* array, int_signed n, int_signed m);
    void*       (*copy)();
    void        (*destroy)();
    int_signed  (*compare)();

    void*       data;

    int_signed  capacity;
    int_signed  item_size;
    int_signed  left_index;
    int_signed  right_index;
};

int_signed  _index_relative_to_abs(const Array* array, int_signed index);
void*       _get_array(int_signed size, int_signed item_size);
void*       _array_at(const Array* array, int_signed n);
void        _array_set(Array* array, const void* item, int_signed index);
void*       array_value_at(const Array* array, int_signed n);
void        array_value_set(Array* array, const void* value, int_signed n);
void        array_value_swap(Array* array, int_signed n, int_signed m);
void*       array_pointer_at(const Array* array, int_signed n);
void        array_pointer_set(Array* array, const void* item, int_signed n);
void        array_pointer_swap(Array* array, int_signed n, int_signed m);

#endif
