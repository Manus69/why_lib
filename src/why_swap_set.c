#include "why_lib.h"
#include "why_math_complex.h"


void int_set(void* memory, const int_signed* n, int_signed index)
{
    MEM_SET(memory, index, n, int_signed);
}

void complex_set(void* memory, const Complex* z, int_signed index)
{
    MEM_SET(memory, index, z, Complex);
}

void pointer_set(void* memory, const void* item, int_signed index)
{
    MEM_SET(memory, index, item, void *);
}

void int_swap(void* memory, int_signed lhs_offset, int_signed rhs_offset)
{
    MEM_SWAP(memory, lhs_offset, rhs_offset, int_signed);
}

void complex_swap(void* memory, int_signed lhs_offset, int_signed rhs_offset)
{
    MEM_SWAP(memory, lhs_offset, rhs_offset, Complex);
}

void pointer_swap(void* memory, int_signed lhs_offset, int_signed rhs_offset)
{
    MEM_SWAP(memory, lhs_offset, rhs_offset, void *);
}