#ifndef WHY_SET_INTERFACE_H
#define WHY_SET_INTERFACE_H

#include "why_definitions.h"

Set*        set_create(void* (*copy)(), void (*destroy)(), int_signed (*compare)());
void        set_destroy(Set* set);
int_signed  set_get_size(const Set* set);
bool        set_insert(Set* set, const void* item);
void*       set_find(const Set* set, const void* item);
void*       set_remove(Set* set, const void* item);
void*       set_pop_min(Set* set);

#endif