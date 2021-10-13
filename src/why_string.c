#include "why_string.h"
#include "why_string_interface.h"
#include "why_memory.h"
#include "why_cstring.h"
#include "why_macros.h"

// #define DBG
#ifdef DBG
    #include <stdio.h>
#endif

void _string_init(String* string, const char* literal, int_signed length)
{
    string->characters = memory_init(string->characters, literal, length);
    string->characters[length] = '\0';
    string->length = length;
}

void _string_init_backwards(String* string, const char* literal, int_signed length)
{
    string->characters = memory_init_backwards(string->characters, literal, length);
    string->characters[length] = '\0';
    string->length = length;
}

static int_signed _compute_size(int_signed length)
{
    return sizeof(String) + sizeof(char) * (length + 1);
}

static int_signed _compute_total_size(const String* string)
{
    return _compute_size(string_length(string));
}

String* string_createFL(const char* literal, int_signed length)
{
    String* string;

    #ifdef DBG
        printf("literal: \"%.*s\" allocating %lld bytes\n", (int)length, literal, _compute_size(length));
    #endif

    string = allocate(_compute_size(length));
    string->characters = (char *)string + sizeof(String);
    _string_init(string, literal, length);

    return string;
}

String* string_createFL_backwards(const char* literal_end, int_signed length)
{
    String* string;

    string = allocate(_compute_size(length));
    string->characters = (char *)string + sizeof(String);
    _string_init_backwards(string, literal_end, length);

    return string;
}

String* string_create(const char* literal)
{
    int_signed length;

    length = cstr_length(literal);

    if (length < 0)
        return NULL;

    return string_createFL(literal, length);
}

int_signed string_length(const String* string)
{
    return string->length;
}

char string_at(const String* string, int_signed n)
{
    return string->characters[n];
}

void string_set(String* string, char value, int_signed index)
{
    string->characters[index] = value;
}

char* string_get_characters(const String* string)
{
    if (!string)
        return NULL;

    return string->characters;
}

void string_destroy(String* string)
{
    if (!string)
        return ;

    free(string);
}

String* string_copy(const String* string)
{
    String* new_string;
    int_signed size;

    size = _compute_total_size(string);
    new_string = allocate(size);
    new_string = memory_init(new_string, string, size);

    return new_string;
}

static String* _append(String* string, const char* rhs, int_signed length)
{
    String*     new_string;
    int_signed  new_size;
    int_signed  old_size;

    old_size = _compute_total_size(string);
    new_size = old_size + length;
    new_string = reallocate(string, old_size, length);

    memory_init(new_string->characters + old_size - 1, rhs, length);
    new_string->characters[new_size] = '\0';
    new_string->length = string_length(string) + length;
    string_destroy(string);

    return new_string;
}

String* string_appendC(String* string, const char* rhs)
{
    int_signed length;

    length = cstr_length(rhs);

    if (!length)
        return string_copy(string);

    return _append(string, rhs, length);
}

String* string_appendS(String* string, const String* rhs)
{
    char* characters;

    if (!rhs)
        return string;
    
    characters = string_get_characters(rhs);

    return _append(string, characters, string_length(rhs));
}

String* string_copy_shallow(const String* string)
{
    return (String *)string;
}

int_signed string_compare(const String* lhs, const String* rhs)
{
    if (!lhs && !rhs)
        return 0;

    if (!lhs)
        return 1;
    
    if (!rhs)
        return -1;

    return cstr_compare(lhs->characters, rhs->characters);
}

int_signed string_compare_length(const String* lhs, const String* rhs, int_signed length)
{
    int_signed lhs_length;
    int_signed rhs_length;

    if (!length)
    {
        lhs_length = string_length(lhs);
        rhs_length = string_length(rhs);
        length = MIN(lhs_length, rhs_length);
    }

    return cstr_compare_length(lhs->characters, rhs->characters, length);
}

String* string_substring(const String* string, int_signed left_index, int_signed length)
{
    return string_createFL(string->characters + left_index, length);
}

String* string_substring_end(const String* string, int_signed left_index)
{
    int_signed length;

    length = string_length(string) - left_index;
    if (length < 0)
        return NULL;
    
    return string_createFL(string->characters + left_index, length);
}

String* string_substitute_chars(String* string, const char* set, char replacement)
{
    char*       characters;
    int_signed  n;
    int_signed  index;

    characters = string_get_characters(string);
    n = 0;
    while (characters[n])
    {
        index = cstr_index_of(set, characters[n]);
        if (index != NOT_FOUND)
            characters[n] = replacement;

        n ++;
    }

    return string;
}

String* string_to_lower(String* string)
{
    cstr_to_lower(string->characters);

    return string;
}

bool string_starts_with(const String* string, const char* start)
{
    return cstr_starts_with(string_get_characters(string), start);
}

char* string_slice_index(const String* string, int_signed left_index, int_signed length)
{
    int_signed  _length;

    _length = string_length(string);
    if (length + left_index > _length)
        length = _length - left_index;

    return cstr_substring(string->characters + left_index, length);
}

char* string_slice(const String* string, int_signed length)
{
    return string_slice_index(string, 0, length);
}