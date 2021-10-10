#include "why_heap_interface.h"
#include "why_array_interface.h"
#include "why_array.h"
#include "why_memory.h"
#include "why_macros.h"

//not tested

Heap* heap_create(void* (*copy)(), void (*destroy)(), int_signed (*compare)())
{
    Heap* heap;

    heap = array_create(copy, destroy);
    heap->compare = compare;

    return heap;
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
    // return array_swap(heap, m, n);
    SWAP(heap->items[m], heap->items[n], void *);
}

static int_signed _index_of_parent(const Heap* heap, int_signed index)
{
    // return (index - 1) / 2;
    return (index + heap->left_index) / 2;
}

static int_signed _index_of_left_child(const Heap* heap, int_signed index)
{
    // return 2 * index + 1;
    return 2 * index - heap->left_index;
}

static int_signed _index_of_right_child(const Heap* heap, int_signed index)
{
    // return 2 * index + 2;
    return 1 + _index_of_left_child(heap, index);
}

static bool _index_in_range(const Heap* heap, int_signed index)
{
    return (index > heap->left_index) && (index < heap->right_index);
}

static void* _heap_at(const Heap* heap, int_signed index)
{
    return _index_in_range(heap, index) ? heap->items[index] : NULL;
}

static void* _get_parent(Heap* heap, int_signed index)
{
    return _index_in_range(heap, index) ? heap->items[_index_of_parent(heap, index)] : NULL;
}

static int_signed _index_of_root(Heap* heap)
{
    return heap->left_index + 1;
}

static int_signed _index_of_last(Heap* heap)
{
    return heap->right_index - 1;
}

void* _get_left_child(Heap* heap, int_signed index)
{
    int_signed child_index;

    child_index = _index_of_left_child(heap, index);
    if (!_index_in_range(heap, child_index))
        return NULL;

    return heap->items[child_index];
}

void* _get_right_child(Heap* heap, int_signed index)
{
    int_signed child_index;

    child_index = _index_of_right_child(heap, index);
    if (!_index_in_range(heap, child_index))
        return NULL;

    return heap->items[child_index];
}

static void _restore_heap_property(Heap* heap, int_signed index)
{
    int_signed  parent_index;
    void*       parent;

    while (index)
    {
        parent_index = _index_of_parent(heap, index);
        parent = _get_parent(heap, parent_index);

        if (heap->compare(parent, heap->items[index]) < 0)
            return ;

        heap_swap(heap, parent_index, index);
        index = parent_index;
    }
}

bool heap_push(Heap* heap, void* item)
{
    if (array_push(heap, item))
    {
        _restore_heap_property(heap, heap->right_index - 1);
        return TRUE;
    }
    
    return FALSE;
}

static bool _process_left_child(Heap* heap, void* lhs, int_signed index)
{
    if (heap->compare(_heap_at(heap, index), lhs) > 0)
    {
        heap_swap(heap, index, _index_of_left_child(heap, index));
        return true;
    }

    return false;
}

static bool _heapify_down(Heap* heap, int_signed index)
{
    void*       lhs;
    void*       rhs;
    void*       root;
    int_signed  lhs_result;
    int_signed  rhs_result;

    if (!_index_in_range(heap, index))
        return false;
    
    lhs = _get_left_child(heap, index);
    rhs = _get_right_child(heap, index);

    if (!lhs && !rhs)
        return true; 
    
    if (!rhs)
        return _process_left_child(heap, lhs, index);
    
    root = _heap_at(heap, index);
    lhs_result = heap->compare(root, lhs);
    rhs_result = heap->compare(root, rhs);

    if (lhs_result <= 0 && rhs_result <= 0)
        return true;
    
    if (heap->compare(lhs, rhs) < 0)
    {
        heap_swap(heap, _index_of_left_child(heap, index), index);
        return _heapify_down(heap, _index_of_left_child(heap, index));
    }
    else
    {
        heap_swap(heap, _index_of_right_child(heap, index), index);
        return _heapify_down(heap, _index_of_right_child(heap, index));
    }
}

static void _swap_out_root(Heap* heap)
{
    heap_swap(heap, _index_of_last(heap), _index_of_root(heap));
    heap->right_index --;
    _heapify_down(heap, _index_of_root(heap));
}

void heap_sort(Heap* heap)
{
    int_signed n;
    
    if (!heap || !heap->compare)
        return ;

    n = heap->right_index - 1;
    while (n > heap->left_index)
    {
        _heapify_down(heap, n);
        n --;
    }

    n = heap->right_index;
    while (array_size(heap))
        _swap_out_root(heap);

    heap->right_index = n;
}
