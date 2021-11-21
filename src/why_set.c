#include "why_lib.h"

Set* set_create(void* (*copy)(), void (*destroy)(), int_signed (*compare)())
{
    return tree_create_avl(copy, destroy, compare);
}

void set_destroy(Set* set)
{
    return tree_destroy(set);
}

int_signed set_get_size(const Set* set)
{
    if (!set)
        return 0;
    
    return tree_get_size(set);
}

bool set_insert(Set* set, const void* item)
{
    return tree_insert(set, item);
}

void* set_find(const Set* set, const void* item)
{
    return tree_find(set, item);
}

void* set_remove(Set* set, const void* item)
{
    return tree_remove(set, item);
}

void* set_pop_min(Set* set)
{
    return tree_pop_min(set);
}