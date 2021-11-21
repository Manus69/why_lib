#include "why_lib.h"

#define FIB_LIMIT 90

int_unsigned fib(int_unsigned n)
{
    static int_unsigned values[FIB_LIMIT];
    int_unsigned        value;

    if (n >= FIB_LIMIT)
        return 0;
    
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    if (values[n])
        return values[n];
    else
    {
        value = fib(n - 1) + fib(n - 2);
        values[n] = value;

        return value;
    }
}