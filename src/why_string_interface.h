#ifndef WHY_STRING_INTERFACE_H
#define WHY_STRING_INTERFACE_H

#include "why_definitions.h"

typedef struct String String;

#ifdef __cplusplus
    extern "C" {
#endif

void        _string_init(String* string, const char* literal, int_signed length, unsigned char allocated);
void        _string_init_copy(String* lhs, const String* rhs);
void        _string_set_allocation(String* string, byte allocated);
char        string_at(const String* string, int_signed n);
char*       string_get_characters(const String* string);
char*       string_slice(const String* string, int_signed length);
char*       string_slice_index(const String* string, int_signed left_index, int_signed length);
int_signed  _string_shift(String* string, int_signed shift);
int_signed  _string_rewind(String* string);
int_signed  string_length(const String* string);
int_signed  string_compare(const String* lhs, const String* rhs);
int_signed  string_compare_length(const String* lhs, const String* rhs, int_signed length);
bool        string_is_identical(const String* lhs, const String* rhs);
bool        string_is_identical_to(const String* string, const char* characters);
bool        string_starts_with(const String* string, const char* start);
String*     string_create_fixed_length(const char* literal, int_signed length);
String*     string_create(const char* literal);
String*     string_create_allocated_fl(const char* literal, int_signed length);
String*     string_create_allocated(const char* literal);
String*     string_append_literal(String* string, const char* rhs);
String*     string_append_string(String* string, const String* rhs);
String*     string_copy_shallow(const String* string);
String*     string_copy_semideep(const String* string);
String*     string_copy_deep(const String* string);
String*     string_substring(const String* string, int_signed left_index, int_signed length);
String*     string_substring_allocated(const String* string, int_signed left_index, int_signed length);
String*     string_substring_from(const String* string, int_signed left_index);
String*     string_substring_from_allocated(const String* string, int_signed left_index);
String*     string_remove_spaces(String* string);
String*     string_substitute_chars(String* string, const char* set, char replacement);
String*     string_to_lower(String* string);
String*     string_trim(String* string);
String*     string_skip_spaces(String* string);
void        string_destroy(String* string);

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
