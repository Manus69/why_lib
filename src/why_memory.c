#include "why_memory.h"

void* memory_init(void* restrict destination, const void* restrict source, int_unsigned size)
{
    void* initial;

    if (!destination || !source)
        return destination;

    initial = destination;
    while (size)
    {
        *(byte *)destination = *(byte *)source;
        destination ++;
        source ++;
        size --;
    }

    return initial;
}

void* memory_set(void* object, byte value, int_unsigned size)
{
    void* initial;

    if (!object)
        return NULL;

    initial = object;
    while (size)
    {
        *(byte *)object = value;
        object ++;
        size --;
    }

    return initial;
}

void* memory_copy(void* restrict source, int_unsigned size)
{
    void* result;

    result = allocate(size);
    memory_init(result, source, size);

    return result;
}

void* allocate(int_unsigned size)
{
    void* result;

    result = malloc(size);
    if (!result)
        exit(EXIT_FAILURE);
    
    return result;
}

void* reallocate(const void* item, int_unsigned current_size, int_unsigned extra_size)
{
    void* new_item;

    new_item = allocate(current_size + extra_size);
    memory_init(new_item, item, current_size);

    return new_item;
}

void* memory_zero(int_unsigned size)
{
    void* object;

    object = allocate(size);
    memory_set(object, 0, size);

    return object;
}

void memory_destroy(void* item)
{
    free(item);
}