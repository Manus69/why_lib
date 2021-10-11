#ifndef WHY_HASH_TABLE_INTERFACE_H
#define WHY_HASH_TABLE_INTERFACE_H

#include "why_definitions.h"

#define HASHT_MIN_CAPACITY (661)

typedef struct HashTable HashTable;

#ifdef __cplusplus
    extern "C" {
#endif

HashTable*      hash_table_create(void* (*copy)(), void (*destroy)(), int_unsigned (*hash)(), int_unsigned capacity);
void            hash_table_destroy(HashTable* table);
int_unsigned    hash_table_capacity(const HashTable* table);
void*           hash_table_at(const HashTable* table, int_unsigned n);
bool            hash_table_is_in(HashTable* table, void* item, int_signed (*compare)());
bool            hash_table_insert(HashTable* table, void* item, int_signed (*compare)());
void*           hash_table_remove(HashTable* table, void* item, int_signed (*compare)());

#ifdef __cplusplus
    }
#endif

#endif
