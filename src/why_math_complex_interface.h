#ifndef WHY_MATH_COMPLEX_INTERFACE_H
#define WHY_MATH_COMPLEX_INTERFACE_H

#include "why_definitions.h"

typedef struct Complex Complex;

Complex         complex(real re, real im);
Complex*        complex_create(real re, real im);
Complex*        complex_copy(Complex* z);
Complex         complex_zero();
Complex         complex_one();
Complex         complex_add(Complex lhs, Complex rhs);
Complex         complex_mult(Complex lhs, Complex rhs);
Complex         complex_div(Complex lhs, Complex rhs);
Complex         complex_subtract(Complex lhs, Complex rhs);
Complex         complex_inv(Complex z);
bool            complex_is_real(Complex z);
bool            complex_is_zero(Complex z);
bool            complex_is_imaginary(Complex z);
Complex         complex_scale(Complex z, real a);
Complex         complex_conjugate(Complex z);
Complex         complex_power(Complex z, int_unsigned n);
real            complex_mod_squared(Complex z);

#endif