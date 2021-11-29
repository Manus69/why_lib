#include "why_lib.h"

// extern inline int_signed heap_size(const Heap* heap);

Heap* heap_create_with_capacity(void* (*copy)(), void (*destroy)(), int_signed (*compare)(), int_signed capacity)
{
    Heap* heap;

    heap = array_create_with_capacity(copy, destroy, capacity);
    array_set_compare(heap, compare);

    return heap;
}

Heap* heap_create(void* (*copy)(), void (*destroy)(), int_signed (*compare)())
{
    return heap_create_with_capacity(copy, destroy, compare, H_CAPACITY_DEFAULT);
}

void heap_destroy(Heap* heap)
{
    return array_destroy(heap);
}

void heap_map(Heap* heap, void (*function)())
{
    return array_map(heap, function);
}

void heap_swap(Heap* heap, int_signed m, int_signed n)
{
    array_swap(heap, m, n);
}

static int_signed _index_of_parent(int_signed index)
{
    return (index - 1) / 2; 
}

static int_signed _index_of_left_child(int_signed index)
{
    return 2 * index + 1;
}

static int_signed _index_of_right_child(int_signed index)
{
    return 2 * (index + 1);
}

static int_signed _index_of_root(const Heap* heap)
{
    NOP(heap);

    return 0;
}

static int_signed _index_of_last(const Heap* heap)
{
    return array_size(heap) - 1;
}

static bool _index_in_range(const Heap* heap, int_signed index)
{
    return (index >= _index_of_root(heap)) && (index <= _index_of_last(heap));
}

void* _heap_at(const Heap* heap, int_signed index)
{
    return _index_in_range(heap, index) ? array_at(heap, index) : NULL;
}

void* _get_parent(Heap* heap, int_signed index)
{
    return _index_in_range(heap, index) ? array_at(heap, _index_of_parent(index)) : NULL;
}

void* _get_left_child(Heap* heap, int_signed index)
{
    int_signed child_index;

    child_index = _index_of_left_child(index);
    if (!_index_in_range(heap, child_index))
        return NULL;

    return array_at(heap, child_index);
}

void* _get_right_child(Heap* heap, int_signed index)
{
    int_signed child_index;

    child_index = _index_of_right_child(index);
    if (!_index_in_range(heap, child_index))
        return NULL;

    return array_at(heap, child_index);
}

static void _restore_heap_property(Heap* heap, int_signed index)
{
    int_signed  parent_index;

    while (index)
    {
        parent_index = _index_of_parent(index);
        if (parent_index <= _index_of_root(heap))
            return ;
        
        if (array_compare_elements(heap, parent_index, index) < 0)
            return ;

        heap_swap(heap, parent_index, index);
        index = parent_index;
    }
}

bool heap_push(Heap* heap, const void* item)
{
    if (array_push(heap, item))
    {
        _restore_heap_property(heap, _index_of_last(heap));
        return TRUE;
    }
    
    return FALSE;
}

int_signed heap_size(const Heap* heap)
{
    return array_size(heap);
}

static bool _process_left_child(Heap* heap, int_signed lhs_index, int_signed index)
{
    if (array_compare_elements(heap, index, lhs_index) > 0)
    {
        heap_swap(heap, index, lhs_index);
        return true;
    }

    return false;
}

static bool _heapify_down(Heap* heap, int_signed index)
{
    int_signed  lhs_index;
    int_signed  rhs_index;
    int_signed  lhs_result;
    int_signed  rhs_result;

    if (!_index_in_range(heap, index))
        return false;

    lhs_index = _index_of_left_child(index);
    rhs_index = _index_of_right_child(index);

    if (!_index_in_range(heap, lhs_index) && !_index_in_range(heap, rhs_index))
        return true; 
    
    if (!_index_in_range(heap, rhs_index))
        return _process_left_child(heap, lhs_index, index);
    
    lhs_result = array_compare_elements(heap, index, lhs_index);
    rhs_result = array_compare_elements(heap, index, rhs_index);

    if (lhs_result <= 0 && rhs_result <= 0)
        return true;
    
    if (array_compare_elements(heap, lhs_index, rhs_index) < 0)
    {
        heap_swap(heap, _index_of_left_child(index), index);
        return _heapify_down(heap, _index_of_left_child(index));
    }
    else
    {
        heap_swap(heap, rhs_index, index);
        return _heapify_down(heap, rhs_index);
    }
}



static void _swap_out_root(Heap* heap)
{
    heap_swap(heap, _index_of_last(heap), _index_of_root(heap));
    _array_shift_right_brk(heap, -1);
    _heapify_down(heap, _index_of_root(heap));
}

void* heap_pop_root(Heap* heap)
{
    void*       item;
    int_signed  size;

    if (!heap || (size = array_size(heap)) == 0)
        return NULL;
    
    if (size != 1)
    {
        _swap_out_root(heap);
        return array_at(heap, _index_of_last(heap) + 1);
    }
    item = array_pop(heap);

    return item;
}

void heap_sort(Heap* heap)
{
    int_signed n;
    
    if (!heap)
        return ;

    n = _index_of_last(heap);
    while (n >= _index_of_root(heap))
    {
        _heapify_down(heap, n);
        n --;
        //
        // print_heap(heap, print_int_pointerN);
    }

    n = array_size(heap);
    while (array_size(heap))
    {
        _swap_out_root(heap);
        // _array_shift_right_brk(heap, -1);
    }

    _array_shift_right_brk(heap, n);
}
