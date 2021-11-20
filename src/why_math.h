
#ifndef WHY_MATH_H
#define WHY_MATH_H

#include "why_definitions.h"
#include "why_math_algebra.h"
#include "why_math_complex_interface.h"
#include "why_math_polynomial_interface.h"
#include "why_math_matrix_interface.h"
#include "why_math_random_interface.h"

#define WHY_RAND_MAX    (((int_unsigned)1 << 31) - 2)
#define EPSILON         (((real)1) / (1 << 12))
#define PI              (real)3.1415926535
#define E               (real)2.7182818284

bool            within_delta(real x, real y, real delta);
bool            real_is_int(real x);
real            math_mod(real x, real mod);
real            power(real base, int_unsigned n);
real            absolute_value(real x);
int_signed      power_int(int_signed base, int_unsigned n);
int_unsigned    factorial(int_unsigned n);
int_unsigned    round_to_int(real x);
int_unsigned    fib(int_unsigned n);
int_unsigned    math_is_perfect_square(int_unsigned x);
int_signed      math_gcd(int_signed a, int_signed b);

//R -> R
real            math_sqrt(real a);
real            math_exp(real x);
real            math_ln(real x);
real            math_log2(real x);
real            math_log10(real x);
real            math_log(real x, real base);
real            math_id(real x);
real            math_sin(real x);
real            math_cos(real x);
real            math_tan(real x);

//primes
bool            is_prime(int_unsigned n);
int_unsigned    get_next_prime(int_unsigned n);

#endif
