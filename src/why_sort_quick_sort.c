#include "why_array_interface.h"
#include "why_definitions.h"
#include "why_math.h"

#define THRESHOLD (1 << 3)

//pivot is on the right
static int_signed _fix_pivot(Array* array, int_signed left, int_signed right)
{
    while (left < right)
    {
        while (array_compare_elements(array, left, right) < 0)
        {
            if (right - left > 1)
                array_swap(array, right - 1, right);
            array_swap(array, left, right);

            right --;
        }
        left ++;
    }

    return right;
}

void _sort_slice(Array* array, int_signed left, int_signed right)
{
    int_signed pivot_index;

    if (left >= right)
        return ;

    if (right - left <= THRESHOLD)
        return _bubble_sort_slice(array, left, right);

    pivot_index = random_in_range(left, right + 1);
    array_swap(array, pivot_index, right);
    pivot_index = _fix_pivot(array, left, right);

    _sort_slice(array, left, pivot_index - 1);
    _sort_slice(array, pivot_index + 1, right);
}

static int_signed _find_next_lesser_element(Array* array, int_signed left, int_signed right, int_signed pivot)
{
    while (left <= right)
    {
        if (array_compare_elements(array, left, pivot) > 0)
            return left;
        
        left ++;
    }

    return NOT_FOUND;
}

static int_signed _find_next_greater_element(Array* array, int_signed left, int_signed right, int_signed pivot)
{
    while (left <= right)
    {
        if (array_compare_elements(array, left, pivot) < 0)
            return left;
        
        left ++;
    }

    return NOT_FOUND;
}

static void _sort_slice2(Array* array, int_signed left, int_signed right)
{
    int_signed pivot;
    int_signed j;
    int_signed k;

    if (right <= left)
        return ;
    
    if (right - left <= THRESHOLD)
        return _bubble_sort_slice(array, left, right);

    pivot = random_in_range(left + 1, right);
    j = left;
    k = pivot + 1;

    while (true)
    {
        j = _find_next_greater_element(array, j, pivot - 1, pivot);
        k = _find_next_lesser_element(array, k, right, pivot);

        if (j == NOT_FOUND && k == NOT_FOUND)
            break ;
        else if (j == NOT_FOUND)
        {
            array_swap(array, pivot, right);
            pivot = _fix_pivot(array, pivot, right);

            break;
        }
        else if (k == NOT_FOUND)
        {
            pivot = _fix_pivot(array, left, pivot);
            break ;
        }

        array_swap(array, j, k);
        j ++;
        k ++;
    }

    _sort_slice2(array, left, pivot - 1);
    _sort_slice2(array, pivot + 1, right);
}

void array_sortQ(Array* array, int_signed (*comapre)())
{
    int_signed size;

    if (!array)
        return ;
    
    if ((size = array_size(array)) < 2)
        return ;
    
    random_seed(0);
    array_set_compare(array, comapre);
    // _sort_slice(array, 0, size - 1);
    _sort_slice2(array, 0, size - 1);
}