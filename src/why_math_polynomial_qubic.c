#include "why_lib.h"
#include "why_math_polynomial.h"
#include "why_error.h"

static Polynomial* _scale(const Polynomial* p)
{
    int_signed  n;
    Complex     coefficient;
    Polynomial* p_scaled;
    Polynomial* pointer;

    p_scaled = polynomial_copy(p);
    n = 0;
    while (n <= p->degree)
    {
        coefficient = polynomial_at(p_scaled, n);
        if (complex_is_zero(coefficient))
        {
            n ++;
            continue ;
        }

        if (absolute_value(coefficient.re) < 1)
        {
            pointer = polynomial_scale(p_scaled, complex(1 / coefficient.re, 0));
            polynomial_destroy(p_scaled);
            p_scaled = pointer;
        }

        n ++;
    }

    return p_scaled;
}

static bool _in_range(const Polynomial* p)
{
    int_signed  n;
    Complex     coefficient;

    n = 0;
    while (n <= p->degree)
    {
        coefficient = polynomial_at(p, n);
        if (absolute_value(coefficient.re) > P_COEFFICIENT_ABS_MAX)
            return FALSE;

        n ++;
    }

    return TRUE;
}

static Array* _get_roots(Polynomial* p_scaled, Array* roots, real a_root)
{
    Polynomial* q;
    Polynomial* factor;
    Array*      quadratic_roots;

    factor = polynomial_create_from_coefficients((real[]){-a_root, 1}, 2);
    q = polynomial_factor(p_scaled, factor);
    quadratic_roots = polynomial_roots(q);
    roots = array_concatG(roots, quadratic_roots, copy_complex);

    polynomial_destroy(factor);
    array_destroy(quadratic_roots);
    polynomial_destroy(q);

    return roots;
}

Array* _solve_qubic(const Polynomial* p)
{
    Array*      roots;
    Polynomial* p_scaled;
    real        a_root;

    p_scaled = _scale(p);

    if (!_in_range(p_scaled))
    {
        error_set(WHY_ERROR_MATH, "failed to find roots");
        polynomial_destroy(p_scaled);
        return NULL;
    }

    a_root = polynomial_newtons(p_scaled);
    roots = array_create_with_capacity(copy_shallow, memory_destroy, 3);

    array_push(roots, complex_create(a_root, 0));
    roots = _get_roots(p_scaled, roots, a_root);

    polynomial_destroy(p_scaled);

    return roots;
}