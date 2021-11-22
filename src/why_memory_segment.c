#include "why_memory_segment.h"

MSegment* msegment_create(int_signed size, int_signed item_size, void* (*get)(), void (*set)(), void (*swap)())
{
    MSegment* segment;

    segment = allocate(sizeof(MSegment));
    segment->memory = allocate(size * item_size);
    segment->size = size;
    segment->item_size = item_size;
    segment->get = get;
    segment->set = set;
    segment->swap = swap;

    return segment;
}

void msegment_destroy(MSegment* segment)
{
    free(segment->memory);
    free(segment);
}

int_signed msegment_get_size(const MSegment* segment)
{
    return segment->size;
}

void* msegment_get(const MSegment* segment, int_signed index)
{
    return segment->get(segment, index);
}

void msegment_set(MSegment* segment, void* value, int_signed index)
{
    return segment->set(segment, value, index);
}

void msegment_map(MSegment* segment, void (*function)())
{
    int_signed n;
    void* item;

    n = 0;
    while (n < segment->size)
    {
        item = segment->get(segment, n);
        function(item);

        n ++;
    }
}

void msegment_swap(MSegment* segment, int_signed j, int_signed k)
{
    return segment->swap(segment, j, k);
}

MSegment* msegment_createINT(int_signed size)
{
    MSegment* segment;

    segment = msegment_create(size, sizeof(int_signed), msegment_get_int, msegment_set_int, msegment_swap_int);

    return segment;
}

MSegment* msegment_createREAL(int_signed size)
{
    MSegment* segment; 

    segment = msegment_create(size, sizeof(real), msegment_get_real, msegment_set_real, msegment_swap_real);

    return segment;
}

MSegment* msegment_createPTR(int_signed size)
{
    MSegment* segment;

    segment = msegment_create(size, sizeof(void *), msegment_get_pointer, msegment_set_pointer, msegment_swap_pointer);

    return segment;
}
