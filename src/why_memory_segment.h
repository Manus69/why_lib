#ifndef WHY_MEMORY_SEGMENT_H
#define WHY_MEMORY_SEGMENT_H

#include "why_lib.h"

struct MSegment
{
    void*       memory;
    int_signed  size;
    int_signed  item_size;

    void        (*set)();
    void*       (*get)();
    void        (*swap)();
};

void    msegment_set_int(MSegment* segment, void* value, int_signed index);
void*   msegment_get_int(const MSegment* segment, int_signed index);
void    msegment_set_pointer(MSegment* segment, void* value, int_signed index);
void*   msegment_get_pointer(const MSegment* segment, int_signed index);
void*   msegment_get_real(const MSegment* segment, int_signed index);
void    msegment_set_real(MSegment* segment, const void* value, int_signed index);
void    msegment_swap_int(MSegment* segment, int_signed j, int_signed k);
void    msegment_swap_pointer(MSegment* segment, int_signed j, int_signed k);
void    msegment_swap_real(MSegment* segment, int_signed j, int_signed k);
void*   msegment_get_complex(const MSegment* segment, int_signed index);
void    msegment_set_complex(MSegment* segment, const void* value, int_signed index);
void    msegment_swap_complex(MSegment* segment, int_signed j, int_signed k);

#endif