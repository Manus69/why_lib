#include "why_conversion.h"
#include "why_cstring.h"
#include "why_error.h"
#include "why_string_interface.h"

#define BUFFER_CAPACITY (1 << 5)
#define DIGITS "0123456789abcdef"

String* convert_to_string_uintB(int_unsigned n, byte base)
{
    char        buffer[BUFFER_CAPACITY];
    int_signed  index;

    if (n == 0)
        return string_create("0");

    if (base > 16)
        return error_set(WHY_ERROR_CONV, NULL);
    
    // memory_set(buffer, 0, BUFFER_CAPACITY);
    index = 0;
    while (n)
    {
        buffer[index] = DIGITS[n % base];
        n = n / base;
        index ++;
    }

    return string_createFL_backwards(buffer + index - 1, index);
}

String* convert_to_string_uint(int_unsigned n)
{
    return convert_to_string_uintB(n, 10);
}