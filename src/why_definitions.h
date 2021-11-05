#ifndef WHY_DEFINITIONS_H
#define WHY_DEFINITIONS_H

#include <limits.h>
#include <stdbool.h>

#define FALSE       0
#define TRUE        1
#define NOT_FOUND   -1
#define SUCCESS     1
#define FAILURE     0
#define WHY_INT_MAX LLONG_MAX

typedef unsigned long long  int_unsigned;
typedef long long           int_signed;
typedef unsigned char       byte;
typedef long double         real;
typedef unsigned char       boolean;

typedef struct Array Array;
typedef struct Buffer Buffer;
typedef struct HashTable HashTable;
typedef struct HashTable Set;
typedef struct Array Heap;
typedef struct List List;
typedef struct Polynomial Polynomial;
typedef struct String String;
typedef struct StringView StringView;
typedef struct Tree Tree;

#endif
