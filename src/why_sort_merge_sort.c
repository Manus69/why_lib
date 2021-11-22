#include "why_lib.h"
#include "why_array.h"

struct _slice
{
    void**      items;
    int_signed  left_index;
    int_signed  right_index;
};

static int_signed _slice_size(struct _slice* slice)
{
    return slice->right_index - slice->left_index;
}

struct _slice _slice_init(void** items, int_signed left_index, int_signed right_index)
{
    struct _slice slice;

    slice.items = items;
    slice.left_index = left_index;
    slice.right_index = right_index;

    return slice;
}

struct _slice _get_slice(struct _slice* source, int_signed size)
{
    struct _slice   slice;
    int_signed      source_size;

    source_size = _slice_size(source);
    size = size > source_size ? source_size : size;
    slice = _slice_init(source->items, source->left_index, source->left_index + size);
    source->left_index += size;

    return slice;
}

static void _insert_slice(struct _slice* target, struct _slice* slice)
{
    memory_init(target->items + target->left_index, slice->items + slice->left_index, _slice_size(slice) * sizeof(void *));
    target->left_index += _slice_size(slice);
}

static void _merge_silces(struct _slice* target, struct _slice* lhs, struct _slice* rhs, int_signed (*compare)())
{
    while (lhs->left_index < lhs->right_index && rhs->left_index < rhs->right_index)
    {
        if (compare(lhs->items[lhs->left_index], rhs->items[rhs->left_index]) > 0)
        {
            target->items[target->left_index] = lhs->items[lhs->left_index];
            lhs->left_index ++;
        }
        else
        {
            target->items[target->left_index] = rhs->items[rhs->left_index];
            rhs->left_index ++;
        }
        target->left_index ++;
    }

    if (lhs->left_index >= lhs->right_index)
        _insert_slice(target, rhs);
    else if (rhs->left_index >= rhs->right_index)
        _insert_slice(target, lhs);
}

static void _make_a_pass(struct _slice* target, struct _slice* source, int_signed (*compare)(), int_signed frame_size)
{
    struct _slice lhs;
    struct _slice rhs;

    while (_slice_size(source))
    {
        lhs = _get_slice(source, frame_size);
        rhs = _get_slice(source, frame_size);

        _merge_silces(target, &lhs, &rhs, compare);
    }
}

static int_signed _first_pass(Array* array, int_signed (*compare)())
{
    void*       lhs;
    void*       rhs;
    int_signed  n;
    int_signed  limit;
    int_signed  n_swaps;

    n = 0;
    n_swaps = 0;
    limit = array_size(array);

    while (n + 1 < limit)
    {
        lhs = array_at(array, n);
        rhs = array_at(array, n + 1);

        if (compare(lhs, rhs) < 0)
        {
            array_swap(array, n, n + 1);
            n_swaps ++;
        }
        
        n += 2;
    }

    return n_swaps;
}

static void _get_sorted_array(Array* array, int_signed (*compare)())
{
    // int_signed      frame_size;
    // void**          swap_array;
    // void**          sorted_array;
    // struct _slice   target;
    // struct _slice   source;

    // swap_array = memory_zero(array_get_capacity(array) * sizeof(void *));
    // source = _slice_init(array->items, array->left_index + 1, array->right_index);
    // target = _slice_init(swap_array, array->left_index + 1, array->right_index);
    // frame_size = 2;
    // sorted_array = array->items;

    // while (frame_size < array_size(array))
    // {
    //     _make_a_pass(&target, &source, compare, frame_size);
    //     sorted_array = target.items;
    //     SWAP(source.items, target.items, void **);
        
    //     frame_size = frame_size * 2;
    //     source.left_index = array->left_index + 1;
    //     target.left_index = array->left_index + 1;
    // }

    // sorted_array == swap_array ? free(array->items) : free(swap_array);
    // array->items = sorted_array;
}

void array_sortM(Array* array, int_signed (*compare)())
{
    if (!array || !compare)
        return ;
    
    if (array_size(array) < 2)
        return ;

    if (_first_pass(array, compare) == 0)
        return ;
    
    if (array_size(array) == 2)
        return ;
    
    _get_sorted_array(array, compare);
}