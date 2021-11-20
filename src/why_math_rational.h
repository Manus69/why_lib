#ifndef WHY_MATH_RATIONAL_H
#define WHY_MATH_RATIONAL_H

#include "why_definitions.h"

typedef struct Rational Rational;

struct Rational
{
    int_signed top;
    int_signed bot;
};

#endif