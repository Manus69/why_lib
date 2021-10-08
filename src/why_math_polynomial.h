
#ifndef WHY_MATH_POLYNOMIAL_H
#define WHY_MATH_POLYNOMIAL_H

#include "why_math.h"
#include "why_definitions.h"
#include "why_array_interface.h"
#include "why_math_complex.h"

#define P_COEFFICIENT_ABS_MAX   (1 << 15)
#define P_DEFAULT_SIZE          (1 << 1)

struct Polynomial
{
    Complex*    coefficients;
    char*       variable;
    int_signed  degree;
    int_signed  capacity;
};

#ifdef __cplusplus
    extern "C" {
#endif

int_signed  _get_degree(Polynomial* p, int_signed start);
Polynomial* _create(int_signed size, char* variable);

#ifdef __cplusplus
    }
#endif

#endif
