#ifndef WHY_ARRAY_H
#define WHY_ARRAY_H

#include "why_definitions.h"

struct Array
{
    void*       (*copy)();
    void        (*destroy)();
    int_signed  (*compare)();

    void**      items;

    int_signed  capacity;
    int_signed  left_index;
    int_signed  right_index;
};

#endif
