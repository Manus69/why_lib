#include "why_lib.h"
#include "why_hash_table_diagnostics.h"
#include "why_tree_diagnostics.h"
#include "why_math_complex.h"
#include "why_math_rational.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE (1 << 20)

int_signed inverse_string_compare(const String* lhs, const String* rhs)
{
    return -string_compare(lhs, rhs);
}

static Array* _get_unsorted_arrayINT(int_signed size)
{
    Array*      array;

    array = array_createINT(0);
    size --;
    while (size >= 0)
    {
        array_push(array, &size);
        size --;
    }

    return array;
}

static Array* _get_unsorted_arrayCPLX(int_signed size)
{
    Array*      array;
    Complex     z;

    array = array_createCPLX(0);
    size --;

    while (size >= 0)
    {
        z = complex(0, size);
        // print_complex_pointerN(&z);
        array_push(array, &z);
        
        // z = *(Complex *)array_last(array);

        size --;
    }

    return array;
}

static Array* _get_unsorted_arrayBYTE(int_signed size)
{
    Array*  array;
    byte    b;

    array = array_createBYTE(0);
    size --;

    random_seed(0);

    while (size >= 0)
    {
        b = random_get() % 256;
        // print_complex_pointerN(&z);
        array_push(array, &b);
        
        // z = *(Complex *)array_last(array);

        size --;
    }

    return array;
}

static Array* _get_unsorted_arrayREAL(int_signed size)
{
    Array*  array;
    real    x;

    array = array_createREAL(size);
    size --;

    while (size >= 0)
    {
        x = size;
        array_push(array, &x);
        size --;
    }

    return array;
}

static Array* _get_unsorted_arrayRAT(int_signed size)
{
    Array*      array;
    Rational    r;

    array = array_createRAT(size);

    while (size)
    {
        r = rational_random(1, 1000);
        // print_rationalN(r);
        array_push(array, &r);

        size --;
    }
    
    return array;
}

void array_test()
{
    Array* array;
    
    array = _get_unsorted_arrayINT(10);
    // print_arrayN(array, print_int_pointerN, NULL);

    array_sortM(array, compare_int);
    // print_arrayN(array, print_int_pointerN, NULL);
    print_real_pointerN(array_last(array));
    array_destroy(array);

    array = _get_unsorted_arrayCPLX(10);
    print_arrayN(array, print_complex_pointerN, NULL);
    array_sortM(array, compare_complex);
    print_arrayN(array, print_complex_pointerN, NULL);

    array_destroy(array);

    array = _get_unsorted_arrayBYTE(10);
    // print_arrayN(array, print_byte_pointerN, NULL);
    array_sortQ(array, compare_byte);
    // print_arrayN(array, print_byte_pointerN, NULL);
    print_real_pointerN(array_last(array));
    array_destroy(array);

    array = _get_unsorted_arrayREAL(10);
    // print_arrayN(array, print_real_pointerN, NULL);
    array_sortQ(array, compare_real);
    // print_array(array, print_real_pointerN, NULL);
    print_real_pointerN(array_last(array));
    array_destroy(array);

    array = _get_unsorted_arrayRAT(30);
    print_arrayN(array, print_rationalPN, "\n");
    array_sortI(array, rational_compare);
    print_arrayN(array, print_rationalPN, "\n");
    array_destroy(array);
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


    // print_arrayN(strings, print_string, "\n");
    print_stringN(array_last(strings));

    array_destroy(strings);
}

void merge_sort_number_test()
{
    Array* numbers;

    numbers = _get_unsorted_arrayINT(SIZE);
    // print_arrayN(numbers, print_int_pointerN, NULL);

    // Array* copy = array_copy(numbers);
    // print_arrayN(copy, print_int_pointerN, NULL);

    array_sortM(numbers, compare_int);

    // print_arrayN(numbers, print_int_pointerN, NULL);
    print_int_pointerN(array_last(numbers));
    array_destroy(numbers);
}

void quick_sort_test()
{
    Array* array;

    array = get_all_linesAFN("test_file.txt");
    String* string = array_at(array, 0);
    print_stringN(string);

    array_sortQ(array, string_compare);

    print_stringN(array_last(array));
    // print_arrayN(array, print_stringN, NULL);
    
    array_destroy(array);
    
}

void quick_sort_number_test()
{
    Array*     array;

    array = _get_unsorted_arrayINT(SIZE);

    int_signed n = *(int_signed *)array_at(array, 0);

    print_int(n);
    // print_arrayN(array, print_int_pointer, " ");
    array_sortQ(array, compare_int);

    print_int_pointerN(array_last(array));
    array_destroy(array);
}

void heap_sort_test()
{
    Array* array;

    // array = get_all_linesAFN("test_file.txt");
    // array_sortH(array, string_compare);

    // // print_string(array_last(array));
    // print_arrayN(array, print_stringN, NULL);

    // array_destroy(array);

    array = _get_unsorted_arrayINT(SIZE);
    // print_arrayN(array, print_int_pointerN, NULL);
    // array_sortH(array, compare_int);
    array_sortH(array, compare_int);
    print_int_pointerN(array_last(array));
    // print_arrayN(array, print_int_pointerN, NULL);
    array_destroy(array);
}

void queue_test()
{
    Heap*   queue;
    Array*  strings;
    String* string;

    strings = get_all_linesAFN("test_file.txt");
    //
    // print_arrayN(strings, print_stringN, NULL);
    //
    queue = heap_create(copy_shallow, string_destroy, string_compareINV);

    while (array_size(strings))
    {
        string = array_pop_front(strings);
        heap_push(queue, string);
    }

    array_destroy(strings);
    // print_heap(queue, print_stringN);

    while ((string = heap_pop_root(queue)))
    {
        print_stringN(string);
        string_destroy(string);
    }

    heap_destroy(queue);
}

void hash_test()
{
    HashTable*  table;
    Array*      strings;
    String*     string;
    Array*      distribution;
    int_signed  unique_lines;

    strings = get_all_linesAFN("test_file.txt");
    // print_arrayN(strings, print_stringN, NULL);
    table = hash_table_create(copy_shallow, string_destroy, hash_string, 20000);
    unique_lines = array_size(strings);

    while (array_size(strings))
    {
        string = array_pop(strings);
        // print_stringN(string);

        if (!hash_table_insert(table, string, string_compare))
        {
            // print_stringN(string);
            // if (string_length(string) > 1)
                // print_stringN(string);
            string_destroy(string);
            unique_lines --;
        }
    }

    print_hash_table(table, print_string);

    distribution = _hash_table_get_distribution(table);
    // print_distribution(distribution);
    print_array(distribution, print_int_pointerN, " ");
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

void random_test()
{
    bool chi_test;

    chi_test = random_chi_squared_test(0, 100000, 1000);

    printf("%d\n", chi_test);
}

void _at_exit()
{
    get_line(-1);
}

//MERGE SORT
int main()
{
    clock_t start;
    clock_t end;

    atexit(_at_exit);

    start = clock();

    tree_test_numbers();
    tree_test();
    tree_test_strings();
    hash_test();
    merge_sort_test();
    quick_sort_test();
    merge_sort_number_test();
    quick_sort_number_test();
    heap_sort_test();
    queue_test();
    string_test();
    random_test();
    array_test();

    end = clock();
    print_time_diff(start, end);

    return EXIT_SUCCESS;
}