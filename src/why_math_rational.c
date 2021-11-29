#include "why_math_rational.h"

#include <assert.h>

Rational rational(int_signed top, int_signed bot)
{
    assert(bot);
        
    return (Rational){top, bot};
}

int_signed rational_get_top(Rational p)
{
    return p.top;
}

int_signed rational_get_bot(Rational p)
{
    return p.bot;
}

Rational rational_one()
{
    return (Rational){1, 1};
}

Rational rational_zero()
{
    return (Rational){0, 1};
}

Rational rational_reciprocal(Rational p)
{
    assert(p.top);

    return (Rational){p.bot, p.top};
}

Rational rational_reduce(Rational p)
{
    int_signed gcd;

    if (p.top == 0)
        return rational_zero();
    
    gcd = math_gcd(p.top, p.bot);

    return (Rational){p.top / gcd, p.bot / gcd};
}

Rational rational_normalize(Rational p)
{
    if (p.top == 0)
        return rational_zero();
    
    if (p.top < 0 && p.bot < 0)
        return rational_reduce((Rational){-p.top, -p.bot});
    
    if (p.bot < 0)
        return rational_reduce((Rational){-p.top, p.bot});

    return rational_reduce(p);
}

Rational rational_scale(Rational p, int_signed factor)
{
    if (factor == 0)
        return rational_zero();
    
    return (Rational){p.top * factor, p.bot};
}

Rational rational_negative(Rational p)
{
    return (Rational){-p.top, p.bot};
}

Rational rational_add(Rational lhs, Rational rhs)
{
    lhs = rational_scale(lhs, rhs.bot);
    rhs = rational_scale(rhs, lhs.bot);

    return (Rational){lhs.top + rhs.top, lhs.bot};
}

Rational rational_subtract(Rational lhs, Rational rhs)
{
    return rational_add(lhs, rational_scale(rhs, -1));
}

Rational rational_mult(Rational lhs, Rational rhs)
{
    return (Rational){lhs.top * rhs.top, lhs.bot * rhs.bot};
}

Rational rational_divide(Rational lhs, Rational rhs)
{
    assert(rhs.top);

    return rational_mult(lhs, rational_reciprocal(rhs));
}

real rational_to_decimal(Rational p)
{
    return ((real)p.top) / p.bot;
}

int_signed rational_compare(const Rational* lhs, const Rational* rhs)
{
    real result;

    result = rational_to_decimal(*rhs) - rational_to_decimal(*lhs);

    return result < 0 ? -1 : result > 0;
}

Rational rational_random(int_signed top_max, int_signed bot_max)
{
    int_signed top;
    int_signed bot;

    top_max += 1;
    bot_max += 1;
    top = random_get() % top_max;
    bot = random_get() % bot_max;
    top = top == 0 ? 1 : top;
    bot = bot == 0 ? 1 : bot;
    
    return rational(top, bot);
}