#ifndef WHY_MATH_RANDOM_INTERFACE_H
#define WHY_MATH_RANDOM_INTERFACE_H

#include "why_definitions.h"

int_unsigned    random_get();
int_unsigned    random_in_range(int_unsigned left, int_unsigned right);
void            random_seed(int_unsigned seed);
real            random_chi_squared(int_unsigned seed, int_unsigned max_value, int_unsigned sample_size);
bool            random_chi_squared_test(int_unsigned seed, int_unsigned max, int_unsigned sample_size);

#endif