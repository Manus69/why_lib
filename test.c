#include "why_lib.h"

#include <time.h>
#include <stdio.h>

//array default size

void _at_exit()
{
    get_line(-1);
}

int main()
{
    clock_t start;
    clock_t end;
    Array* strings;

    atexit(_at_exit);

    start = clock();

    strings = get_all_linesAFN("test_file.txt");
    print_arrayN(strings, print_string, "\n");

    array_destroy(strings);

    end = clock();

    printf("Time elapsed: %f s\n", (end - start) / (double) CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}