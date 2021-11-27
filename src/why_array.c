#include "why_array.h"

int_signed _index_relative_to_abs(const Array* array, int_signed index)
{
    return array->left_index + index + 1;
}

int_signed _index_abs_to_relative(const Array* array, int_signed index)
{
    return index - array->left_index - 1;
}

void* _array_get_data(const Array* array)
{
    return array->data;
}

void _array_set_data(Array* array, const void* data)
{
    array->data = (void *)data;
}

int_signed array_size(const Array* array)
{
    if (!array)
        return 0;
    
    return array->right_index - array->left_index - 1;
}

void _array_shift_right_brk(Array* array, int_signed shift)
{
    array->right_index += shift;
}

int_signed _array_get_right_brk(const Array* array)
{
    return array->right_index;
}

int_signed array_get_capacity(const Array* array)
{
    if (!array)
        return 0;
    
    return array->capacity;
}

void* _array_at(const Array* array, int_signed n)
{
    return array->at(array, n);
}

void* array_at(const Array* array, int_signed index)
{
    if (!array)
        return NULL;
    
    return _array_at(array, _index_relative_to_abs(array, index));
}

void _array_set(Array* array, const void* item, int_signed index)
{
    array->set(array, item, index);
}

void* array_set(Array* array, const void* item, int_signed index)
{
    void* return_value;

    if (!array)
        return NULL;
    
    index = _index_relative_to_abs(array, index);
    return_value = _array_at(array, index);
    _array_set(array, array->copy(item), index);

    return return_value;
}

static bool _reallocate_array(Array* array)
{
    int_signed  new_capacity;
    int_signed  left_index;
    int_signed  right_index;
    int_signed  n_items;
    void*       new_array;

    new_capacity = array->capacity * 2;
    new_array = _get_array(new_capacity, array->item_size);
    n_items = array_size(array);

    left_index = (new_capacity - n_items) / 2;
    right_index = left_index + n_items + 1;

    memory_init(new_array + (left_index + 1) * array->item_size, 
                array->data + (array->left_index + 1) * array->item_size, n_items * array->item_size);

    free(array->data);
    array->data = new_array;
    array->left_index = left_index;
    array->right_index = right_index;
    array->capacity = new_capacity;

    return TRUE;
}

bool array_pushG(Array* array, const void* item, void* (*copy)())
{
    if (array->right_index == array->capacity)
        _reallocate_array(array);
    
    _array_set(array, copy(item), array->right_index);
    array->right_index ++;

    return TRUE;
}

bool array_push_frontG(Array* array, const void* item, void* (*copy)())
{
    if (array->left_index == 0)
        _reallocate_array(array);
    
    _array_set(array, copy(item), array->left_index);
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
    item = _array_at(array, array->right_index);

    return item;
}

void* array_pop_front(Array* array)
{
    void* item;

    if (array_size(array) == 0)
        return NULL;
    
    array->left_index ++;
    item = _array_at(array, array->left_index);

    return item;
}

void array_swap(Array* array, int_signed m, int_signed n)
{
    array->swap(array, _index_relative_to_abs(array, m), _index_relative_to_abs(array, n));
}

void array_map(Array* array, void (*function)())
{
    int_signed  n;
    void*       item;

    if (!array || !function)
        return ;
    
    n = array->left_index + 1;
    while (n < array->right_index)
    {
        item = _array_at(array, n);
        function(item);
        n ++;
    }
}

Array* array_copy_with(const Array* array, void* (*copy_function)())
{
    Array*      copy;
    void*       item;
    int_signed  left;
    int_signed  size;

    if (!array)
        return NULL;
    
    copy = memory_copy(array, sizeof(Array));
    copy->data = _get_array(array->capacity, array->item_size);
    if ((size = array_size(array)) == 0)
        return copy;

    left = _index_relative_to_abs(array, 0);

    while (size)
    {
        item = copy_function(_array_at(array, left));
        _array_set(copy, item, left);

        left ++;
        size --;
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

void array_set_compare(Array* array, int_signed (*compare)())
{
    if (!array)
        return ;
    
    array->compare = compare;
}

int_signed array_compare_elements(const Array* array, int_signed left, int_signed right)
{
    return array->compare(array_at(array, left), array_at(array, right));
}