#include "why_memory_segment.h"
#include "why_math_complex.h"

// #define SHIFT(pointer, index, type) (pointer + index * sizeof(type))
// #define SHIFT(pointer, index, type) ((type *)pointer)[index]
#define SHIFT(pointer, index, item_size) (pointer + index * item_size)
#define SET(pointer, index, value, type) (((type *)pointer)[index] = *(type *)value)

void msegment_set_int(MSegment* segment, void* value, int_signed index)
{
    // ((int_signed *)segment->memory)[index] = *(int_signed *)value;
    SET(segment->memory, index, value, int_signed);
}

void* msegment_get_int(const MSegment* segment, int_signed index)
{
    // return segment->memory + index * sizeof(int_signed);
    // return SHIFT(segment->memory, index, int_signed);
    return SHIFT(segment->memory, index, sizeof(int_signed));
}

void msegment_set_pointer(MSegment* segment, void* value, int_signed index)
{
    ((void **)segment->memory)[index] = value;
    // SET(segment->memory, index, value, void *);
}

void* msegment_get_pointer(const MSegment* segment, int_signed index)
{
    // return ((void **)segment->memory)[index];
    // return *((void **)segment->memory + index);
    return *(void **)SHIFT(segment->memory, index, sizeof(void *));
}

void* msegment_get_real(const MSegment* segment, int_signed index)
{
    // return segment->memory + index * sizeof(real);
    // return SHIFT(segment->memory, index, real);
    return SHIFT(segment->memory, index, sizeof(real));
}

void msegment_set_real(MSegment* segment, const void* value, int_signed index)
{
    // ((real *)segment->memory)[index] = *(real *)value;
    SET(segment->memory, index, value, real);
}

void* msegment_get_complex(const MSegment* segment, int_signed index)
{
    // return SHIFT(segment->memory, index, Complex);
    return SHIFT(segment->memory, index, sizeof(Complex));

}

void msegment_set_complex(MSegment* segment, const void* value, int_signed index)
{
    SET(segment->memory, index, value, Complex);
}

#define MS_SWAP(memory, j, k, type) \
    type lhs = *(type *)SHIFT(memory, j, sizeof(type)); \
    type rhs = *(type *)SHIFT(memory, k, sizeof(type)); \
    SET(memory, j, &rhs, type); \
    SET(memory, k, &lhs, type);


void msegment_swap_int(MSegment* segment, int_signed j, int_signed k)
{
    MS_SWAP(segment->memory, j, k, int_signed);
}

void msegment_swap_real(MSegment* segment, int_signed j, int_signed k)
{
    MS_SWAP(segment->memory, j, k, real);
}

void msegment_swap_complex(MSegment* segment, int_signed j, int_signed k)
{
    MS_SWAP(segment->memory, j, k, Complex);
}

void msegment_swap_pointer(MSegment* segment, int_signed j, int_signed k)
{
    MS_SWAP(segment->memory, j, k, void *);
}
