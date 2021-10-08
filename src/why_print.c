#include "why_print.h"
#include "why_cstring.h"
#include "why_error.h"

#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE (1 << 7)

void print_int(int_signed n)
{
    printf("%lld", n);
}

void print_int_pointerN(int_signed* n)
{
    print_int(*n);
    printf("\n");
}

static void _print_number_string(char* string)
{
    int_signed n;
    int_signed index_of_dot;

    index_of_dot = cstr_index_of(string, '.');
    if (index_of_dot == NOT_FOUND)
    {
        printf("%s", string);
        return ;
    }

    n = cstr_length(string) - 1;
    while (n)
    {
        if (string[n] != '0')
            break ;
        
        n --;
    }

    n == index_of_dot ? n : n ++;
    string[n] = 0;
    printf("%s", string);
}

void print_real(real x)
{
    char* buffer;

    if (x < 0)
    {
        if (!within_delta(0, -x, TOLERANCE))
            printf("-");
        print_real(-x);

        return ;
    }

    if (x == 0)
        printf("0");
    else if (absolute_value(x - round_to_int(x)) < TOLERANCE)
        printf("%.0Lf", x);
    else if (!WHY_ERROR)
    {
        buffer = memory_zero(BUFFER_SIZE);
        sprintf(buffer, "%Lf", x);
        _print_number_string(buffer);
        cstr_destroy(buffer);
    }
}

void print_complex(Complex z)
{
    if (z.im == 0)
    {
        print_real(z.re);
        return ;
    }
    if (z.re)
    {
        printf("(");
        print_real(z.re);
        if (z.im < 0)
            printf(" - ");
        else
            printf(" + ");
        if (z.im != 1 && z.im != -1)
            print_real(absolute_value(z.im));
        printf("i");
        printf(")");

        return ;
    }

    if (within_delta(z.im, -1, TOLERANCE))
        printf("-");
    else if (!within_delta(z.im, 1, TOLERANCE))
        print_real(z.im);

    printf("i");
}

void print_cstring(const char* string)
{
    printf("%s", string);
}

void print_cstringN(const char* string)
{
    print_cstring(string);
    printf("\n");
}

//this is ugly and dangerous
void print_string(const String* string)
{
    char*       cstring;
    int_signed  length;

    if (!string)
        return ;

    cstring = string_get_characters(string);
    length = string_length(string);
    printf("%.*s", (int)length, cstring);
}

void print_string_n(const String* string)
{
    print_string(string);
    printf("\n");
}

void print_array(const Array* array, void (*print)(), const char* separator)
{
    int_signed  n;
    int_signed  size;
    void*       item;

    if (!array)
        return ;

    size = array_size(array);
    item = array_at(array, 0);
    print(item);

    n = 1;
    while (n < size)
    {
        if (separator)
            printf("%s", separator);
        
        item = array_at(array, n);
        print(item);

        n ++;
    }
}

void print_arrayN(const Array* array, void (*print)(), const char* separator)
{
    print_array(array, print, separator);
    printf("\n");
}

void print_list(const List* list, void (*function)())
{
    return list_map((List *)list, function);
}
