#include "why_lib.h"

#include <time.h>
#include <stdio.h>

int_signed inverse_string_compare(const String* lhs, const String* rhs)
{
    return -string_compare(lhs, rhs);
}

void merge_sort_test()
{
    Array* strings;

    strings = get_all_linesAFN("test_file.txt");
    // print_arrayN(strings, print_string, "\n");
    // printf("\n---------------\n");

    // array_sortM(strings, string_compare);
    array_sortH(strings, string_compare);
    // array_sortH(strings, inverse_string_compare);


    print_arrayN(strings, print_string, "\n");

    array_destroy(strings);
}

void _at_exit()
{
    get_line(-1);
}

int main()
{
    clock_t start;
    clock_t end;

    atexit(_at_exit);

    start = clock();

    merge_sort_test();

    end = clock();

    printf("Time elapsed: %f s\n", (end - start) / (double) CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}