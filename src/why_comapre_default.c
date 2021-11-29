#include "why_lib.h"
#include "why_math_complex.h"

int_signed compare_int(const int_signed* lhs, const int_signed* rhs)
{
    return *rhs - *lhs;
}

int_signed compare_intINV(const int_signed* lhs, const int_signed* rhs)
{
    return -compare_int(lhs, rhs);
}

int_signed compare_byte(const byte* lhs, const byte* rhs)
{
    return *rhs - *lhs;
}

int_signed compare_real(const real* lhs, const real* rhs)
{
    return *rhs - *lhs;
}

int_signed compare_complex(const Complex* lhs, const Complex* rhs)
{
    return complex_mod(*rhs) - complex_mod(*lhs);
}