#include "why_math_polynomial.h"
#include "why_math_complex.h"

Array* _solve_qubic(const Polynomial* p);

static Array* _solve_constant(const Polynomial* p)
{
    Array* root;

    if (!complex_is_zero(p->coefficients[0]))
        return NULL;

    root = array_create_with_capacity(copy_shallow, memory_destroy, 1);
    array_push(root, complex_copy(&p->coefficients[0]));

    return root;
}

//a0 + a1x = 0
static Array* _solve_linear(const Polynomial* p)
{
    Array*  roots;
    real    x;
    
    roots = array_create_with_capacity(copy_shallow, memory_destroy, 2);

    x = -p->coefficients[0].re / p->coefficients[1].re;
    array_push(roots, complex_create(x, 0));

    return roots;
}

//c + bx + ax^2 = 0
static Array* _solve_quadratic(const Polynomial* p)
{
    Array*  roots;
    real    a, b, c, x, D;

    roots = array_create_with_capacity(copy_shallow, memory_destroy, 2);
    
    a = p->coefficients[2].re;
    b = p->coefficients[1].re;
    c = p->coefficients[0].re;

    D = b * b - 4 * a *c;
    if (D == 0)
    {
        array_push(roots, complex_create(-b / (2 * a), 0));
    }
    else if (D > 0)
    {
        x = (-b + math_sqrt(D)) / (2 * a);
        array_push(roots, complex_create(x, 0));
        x = (-b - math_sqrt(D)) / (2 * a);
        array_push(roots, complex_create(x, 0));
    } 
    else
    {
        x = math_sqrt(-D) / (2 * a);
        array_push(roots, complex_create(-b / (2 * a), x));
        array_push(roots, complex_create(-b / (2 * a), -x));
    }

    return roots;
}

Array* polynomial_roots(const Polynomial* p)
{
    if (!p)
        return NULL;

    if (p->degree < 0)
        return NULL;

    if (!polynomial_is_real(p))
        return NULL;

    if (p->degree == 0)
        return _solve_constant(p);
    
    if (p->degree == 1)
        return _solve_linear(p);

    if (p->degree == 2)
        return _solve_quadratic(p);

    if (p->degree == 3)
        return _solve_qubic(p);

    return error_set(WHY_ERROR_MATH, "polynomial degree must be no greater than 3"); 
}