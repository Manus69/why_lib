
#ifndef WHY_PRINT_H
#define WHY_PRINT_H

#include "why_definitions.h"
#include "why_array_interface.h"
#include "why_math_complex.h"
#include "why_string_interface.h"
#include "why_list_interface.h"
#include "why_hash_table_interface.h"
#include "why_tree_interface.h"

#define TOLERANCE (1.0/10000)

#ifdef __cplusplus
    extern "C" {
#endif

void print_int(int_signed n);
void print_intN(int_signed n);
void print_int_pointer(int_signed* n);
void print_int_pointerN(int_signed* n);
void print_real(real x);
void print_complex(Complex z);
void print_cstring(const char* string);
void print_cstringN(const char* string);
void print_string(const String* string);
void print_stringN(const String* string);
void print_cstringS(const char* string);
void print_stringL(const String* string);
void print_polynomial(const Polynomial* p);
void print_polynomial_with_rhs(const Polynomial* p);
void _print_polynomialDBG(const Polynomial* p);
void print_array(const Array* array, void (*print)(), const char* separator);
void print_arrayN(const Array* array, void (*print)(), const char* separator);
void print_list(const List* list, void (*function)());
void print_distribution(const Array* distribution);
void print_hash_table(const HashTable* table, void (*print)());
void print_hash_table_cell(const HashTable* table, void (*print)(), int_signed n);
void print_heap(const Heap* heap, void (*print)());
void print_tree(const Tree* tree, void (*print)());
void print_treeN(const Tree* tree, void (*print)());
void print_set(const Set* set, void (*print)());
void print_setN(const Set* set, void (*print)());

#ifdef __cplusplus
    }
#endif

#endif