#include "why_lib.h"

#include <assert.h>

static int_signed _gcd(int_signed a, int_signed b)
{
    if (a < b)
        SWAP(a, b, int_signed);
        
    assert(a);

    if (b == 0)
        return a;

    if (b == 1)
        return b;

    return _gcd(b, a % b);
}

//gcd(a, b) = gcd(b, a - b)
int_signed math_gcd(int_signed a, int_signed b)
{
    a = ABS(a);
    b = ABS(b);

    return _gcd(a, b);
}
//lcm(a, b)gcd(a, b) = |ab|
int_signed math_lcm(int_signed a, int_signed b)
{
    a = ABS(a);
    b = ABS(b);

    return (a * b) / _gcd(a, b);
}