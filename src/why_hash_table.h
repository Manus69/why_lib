#ifndef WHY_HASH_TABLE_H
#define WHY_HASH_TABLE_H

#include "why_hash_table_interface.h"

struct HashTable
{
    void*           (*copy)();
    void            (*destroy)();
    int_unsigned    (*hash)();

    void**          items;
    int_unsigned    capacity;
    int_signed      number_of_items;
};

#endif