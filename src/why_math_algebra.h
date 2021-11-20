
#ifndef WHY_MATH_ALGEBRA_H
#define WHY_MATH_ALGEBRA_H

#include "why_definitions.h"
#include "why_math_complex_interface.h"

#ifdef __cplusplus
    extern "C" {
#endif

int_signed  int_add(int_signed n, int_signed m);
int_signed  int_mult(int_signed n, int_signed m);
int_signed  int_subtract(int_signed n, int_signed m);
int_signed  int_divide(int_signed n, int_signed m);
int_signed  int_mod(int_signed n, int_signed m);
real        real_add(real x, real y);
real        real_mult(real x, real y);
real        real_subtract(real x, real y);
real        real_divide(real x, real y);

bool        real_is_zeroP(const real* x);
void*       real_addP(const real* x, const real* y);
void*       real_multP(const real* x, const real* y);

bool        complex_is_zeroP(const Complex* z);
void*       complex_addP(const Complex* z, const Complex* w);
void*       complex_multP(const Complex* z, const Complex* w);

#ifdef __cplusplus
    }
#endif

#endif
