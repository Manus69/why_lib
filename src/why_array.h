#ifndef WHY_ARRAY_H
#define WHY_ARRAY_H

#include "why_lib.h"

struct Array
{
    void*       (*at)();
    void        (*set)();
    void        (*swap)();
    void*       (*copy)();
    void        (*destroy)();
    int_signed  (*compare)();

    void*       data;

    int_signed  capacity;
    int_signed  item_size;
    int_signed  left_index;
    int_signed  right_index;
};

#endif
