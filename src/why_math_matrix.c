#include "why_math_matrix.h"
#include "why_memory.h"
#include "why_math_complex.h"
#include "why_array_interface.h"

#include <assert.h>

Matrix* matrix_create(int_signed n_rows, int_signed n_cols)
{
    Matrix*     matrix;
    int_signed  size;

    matrix = allocate(sizeof(Matrix));
    size = n_rows * n_cols;
    matrix->array = allocate(sizeof(Complex) * size);
    matrix->n_rows = n_rows;
    matrix->n_cols = n_cols;

    return matrix;
}

void matrix_destroy(Matrix* matrix)
{
    if (!matrix)
        return ;
    
    free(matrix->array);
    free(matrix);
}

Matrix* matrix_copy(const Matrix* matrix)
{
    Matrix* copy;

    if (!matrix)
        return NULL;
    
    copy = memory_copy(matrix, sizeof(Matrix));
    copy->array = memory_copy(matrix->array, matrix_get_total_size(matrix) * sizeof(Complex));

    return copy;
}

Complex matrix_at(const Matrix* A, int_signed j, int_signed k)
{
    return A->array[A->n_cols * j + k];
}

bool matrix_set(Matrix* A, Complex z, int_signed j, int_signed k)
{
    A->array[A->n_cols * j + k] = z;

    return TRUE;
}

int_signed matrix_get_n_rows(const Matrix* matrix)
{
    return matrix->n_rows;
}

int_signed matrix_get_n_cols(const Matrix* matrix)
{
    return matrix->n_cols;
}

int_signed matrix_get_total_size(const Matrix* matrix)
{
    return matrix->n_cols * matrix->n_rows;
}

bool _same_size(const Matrix* lhs, const Matrix* rhs)
{
    return (lhs->n_cols == rhs->n_cols) && (lhs->n_rows == rhs->n_rows);
}

bool _conformant(const Matrix* lhs, const Matrix* rhs)
{
    return lhs->n_cols == rhs->n_rows;
}

Matrix* matrix_create_from_array(const Array* array, int_signed rows, int_signed cols)
{
    Matrix* matrix;
    
    if (!array || rows * cols != array_size(array))
        return NULL;

    return NULL;
}