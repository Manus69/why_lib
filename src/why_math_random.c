#include "why_definitions.h"
#include "why_math_random.h"
#include "why_math.h"
#include "why_memory.h"
#include "why_macros.h"

static int_unsigned rand_int = INITIAL_VALUE;

int_unsigned random_get()
{
    rand_int = (rand_int * SCALE_FACTOR + INCREMENT) % MODULUS;

    return rand_int;
}

void random_seed(int_unsigned seed)
{
    seed = seed < INITIAL_VALUE ? INITIAL_VALUE : seed;
    rand_int = seed % 2 == 0 ? seed + 1 : seed;
}

int_unsigned random_in_range(int_unsigned left, int_unsigned right)
{
    int_unsigned value;

    value = random_get() % (right - left);
    value += left;

    return value;

}

real random_chi_squared(int_unsigned seed, int_unsigned max_value, int_unsigned sample_size)
{
    int_unsigned    array[max_value % WHY_RAND_MAX];
    int_unsigned    value;
    int_unsigned    n;
    int_unsigned    size;
    real            sum;

    random_seed(seed);
    size = max_value % WHY_RAND_MAX;
    memory_set(array, 0, size * sizeof(int_unsigned));
    n = 0;

    while (n < sample_size)
    {
        value = random_get() % size;
        array[value] ++;
        n ++;
    }
    
    n = 0;
    sum = 0;
    while (n < size)
    {
        sum += array[n] * array[n];
        n ++;
    }

    return ((size * sum) / sample_size) - sample_size;
}

static real _max_diff(real max)
{
    real sqrt_max;

    sqrt_max = math_sqrt(max);

    return 2 * sqrt_max;
}

bool random_chi_squared_test(int_unsigned seed, int_unsigned max, int_unsigned sample_size)
{
    real chi;
    real diff;

    sample_size = sample_size < SAMPLE_SIZE_SCALE_FACTOR * max ? SAMPLE_SIZE_SCALE_FACTOR * max : sample_size;
    chi = random_chi_squared(seed, max, sample_size);
    diff = chi - max;

    return ABS(diff) <= _max_diff(max);
}