#include "why_lib.h"
#include "why_hash_table.h"

#define HASHT_MIN_CAPACITY  (661)

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

HashTable* _hash_table_create_force_capacity(void* (*copy)(), void (*destroy)(), int_unsigned (*hash)(), int_unsigned capacity)
{
    HashTable* table;

    table = allocate(sizeof(HashTable));
    table->copy = copy;
    table->destroy = destroy;
    table->hash = hash;
    table->capacity = capacity;
    table->number_of_items = 0;
    table->items = _get_items(copy, destroy, table->capacity);

    return table;
}

HashTable* hash_table_create(void* (*copy)(), void (*destroy)(), int_unsigned (*hash)(), int_unsigned capacity)
{
    capacity = capacity < HASHT_MIN_CAPACITY ? HASHT_MIN_CAPACITY : get_next_prime(capacity);

    return _hash_table_create_force_capacity(copy, destroy, hash, capacity);
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

int_unsigned hash_table_capacity(const HashTable* table)
{
    return table->capacity;
}

int_signed hash_table_number_of_items(const HashTable* table)
{
    return table->number_of_items;
}

void* hash_table_at(const HashTable* table, int_unsigned n)
{
    return table->items[n];
}

bool hash_table_is_in_at_index(const HashTable* table, const void* item, int_signed (*compare)(), int_unsigned index)
{
    if (list_find(table->items[index], item, compare) == NULL)
        return false;
    
    return true;
}

bool hash_table_is_in_hashed(const HashTable* table, const void* item, int_signed (*compare)(), int_unsigned hash_value)
{
    int_unsigned index;

    index = hash_value % table->capacity;

    return hash_table_is_in_at_index(table, item, compare, index);
}

bool hash_table_is_in(const HashTable* table, const void* item, int_signed (*compare)())
{
    int_unsigned index;

    if (!table)
        return false;
    
    index = table->hash(item) % table->capacity;
    
    return hash_table_is_in_at_index(table, item, compare, index);
}

bool hash_table_insert_at_index(HashTable* table, const void* item, int_signed (*compare)(), int_unsigned index)
{
    if (list_find(table->items[index], item, compare))
        return false;
    
    list_push_back(table->items[index], item);
    table->number_of_items ++;

    return true;
}

bool hash_table_insert_hashed(HashTable* table, const void* item, int_signed (*compare)(), int_unsigned hash_value)
{
    int_unsigned index;

    index = hash_value % table->capacity;

    return hash_table_insert_at_index(table, item, compare, index);
}

bool hash_table_insert(HashTable* table, const void* item, int_signed (*compare)())
{
    int_unsigned index;

    index = table->hash(item) % table->capacity;

    return hash_table_insert_at_index(table, item, compare, index);
}

void* hash_table_remove_at_index(HashTable* table, const void* item, int_signed (*compare)(), int_unsigned index)
{
    void* _item;

    _item = list_remove(table->items[index], item, compare);

    if (_item)
        table->number_of_items --;

    return _item; 
}

void* hash_table_remove_hashed(HashTable* table, const void* item, int_signed (*compare)(), int_unsigned hash_value)
{
    int_unsigned index;

    index = hash_value % table->capacity;

    return hash_table_remove_at_index(table, item, compare, index);
}

void* hash_table_remove(HashTable* table, const void* item, int_signed (*compare)())
{
    int_unsigned    index;

    index = table->hash(item) % table->capacity;

    return hash_table_remove_at_index(table, item, compare, index);
}