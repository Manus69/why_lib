#include "why_math_algebra.h"
#include "why_memory.h"
#include "why_math_complex_interface.h"
#include "why_math_complex.h"
#include "why_macros.h"

#if OVERFLOW_CHECK
    #include "why_error.h"
#endif

bool check_add_overflow(int_signed n, int_signed m)
{
    if (n > 0 && m > 0)
    {
        if (n > WHY_INT_MAX - m)
            return TRUE;
    }
    
    return FALSE;
}

int_signed int_add(int_signed n, int_signed m)
{
    #if OVERFLOW_CHECK
    if (check_add_overflow(n, m))
        error_set(WHY_ERROR_MATH, "int overflow");
    #endif

    return n + m;
}

bool check_mult_overflow(int_signed n, int_signed m)
{
    if (!n || !m)
        return FALSE;
    
    if (ABS(n) > WHY_INT_MAX / ABS(m))
        return TRUE;
    
    return FALSE;
}

int_signed int_mult(int_signed n, int_signed m)
{
    #if OVERFLOW_CHECK
    if (check_mult_overflow(n, m))
        error_set(WHY_ERROR_MATH, "int overflow");
    #endif

    return n * m;
}

int_signed int_subtract(int_signed n, int_signed m)
{
    return n - m;
}

int_signed int_divide(int_signed n, int_signed m)
{
    return n / m;
}

int_signed int_mod(int_signed n, int_signed m)
{
    return n % m;
}

real real_add(real x, real y)
{
    return x + y;
}

real real_mult(real x, real y)
{
    return x * y;
}

real real_subtract(real x, real y)
{
    return x - y;
}

real real_divide(real x, real y)
{
    return x / y;
}

bool real_is_zeroP(const real* x)
{
    return *x == 0;
}

bool real_is_int(real x)
{
    return x == (int_signed)x;
}

void* real_addP(const real* x, const real* y)
{
    real* result;

    result = allocate(sizeof(real));
    *result = *x + *y;

    return result;
}

void* real_multP(const real* x, const real* y)
{
    real* result;

    result = allocate(sizeof(real));
    *result = *x * *y;

    return result;
}

bool complex_is_zeroP(const Complex* z)
{
    return complex_is_zero(*z);
}

void* complex_addP(const Complex* z, const Complex* w)
{
    Complex* result;

    result = allocate(sizeof(Complex));
    *result = complex_add(*z, *w);

    return result;
}

void* complex_multP(const Complex* z, const Complex* w)
{
    Complex* result;

    result = allocate(sizeof(Complex));
    *result = complex_mult(*z, *w);

    return result;
}