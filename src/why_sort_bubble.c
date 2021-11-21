#include "why_lib.h"

void _bubble_sort_slice(Array* array, int_signed left, int_signed right)
{
    int_signed sorted_index;
    int_signed index;

    sorted_index = right;
    while (left < sorted_index)
    {
        index = left;
        while (index < sorted_index)
        {
            if (array_compare_elements(array, index, index + 1) < 0)
                array_swap(array, index, index + 1);
            
            index ++;
        }

        sorted_index --;
    }
}

void array_sortB(Array* array, int_signed (*compare)())
{
    int_signed size;

    if (!array)
        return ;
    
    if ((size = array_size(array)) < 2)
        return ;

    array_set_compare(array, compare);
    _bubble_sort_slice(array, 0, size - 1);
}