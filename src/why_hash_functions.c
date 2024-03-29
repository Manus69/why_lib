#include "why_lib.h"

#define H_VALUE 5381

//this is some voodoo bullshit
int_unsigned hash_bytesFL(const byte* bytes, int_signed length)
{
    int_unsigned    hash_value;

    hash_value = H_VALUE;
    while (length)
    {
        hash_value = ((hash_value << 5) + hash_value) + *bytes;

        length --;
        bytes ++;
    }

    return hash_value;
}

int_unsigned hash_cstringFL(const char* string, int_signed length)
{
    return hash_bytesFL((byte *)string, length);
}

int_unsigned hash_cstring(const char* string)
{
    int_signed length;

    if (!string)
        return 0;
    
    length = cstr_length(string);

    return hash_cstringFL(string, length);
}

int_unsigned hash_string(const String* string)
{
    int_signed length;

    if (!string)
        return 0;

    length = string_length(string);

    return hash_cstringFL(string_get_characters(string), length);
}