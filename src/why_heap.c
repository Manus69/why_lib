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
    return array_swap(heap, m, n);
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
    return 2 * index + 2;
}

static void* _get_parent(Heap* heap, int_signed index)
{
    return heap->items[_index_of_parent(index)];
}

void* _get_left_child(Heap* heap, int_signed index)
{
    int_signed child_index;

    child_index = _index_of_left_child(index);
    if (child_index >= heap->right_index)
        return NULL;

    return heap->items[child_index];
}

void* _get_right_child(Heap* heap, int_signed index)
{
    int_signed child_index;

    child_index = _index_of_right_child(index);
    if (child_index >= heap->right_index)
        return NULL;

    return heap->items[child_index];
}

static void _restore_heap_property(Heap* heap, int_signed index)
{
    int_signed  parent_index;
    void*       parent;

    while (index)
    {
        parent_index = _index_of_parent(index);
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
