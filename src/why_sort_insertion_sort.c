#include "why_array_interface.h"

static int_signed _find_index(Array* array, int_signed left, int_signed right)
{
    while (left < right)
    {
        if (array_compare_elements(array, left, right) < 0)
            break ;
        
        left ++;
    }

    return left;
}

static void _swap_elements(Array* array, int_signed index, int_signed sorted_index)
{
    while (index < sorted_index)
    {
        array_swap(array, index, sorted_index);
        index ++;
    }
}

void _insert_sort_slice(Array* array, int_signed left, int_signed right)
{
    int_signed sorted_index;
    int_signed intended_index;

    sorted_index = left + 1;
    while (sorted_index <= right)
    {
        intended_index = _find_index(array, left, sorted_index);
        _swap_elements(array, intended_index, sorted_index);
        sorted_index ++;
    }
}

void array_sortI(Array* array, int_signed (*comapre)())
{
    int_signed size;

    if (!array)
        return ;
    
    if ((size = array_size(array)) < 2)
        return ;
    
    array_set_compare(array, comapre);
    _insert_sort_slice(array, 0, size - 1);
}