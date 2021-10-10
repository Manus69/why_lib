#ifndef WHY_HASH_FUNCTIONS_H
#define WHY_HASH_FUNCTIONS_H

#include "why_string_interface.h"

int_unsigned hash_cstring(const byte* string);
int_unsigned hash_string(const String* string);

#endif