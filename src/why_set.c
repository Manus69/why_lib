#include "why_memory.h"
#include "why_hash_table_interface.h"
#include "why_hash_functions.h"

Set* set_create(void* (*copy)(), void (*destroy)(), int_unsigned (*hash)(), int_unsigned capacity)
{
    return hash_table_create(copy, destroy, hash, capacity);
}

void set_destroy(Set* set)
{
    return hash_table_destroy(set);
}

int_signed set_get_size(const Set* set)
{
    return hash_table_number_of_items(set);
}

bool set_insert(Set* set, const void* item, int_signed (*compare)())
{
    return hash_table_insert(set, item, compare);
}

void* set_remove(Set* set, const void* item, int_signed (*compare)())
{
    return hash_table_remove(set, item, compare);
}