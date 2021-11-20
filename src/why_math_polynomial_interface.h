#ifndef WHY_MATH_POLYNOMIAL_INTERFACE_H
#define WHY_MATH_POLYNOMIAL_INTERFACE_H

#include "why_definitions.h"
#include "why_math_complex.h"

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

#endif