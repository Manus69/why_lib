#include "why_lib.h"
#include "why_hash_table_diagnostics.h"
#include "why_tree_diagnostics.h"

#include <time.h>
#include <stdio.h>

int_signed inverse_string_compare(const String* lhs, const String* rhs)
{
    return -string_compare(lhs, rhs);
}

int_signed compare_int(int_signed* lhs, int_signed* rhs)
{
    return *rhs - *lhs;
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

void merge_sort_number_test()
{
    Array* numbers;
    int_signed n;

    numbers = array_create(copy_int_signed, memory_destroy);
    n = 1000000;
    while (n)
    {
        array_push(numbers, &n);
        n --;
    }

    array_sortM(numbers, compare_int);

    // print_arrayN(numbers, print_int_pointerN, NULL);
    array_destroy(numbers);
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
            // if (string_length(string) > 1)
                // print_stringN(string);
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

void tree_test()
{
    const char* strings[] = {"a", "aa", "b", "c", "d", 0};
    Tree*       tree;
    char*       string;
    int         n;

    n = 0;
    tree = tree_create(copy_cstring, cstr_destroy, cstr_compare);
    // tree = tree_create_avl(copy_cstring, cstr_destroy, cstr_compare);
    while (strings[n])
    {
        tree_insert(tree, strings[n]);
        n ++;
    }

    print_treeN(tree, print_cstringS);

    n = 0;
    while (strings[n])
    {
        string = tree_remove(tree, strings[n]);
        print_cstringN(string);
        cstr_destroy(string);
        n ++;
    }

    // print_tree(tree, print_cstringS);

    tree_destroy(tree);
}

void tree_test_strings()
{
    Tree* tree;
    Array* strings;
    String* string;

    strings = get_all_linesAFN("test_file.txt");
    tree = tree_create_avl(copy_shallow, string_destroy, string_compare);
    while (array_size(strings))
    {
        string = array_pop(strings);
        if (!tree_insert(tree, string))
            string_destroy(string);
    }

    print_intN(tree_get_size(tree));
    array_destroy(strings);
    tree_destroy(tree);
}

void tree_test_numbers()
{
    Tree* tree;
    int_signed n;
    int_signed limit;

    tree = tree_create_avl(copy_int_signed, memory_destroy, compare_int);
    // tree = tree_create(copy_int_signed, memory_destroy, compare_int);

    n = 0;
    limit = 1000;

    while (n < limit)
    {
        tree_insert(tree, &n);
        //
        // tree_check_integrity(tree);
        // tree_check_avl_invariant(tree);
        //
        n ++;
    }

    print_treeN(tree, print_int_pointerN);
    print_intN(tree_compute_height(tree));

    n = 0;
    void* item;
    while (n < limit)
    {
        item = tree_remove(tree, &n);
        //
        // print_treeN(tree, print_int_pointerN);
        //
        // print_int_pointerN(item);
        memory_destroy(item);
        n ++;
    }

    tree_destroy(tree);
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

    // tree_test_numbers();
    // tree_test();
    // tree_test_strings();
    hash_test();
    // merge_sort_test();
    // merge_sort_number_test();
    // queue_test();
    // string_test();
    // perfect_square_test();

    end = clock();

    printf("Time elapsed: %f s\n", (end - start) / (double) CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}