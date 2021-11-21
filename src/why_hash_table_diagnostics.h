#ifndef WHY_HASH_TABLE_DIAGNOSTICS_H
#define WHY_HASH_TABLE_DIAGNOSTICS_H

#include "why_lib.h"

int_unsigned    _hash_table_count_collisions(const HashTable* table);
Array*          _hash_table_get_distribution(const HashTable* table);

#endif