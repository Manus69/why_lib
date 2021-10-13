
#ifndef WHY_MATH_H
#define WHY_MATH_H

#include "why_definitions.h"
#include "why_array_interface.h"

#define EPSILON (((real)1) / (1 << 12))
#define PI      (real)3.1415926535
#define E       (real)2.7182818284

typedef struct Complex Complex;
typedef struct Polynomial Polynomial;
typedef struct Matrix Matrix;

#ifdef __cplusplus
    extern "C" {
#endif

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

//R -> R
real            math_sqrt(real a);
real            math_exp(real x);
real            math_ln(real x);
real            math_log2(real x);
real            math_log(real x, real base);
real            math_id(real x);
real            math_sin(real x);
real            math_cos(real x);
real            math_tan(real x);

//Complex algebra
Complex         complex(real re, real im);
Complex*        complex_create(real re, real im);
Complex*        complex_copy(Complex* z);
Complex         complex_zero();
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

//Polynomials
Polynomial*     polynomial_create(char* variable);
Polynomial*     polynomial_create_from_complex(Complex z);
Polynomial*     polynomial_create_from_complexG(Complex z, int_signed degree, char* variable);
Polynomial*     polynomial_create_from_coefficients(real coefficients[], int_signed size);
Polynomial*     polynomial_copy(const Polynomial* p);
void            polynomial_destroy(Polynomial* p);
int_signed      polynomial_get_degree(const Polynomial* p);
char*           polynomial_get_variable(const Polynomial* p);
Complex         polynomial_at(const Polynomial* p, int_signed degree);
Complex         polynomial_get_leading_coefficient(const Polynomial* p);
bool            polynomial_set(Polynomial* p, Complex value, int_signed degree);
Polynomial*     polynomial_increment(Polynomial* p, Polynomial* q);
Polynomial*     polynomial_add(Polynomial* p, Polynomial* q);
Polynomial*     polynomial_addLD(Polynomial* p, Polynomial* q);
Polynomial*     polynomial_subtract(Polynomial* p, Polynomial* q);
Polynomial*     polynomial_subtractLD(Polynomial* p, Polynomial* q);
Polynomial*     polynomial_multiply(Polynomial* p, Polynomial* q);
Polynomial*     polynomial_multiplyLD(Polynomial* p, Polynomial* q);
Polynomial*     polynomial_scale(Polynomial* p, Complex factor);
Polynomial*     polynomial_exponentiate(Polynomial* p, int_signed power);
Polynomial*     polynomial_factor(const Polynomial* p,const Polynomial* q);
Polynomial*     polynomial_differentiate(const Polynomial* p);
Complex         polynomial_evaluate(const Polynomial* p, Complex value);
bool            polynomial_is_constant(const Polynomial* p);
Complex         polynomial_get_constant_coefficient(const Polynomial* p);
bool            polynomial_is_real(const Polynomial* p);
bool            polynomial_is_zero(const Polynomial* p);
Array*          polynomial_roots(const Polynomial* p);
real            polynomial_newtons(const Polynomial* p);

//Matrix stuff
Matrix*         matrix_create(int_signed n_rows, int_signed n_cols);
void            matrix_destroy(Matrix* matrix);
Complex         matrix_at(Matrix* A, int_signed j, int_signed k);
bool            matrix_set(Matrix* A, Complex z, int_signed j, int_signed k);
Matrix*         matrix_eye(int_signed size);
Matrix*         matrix_add(Matrix* A, Matrix* B);
Matrix*         matrix_mult(Matrix* A, Matrix* B);

//primes
bool            is_prime(int_unsigned n);
int_unsigned    get_next_prime(int_unsigned n);

#ifdef __cplusplus
    }
#endif

#endif
