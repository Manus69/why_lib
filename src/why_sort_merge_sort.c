#include "why_lib.h"
#include "why_array.h"

typedef struct ArrayView ArrayView;

struct ArrayView
{
    Array*      array;
    int_signed  left_index;
    int_signed  right_index;
};

ArrayView array_view_init(const Array* array, int_signed left_index, int_signed right_index)
{
    ArrayView view;

    view.array = (Array *)array;
    view.left_index = left_index;
    view.right_index = right_index;

    return view;
}

int_signed array_view_size(const ArrayView* view)
{
    return view->right_index - view->left_index - 1;
}

int_signed array_view_insert(ArrayView* target, const ArrayView* source, int_signed target_index, int_signed source_index)
{
    void*       item;
    int_signed  index;

    index = target_index;
    while (target_index < target->right_index && source_index < source->right_index)
    {
        item = array_at(source->array, source_index);
        array_set(target->array, item, target_index);

        target_index ++;
        source_index ++;
    }

    return target_index - index;
}

static int_signed _compute_shift(const ArrayView* view)
{
    return array_size(view->array) - view->right_index;
}

int_signed array_view_shift(ArrayView* view, int_signed size)
{
    int_signed available_shift;

    available_shift = _compute_shift(view);
    size = size > available_shift ? available_shift : size;
    view->left_index += size;
    view->right_index += size;

    return size;
}

int_signed array_view_shift_to_index(ArrayView* view, int_signed left_index, int_signed size)
{
    int_signed available_shift;

    available_shift = array_size(view->array) - left_index;
    size = size > available_shift ? available_shift : size;
    view->left_index = left_index;
    view->right_index = view->left_index + size;

    return size;
}

static int_signed _merge_views(const ArrayView* lhs, const ArrayView* rhs, ArrayView* target, int_signed index)
{
    int_signed  lhs_index;
    int_signed  rhs_index;
    int_signed  initial_index;
    int_signed  result;
    void*       item;

    lhs_index = lhs->left_index;
    rhs_index = rhs->left_index;
    initial_index = index;

    while (lhs_index < lhs->right_index && rhs_index < rhs->right_index)
    {
        result = array_compare_elements(lhs->array, lhs_index, rhs_index);
        if (result <= 0)
        {
            item = array_at(rhs->array, rhs_index);
            rhs_index ++;
        }
        else
        {
            item = array_at(lhs->array, lhs_index);
            lhs_index ++;
        }

        array_set(target->array, item, index);
        index ++;
    }

    if (lhs_index >= lhs->right_index)
        return index - initial_index + array_view_insert(target, rhs, index, rhs_index);
    else if (rhs_index >= rhs->right_index)
        return index - initial_index + array_view_insert(target, lhs, index, lhs_index);

    return index - initial_index;
}

static ArrayView _get_view(const Array* array, int_signed left_index, int_signed right_index)
{
    int_signed size;

    size = array_size(array);
    if (left_index >= size)
        left_index = size;
    if (right_index >= size)
        right_index = size;

    return array_view_init(array, left_index, right_index);
}

static void _merge_all_views(Array* target_array, const Array* source_array, int_signed frame_size)
{
    ArrayView   lhs;
    ArrayView   rhs;
    ArrayView   target;
    int_signed  t_index;
    
    t_index = 0;
    target = array_view_init(target_array, 0, array_size(target_array));
    lhs = _get_view(source_array, 0, frame_size);
    rhs = _get_view(source_array, frame_size, 2 * frame_size);

    while (true)
    {
        t_index += _merge_views(&lhs, &rhs, &target, t_index);
        //
        // print_arrayN(target_array, print_int_pointerN, NULL);
        //
        array_view_shift_to_index(&lhs, rhs.right_index, frame_size);
        array_view_shift_to_index(&rhs, lhs.right_index, frame_size);
        if (t_index == target.right_index)
            break ;
    }
}

static void _get_sorted_array(Array* array)
{
    Array*      second_array;
    int_signed  frame_size;
    int_signed  swaps;

    second_array = array_copy_with(array, copy_shallow);
    //
    // print_arrayN(second_array, print_int_pointerN, NULL);
    //
    frame_size = 2;
    swaps = 0;

    while (true)
    {
        if (swaps % 2 == 0)
        {
            _merge_all_views(second_array, array, frame_size);
            // print_arrayN(second_array, print_int_pointerN, NULL);

        }
        else
        {
            _merge_all_views(array, second_array, frame_size);
            // print_arrayN(array, print_int_pointerN, NULL);
        }
        
        frame_size = frame_size * 2;
        swaps ++;

        if (frame_size > array_size(array))
            break ;
    }

    if (swaps % 2)
    {
        SWAP(array->data, second_array->data, void *);
    }
    array_destroy_no_content(second_array);
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
    
    array_set_compare(array, compare);
    _get_sorted_array(array);
}