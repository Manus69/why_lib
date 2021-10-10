#include "why_hash_table_interface.h"
#include "why_list_interface.h"
#include "why_hash_table.h"
#include "why_memory.h"
#include "why_math.h"

static void** _get_items(void* (*copy)(), void (*destroy)(), int_unsigned capacity)
{
    void**          items;
    int_unsigned    n;

    items = allocate(capacity * sizeof(void *));
    n = 0;

    while (n < capacity)
    {
        items[n] = list_create(copy, destroy);
        n ++;
    }

    return items;
}

HashTable* hash_table_create(void* (*copy)(), void (*destroy)(), int_unsigned (*hash)(), int_unsigned capacity)
{
    HashTable* table;

    table = allocate(sizeof(HashTable));
    table->copy = copy;
    table->destroy = destroy;
    table->hash = hash;
    capacity = capacity < HASHT_MIN_CAPACITY ? HASHT_MIN_CAPACITY : get_next_prime(capacity);
    table->items = _get_items(copy, destroy, capacity);

    return table;
}

void hash_table_destroy(HashTable* table)
{
    int_unsigned n;

    if (!table)
        return ;
    
    n = 0;
    while (n < table->capacity)
    {
        list_destroy(table->items[n]);
        n ++;
    }

    free(table->items);
    free(table);
}

bool hash_table_is_in(HashTable* table, void* item, int_signed (*compare)())
{
    int_unsigned index;

    if (!table)
        return false;
    
    index = table->hash(item);
    if (!list_find(table->items[index], item, compare))
        return false;
    
    return true;
}

bool hash_table_insert(HashTable* table, void* item, int_signed (*compare)())
{
    int_unsigned index;

    index = table->hash(item);
    if (list_find(table->items[index], item, compare))
        return false;
    
    list_push_back(table->items[index], item);

    return true;
}

void* hash_table_remove(HashTable* table, void* item, int_signed (*compare)())
{
    int_unsigned    index;
    void*           _item;

    index = table->hash(item);
    _item = list_remove(table->items[index], item, compare);

    return _item;
}