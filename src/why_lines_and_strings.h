#ifndef WHY_LINES_AND_STRINGS_H
#define WHY_LINES_AND_STRINGS_H

#include "why_array_interface.h"
#include "why_string_interface.h"

#ifdef __cplusplus
    extern "C" {
#endif

Array*  string_split(String* string, char delimiter);
Array*  cstr_split(char* string, char delimiter);
Array*  get_all_linesA(int file_descriptor);
Array*  get_all_linesAFN(const char* file_name);
String* get_line(int file_descriptor);
String* get_all_lines(int file_descriptor);

#ifdef __cplusplus
    }
#endif

#endif