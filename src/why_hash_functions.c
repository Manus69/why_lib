#include "why_string_interface.h"

#define H_VALUE 5381

//this is some voodoo bullshit
int_unsigned hash_cstring(const byte* string)
{
    byte            byte;
    int_unsigned    hash_value;

    hash_value = H_VALUE;
    while ((byte = *string ++))
        hash_value = ((hash_value << 5) + hash_value) + byte;

    return hash_value;
}

int_unsigned hash_string(const String* string)
{
    byte            byte;
    int_unsigned    hash_value;
    int_signed      n;
    char*           characters;

    hash_value = H_VALUE;
    characters = string_get_characters(string);
    n = string_length(string);

    while (n)
    {
        byte = *characters ++;
        hash_value = ((hash_value << 5) + hash_value) + byte;
        n --;
    }

    return hash_value;
}