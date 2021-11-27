#include "why_lib.h"

void array_sortH(Array* array, int_signed (*compare)())
{
    if (!array || !compare)
        return ;
    
    if (array_size(array) < 2)
        return ;

    array_set_compare(array, compare);
    heap_sort(array);
}