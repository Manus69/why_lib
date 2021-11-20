#include "why_math_matrix.h"
#include "why_memory.h"
#include "why_math_complex.h"

#include <assert.h>

Complex _dot_row_col(const Matrix* lhs, const Matrix* rhs, int_signed row, int_signed col)
{
    Complex     result;
    Complex     increment;
    int_signed  n;

    result = complex_zero();
    n = 0;
    while (n < matrix_get_n_cols(lhs))
    {
        increment = complex_mult(matrix_at(lhs, row, n), matrix_at(rhs, n, col));
        result = complex_add(result, increment);

        n ++;
    }

    return result;
}

void _matrix_operation_lhs(Matrix* lhs, const Matrix* rhs, Complex (operation)())
{
    int_signed  j;
    int_signed  k;
    Complex     value;

    j = 0;
    while (j < matrix_get_n_rows(lhs))
    {
        k = 0;
        while (k < matrix_get_n_cols(lhs))
        {
            value = operation(lhs, rhs, j, k);
            matrix_set(lhs, value, j, k);

            k ++;
        }
        j ++;
    }
}

Complex _add(const Matrix* lhs, const Matrix* rhs, int_signed row, int_signed col)
{
    return complex_add(matrix_at(lhs, row, col), matrix_at(rhs, row, col));
}

Complex _one(const Matrix* lhs, const Matrix* rhs, int_signed row, int_signed col)
{
    if (lhs == rhs){};

    return row == col ? complex_one() : complex_zero();
}

Matrix* matrix_eye(int_signed size)
{
    Matrix*     matrix;

    matrix = matrix_create(size, size);
    _matrix_operation_lhs(matrix, NULL, _one);

    return matrix;
}

void matrix_add_to_left(Matrix* lhs, const Matrix* rhs)
{
    if (!lhs || !rhs)
        return ;
    
    if (!_same_size(lhs, rhs))
        return ;
    
    _matrix_operation_lhs(lhs, rhs, _add);
}

Matrix* matrix_add(const Matrix* lhs, const Matrix* rhs)
{
    Matrix* result;

    result = matrix_copy(lhs);
    matrix_add_to_left(result, rhs);

    return result;
}

Matrix* matrix_mult(const Matrix* lhs, const Matrix* rhs)
{
    Matrix*     result;
    Complex     value;
    int_signed  j;
    int_signed  k;

    if (!lhs || !rhs)
        return NULL;
    
    if (!_conformant(lhs, rhs))
        return NULL;

    result = matrix_create(lhs->n_rows, rhs->n_cols);
    j = 0;
    while (j < result->n_rows)
    {
        k = 0;
        while (k < result->n_cols)
        {
            value = _dot_row_col(lhs, rhs, j, k);
            matrix_set(result, value, j, k);

            k ++;
        }
        j ++;
    }

    return result;
}