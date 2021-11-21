#ifndef WHY_LIST_H
#define WHY_LIST_H

#include "why_lib.h"

typedef struct Sequence Sequence;

struct List
{
    void*       (*copy)();
    void        (*destroy)();

    Sequence*   head;
    Sequence*   tail;
    int_signed  size;
};

struct Sequence
{
    void*       data;
    Sequence*   next;
};

#endif