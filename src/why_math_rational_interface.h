#ifndef WHY_MATH_RATIONAL_INTERFACE_H
#define WHY_MATH_RATIONAL_INTARFACE_H

typedef struct Rational Rational;

Rational rational(int_signed top, int_signed bot);
Rational rational_one();
Rational rational_zero();
Rational rational_scale(Rational p, int_signed factor);
Rational rational_add(Rational lhs, Rational rhs);

#endif