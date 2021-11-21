#ifndef WHY_MATH_MATRIX_H
#define WHY_MATH_MATRIX_H

#include "why_lib.h"

struct Matrix
{
    Complex*    array;
    int_signed  n_rows;
    int_signed  n_cols;
};

bool _same_size(const Matrix* lhs, const Matrix* rhs);
bool _conformant(const Matrix* lhs, const Matrix* rhs);

#endif
