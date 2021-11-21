#include "why_math_rational.h"

Rational rational(int_signed top, int_signed bot)
{
    return (Rational){top, bot};
}

Rational rational_one()
{
    return (Rational){1, 1};
}

Rational rational_zero()
{
    return (Rational){0, 1};
}

Rational rational_scale(Rational p, int_signed factor)
{
    return (Rational){p.top * factor, p.bot * factor};
}

Rational rational_add(Rational lhs, Rational rhs)
{
    lhs = rational_scale(lhs, rhs.bot);
    rhs = rational_scale(rhs, lhs.bot);

    return (Rational){lhs.top + rhs.top, lhs.bot};
}