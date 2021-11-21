#include "why_lib.h"

bool is_prime(int_unsigned n)
{
    int_unsigned divisor;

    if (n < 2 || n == 4)
        return false;
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0)
        return false;

    divisor = 3;
    while (divisor * divisor < n)
    {
        if (n % divisor == 0)
            return false;
        divisor ++;
    }

    return true;
}

int_unsigned get_next_prime(int_unsigned n)
{
    n ++;
    
    while (!is_prime(n))
        n ++;
    
    return n;
}