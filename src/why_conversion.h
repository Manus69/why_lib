#ifdef __cplusplus
    extern "C" {
#endif

#ifndef WHY_CONVERSION_H
#define WHY_CONVERSION_H

#include "why_math_complex.h"
#include "why_string_interface.h"

int_signed  convert_to_int(const char* string);
int_signed  convert_to_intS(const String* string);
real        convert_to_real(const char* string);
Complex     convert_to_complex(const char* string);

String*     convert_to_string_uintB(int_unsigned n, byte base);
String*     convert_to_string_uint(int_unsigned n);


#endif

#ifdef __cplusplus
    }
#endif