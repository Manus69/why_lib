#include "why_lib.h"
#include "why_hash_table_diagnostics.h"

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

    array_sortM(strings, string_compare);
    // array_sortH(strings, string_compare);
    // array_sortH(strings, inverse_string_compare);


    print_arrayN(strings, print_string, "\n");

    array_destroy(strings);
}

void queue_test()
{
    Heap*   queue;
    Array*  strings;
    String* string;

    strings = get_all_linesAFN("test_file.txt");
    queue = heap_create(copy_shallow, string_destroy, string_compare);

    // print_arrayN(strings, print_string, "\n");

    while (array_size(strings))
    {
        string = array_pop_front(strings);
        heap_push(queue, string);
    }

    while ((string = heap_pop_root(queue)))
    {
        print_stringN(string);
        string_destroy(string);
    }

    heap_destroy(queue);
    array_destroy(strings);
}

void hash_test()
{
    HashTable*  table;
    Array*      strings;
    String*     string;
    Array*      distribution;
    int_signed  unique_lines;

    strings = get_all_linesAFN("test_file.txt");
    table = hash_table_create(copy_shallow, string_destroy, hash_string, 30000);
    unique_lines = array_size(strings);

    while (array_size(strings))
    {
        string = array_pop(strings);
        if (!hash_table_insert(table, string, string_compare))
        {
            // print_stringN(string);
            if (string_length(string) > 1)
                print_stringN(string);
            string_destroy(string);
            unique_lines --;
        }
    }

    // print_hash_table(table, print_string);

    distribution = _hash_table_get_distribution(table);
    // print_distribution(distribution);
    // print_array(distribution, print_int_pointerN, " ");
    array_destroy(distribution);

    print_intN(unique_lines);

    array_destroy(strings);
    hash_table_destroy(table);
}

void string_test()
{
    String* string; 
    Array*  strings;

    string = string_create("0    1  xx");
    // print_string(string);

    strings = string_split(string, ' ');
    print_arrayN(strings, print_string, " ");
    array_destroy(strings);

    string_destroy(string);
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
    // queue_test();
    // hash_test();
    // string_test();
    // perfect_square_test();

    end = clock();

    printf("Time elapsed: %f s\n", (end - start) / (double) CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}