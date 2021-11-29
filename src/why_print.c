#include "why_lib.h"
#include "why_math_complex.h"
#include "why_math_rational.h"

#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE (1 << 7)
#define TOLERANCE (1.0/10000)

void print_time_diff(clock_t start, clock_t end)
{
    printf("Time elapsed: %f sec.\n", ((double)(end - start) / CLOCKS_PER_SEC));
}

void print_int(int_signed n)
{
    printf("%lld", n);
}

void print_intN(int_signed n)
{
    print_int(n);
    printf("\n");
}

void print_int_pointer(int_signed* n)
{
    if (n)
        print_int(*n);
    else
        printf("(null)");
    
}

void print_int_pointerN(int_signed* n)
{
    print_int_pointer(n);
    printf("\n");
}

void print_uint(int_unsigned n)
{
    printf("%llu", n);
}

void print_byte(byte byte)
{
    printf("%u", byte);
}

void print_byte_pointer(byte* byte)
{
    print_byte(*byte);
}

void print_byte_pointerN(byte* byte)
{
    print_byte_pointer(byte);
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

void print_real_pointer(const real* x)
{
    if (!x)
        return ;
    
    print_real(*x);
}

void print_real_pointerN(const real* x)
{
    print_real_pointer(x);
    printf("\n");
}

void print_rational(Rational p)
{
    int_signed top;
    int_signed bot;

    p = rational_normalize(p);
    top = rational_get_top(p);
    bot = rational_get_bot(p);

    if (top == 0)
        return print_int(0);
    
    print_int(top);
    printf(" / ");
    print_int(bot);
}

void print_rationalN(Rational p)
{
    print_rational(p);
    printf("\n");
}

void print_rationalPN(const Rational* p)
{
    print_rational(*p);
    printf("\n");
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

void print_complexN(Complex z)
{
    print_complex(z);
    printf("/n");
}

void print_complex_pointer(const Complex* z)
{
    if (!z)
        return ;

    print_complex(*z);
}

void print_complex_pointerN(const Complex* z)
{
    print_complex_pointer(z);
    printf("\n");
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

void print_cstringS(const char* string)
{
    print_cstring(string);
    printf(" ");
}

void print_string(const String* string)
{
    if (!string)
        return ;

    printf("%s", string_get_characters(string));
}

//this is ugly and dangerous
void print_stringL(const String* string)
{
    char*       cstring;
    int_signed  length;

    if (!string)
        return ;

    cstring = string_get_characters(string);
    length = string_length(string);
    printf("%.*s", (int)length, cstring);
}

void print_stringN(const String* string)
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

void print_distribution(const Array* distribution)
{
    int_signed  n;
    int_signed* item;

    if (!distribution)
        return ;
    
    n = 0;
    while (n < array_size(distribution))
    {
        item = array_at(distribution, n);
        if (!item || *item <= 0)
        {
            printf("\n");
            n ++;

            continue ;
        }
        
        while (*item > 0)
        {
            *item = *item - 1;
            printf("#");
        }
        
        printf("\n");
        n ++;
    }
}

void print_hash_table_cell(const HashTable* table, void (*print)(), int_signed n)
{
    print_list(hash_table_at(table, n), print);
}

void print_hash_table(const HashTable* table, void (*print)())
{
    int_unsigned n;

    n = 0;
    while (n < hash_table_capacity(table))
    {
        print_list(hash_table_at(table, n), print);
        printf("\n");

        n ++;
    }
}

void print_heap(const Heap* heap, void (*print)())
{
    if (!heap)
        return ;
    
    if (array_size(heap) == 0)
        return ;
    
    print_array(heap, print, NULL);
}

void print_tree(const Tree* tree, void (*print)())
{
    return tree_map_inorder((Tree *)tree, print);
}

void print_treeN(const Tree* tree, void (*print)())
{
    print_tree(tree, print);
    printf("\n");
}

void print_set(const Set* set, void (*print)())
{
    printf("{ ");
    print_tree(set, print);
    printf(" }");
}

void print_setN(const Set* set, void (*print)())
{
    print_set(set, print);
    printf("\n");
}

void print_msegment(const MSegment* segment, void (*print)())
{
    int_signed  n;
    void*       value;

    if (!segment)
        return ;

    n = 0;
    while (n < msegment_get_size(segment))
    {
        value = msegment_get(segment, n);
        print(value);

        n ++;
    }
}