#include "why_hash_table_interface.h"
#include "why_hash_table.h"
#include "why_array_interface.h"
#include "why_list_interface.h"

int_unsigned _hash_table_count_collisions(HashTable* table)
{
    int_unsigned    count;
    int_unsigned    n;
    int_signed      n_items;

    count = 0;
    n = 0;
    while (n < table->capacity)
    {
        n_items = list_length(table->items[n]);
        if (n_items > 1)
            count += n_items - 1;

        n ++;
    }

    return count;
}
