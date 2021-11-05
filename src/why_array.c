#include "why_array.h"
#include "why_array_interface.h"
#include "why_memory.h"
#include "why_macros.h"

static void** _get_array(int_signed size)
{
    void** array;

    array = allocate(sizeof(void *) * size);
    size --;
    while (size >= 0)
    {
        array[size] = NULL;
        size --;
    }

    return array;
}

Array* array_create_with_capacity(void* (copy)(), void (*destroy)(), int_signed capacity)
{
    Array* array;

    array = allocate(sizeof(Array));

    capacity = capacity < A_CAPACITY_MIN ? A_CAPACITY_MIN : capacity;

    array->items = _get_array(capacity);
    array->copy = copy;
    array->compare = NULL;
    array->destroy = destroy;

    array->left_index = capacity / 2;
    array->right_index = array->left_index + 1;
    array->capacity = capacity;

    return array;
}

Array* array_create(void* (*copy)(), void (*destroy)())
{
    return array_create_with_capacity(copy, destroy, A_CAPACITY_DEFAULT);
}

void array_map(Array* array, void (*function)())
{
    int_signed n;

    if (!array || !function)
        return ;
    
    n = array->left_index + 1;
    while (n < array->right_index)
    {
        function(array->items[n]);
        n ++;
    }
}

static void _destroy_items(Array* array)
{
    if (!array)
        return ;
    
    array_map(array, array->destroy);
}

void array_destroy(Array* array)
{
    if (!array)
        return ;
    
    _destroy_items(array);
    free(array->items);
    free(array);
}

void array_destroy_no_content(Array* array)
{
    if (!array)
        return ;
    
    free(array->items);
    free(array);
}

void* array_at(const Array* array, int_signed index)
{
    if (!array)
        return NULL;
    
    return array->items[array->left_index + index + 1];
}

int_signed array_size(const Array* array)
{
    if (!array)
        return 0;
    
    return array->right_index - array->left_index - 1;
}

int_signed array_get_capacity(const Array* array)
{
    if (!array)
        return 0;
    
    return array->capacity;
}

void* array_set(Array* array, void* item, int_signed index)
{
    void* return_value;

    if (!array)
        return NULL;
    
    return_value = array_at(array, index);
    array->items[array->left_index + index + 1] = item;

    return return_value;
}

static bool _reallocate_array(Array* array)
{
    int_signed  new_capacity;
    int_signed  left_index;
    int_signed  right_index;
    int_signed  n_items;
    void**      new_array;

    new_capacity = array->capacity * 2;
    new_array = _get_array(new_capacity);
    n_items = array_size(array);

    left_index = (new_capacity - n_items) / 2;
    right_index = left_index + n_items + 1;

    memory_init(new_array + left_index + 1, array->items + array->left_index + 1, n_items * sizeof(void *));

    free(array->items);
    array->items = new_array;
    array->left_index = left_index;
    array->right_index = right_index;
    array->capacity = new_capacity;

    return TRUE;
}

bool array_pushG(Array* array, const void* item, void* (*copy)())
{
    if (array->right_index == array->capacity)
        _reallocate_array(array);
    
    array->items[array->right_index] = copy(item);
    array->right_index ++;

    return TRUE;
}

bool array_push_frontG(Array* array, const void* item, void* (*copy)())
{
    if (array->left_index == 0)
        _reallocate_array(array);
    
    array->items[array->left_index] = copy(item);
    array->left_index --;

    return TRUE;
}

bool array_push(Array* array, const void* item)
{
    return array_pushG(array, item, array->copy);
}

bool array_push_front(Array* array, const void* item)
{
    return array_push_frontG(array, item, array->copy);
}

void* array_pop(Array* array)
{
    void* item;

    if (array_size(array) == 0)
        return NULL;
    
    array->right_index --;
    item = array->items[array->right_index];

    return item;
}

void* array_pop_front(Array* array)
{
    void* item;

    if (array_size(array) == 0)
        return NULL;
    
    array->left_index ++;
    item = array->items[array->left_index];

    return item;
}

void array_swap(Array* array, int_signed m, int_signed n)
{
    SWAP(array->items[array->left_index + m + 1], array->items[array->left_index + n + 1], void *);
}

Array* array_copy_with(const Array* array, void* (*copy_function)())
{
    Array*      copy;
    void*       item;
    int_signed  n;
    int_signed  length;

    if (!array)
        return NULL;
    
    copy = array_create(array->copy, array->destroy);
    n = array->left_index + 1;
    length = array->right_index;
    while (n < length)
    {
        item = copy_function(array->items[n]);
        array_push(copy, item);

        n ++;
    }

    return copy;
}

Array* array_copy(const Array* array)
{
    return array_copy_with(array, array->copy);
}

Array* array_concatG(Array* lhs, const Array* rhs, void* (copy)())
{
    int_signed n;

    if (!lhs)
        return array_copy(rhs);

    n = rhs->left_index + 1;
    while (n < rhs->right_index)
    {
        array_pushG(lhs, array_at(rhs, n), copy);

        n ++;
    }

    return lhs;
}

Array* array_concat(Array* lhs, const Array* rhs)
{
    return array_concatG(lhs, rhs, rhs->copy);
}

void* array_findCMP(const Array* array, const void* item, int_signed (*comapre)())
{
    int_signed  n;
    void*       current;

    if (!array)
        return NULL;
    
    n = 0;
    while (n < array_size(array))
    {
        current = array_at(array, n);

        if (comapre(current, item) == 0)
            return current;
        
        n ++;
    }

    return NULL;
}

void* array_find(const Array* array, const void* item)
{
    if (!array || !array->compare)
        return NULL;
    
    return array_findCMP(array, item, array->compare);
}

void* array_first(const Array* array)
{
    if (array_size(array))
        return array_at(array, 0);
    
    return NULL;
}

void* array_last(const Array* array)
{
    if (array_size(array))
        return array_at(array, array_size(array) - 1);
    
    return NULL;
}