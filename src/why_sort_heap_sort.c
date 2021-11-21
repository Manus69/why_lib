#include "why_lib.h"
#include "why_array.h"

void array_sortH(Array* array, int_signed (*compare)())
{
    if (!array || !compare)
        return ;
    
    if (array_size(array) < 2)
        return ;

    array->compare = compare;
    heap_sort(array);
}