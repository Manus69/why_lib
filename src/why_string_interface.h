#ifndef WHY_STRING_INTERFACE_H
#define WHY_STRING_INTERFACE_H

#include "why_definitions.h"

typedef struct String String;

#ifdef __cplusplus
    extern "C" {
#endif

String*     string_createFL(const char* literal, int_signed length);
String*     string_create(const char* literal);
int_signed  string_length(const String* string);
char        string_at(const String* string, int_signed n);
void        string_set(String* string, char value, int_signed index);
char*       string_get_characters(const String* string);
void        string_destroy(String* string);
String*     string_copy(const String* string);
String*     string_appendC(String* string, const char* rhs);
String*     string_appendS(String* string, const String* rhs);
String*     string_copy_shallow(const String* string);
int_signed  string_compare(const String* lhs, const String* rhs);
int_signed  string_compare_length(const String* lhs, const String* rhs, int_signed length);
String*     string_substring(const String* string, int_signed left_index, int_signed length);
String*     string_substring_end(const String* string, int_signed left_index);
String*     string_substitute_chars(String* string, const char* set, char replacement);
String*     string_to_lower(String* string);
bool        string_starts_with(const String* string, const char* start);
char*       string_slice_index(const String* string, int_signed left_index, int_signed length);
char*       string_slice(const String* string, int_signed length);

//search
int_signed  string_index_of_predicate(const String* string, int_signed start, char c, bool (*predicate)(char, char));
int_signed  string_index_of_from(const String* string, int_signed start, char c);
int_signed  string_index_of(const String* string, char c);
int_signed  string_index_of_compliment_from(const String* string, int_signed start, char c);
int_signed  string_index_of_any(const String* string, char* characters);
int_signed  string_find(const String* haystack, const String* needle);
int_signed  string_find_literal(const String* haystack, const char* needle);

#ifdef __cplusplus
    }
#endif

#endif
