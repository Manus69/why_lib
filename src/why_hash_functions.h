#ifndef WHY_HASH_FUNCTIONS_H
#define WHY_HASH_FUNCTIONS_H

#include "why_string_interface.h"

int_unsigned hash_bytesFL(const byte* bytes, int_signed length);
int_unsigned hash_cstringFL(const char* string, int_signed length);
int_unsigned hash_cstring(const char* string);
int_unsigned hash_string(const String* string);

#endif