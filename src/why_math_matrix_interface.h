#ifndef WHY_MATH_MATRIX_INTERFACE_H
#define WHY_MATH_MATRIX_INTERFACE_H

#include "why_definitions.h"
#include "why_math_complex_interface.h"

typedef struct Matrix Matrix;

Matrix*         matrix_create(int_signed n_rows, int_signed n_cols);
void            matrix_destroy(Matrix* matrix);
Matrix*         matrix_copy(const Matrix* matrix);
int_signed      matrix_get_n_rows(const Matrix* matrix);
int_signed      matrix_get_n_cols(const Matrix* matrix);
int_signed      matrix_get_total_size(const Matrix* matrix);
Complex         matrix_at(const Matrix* A, int_signed j, int_signed k);
bool            matrix_set(Matrix* A, Complex z, int_signed j, int_signed k);
Matrix*         matrix_eye(int_signed size);
void            matrix_add_to_left(Matrix* lhs, const Matrix* rhs);
void            matrix_mult_lhs(Matrix* lhs, const Matrix* rhs);
Matrix*         matrix_add(const Matrix* A, const Matrix* B);
Matrix*         matrix_mult(const Matrix* A, const Matrix* B);

#endif