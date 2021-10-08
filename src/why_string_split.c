#include "why_array_interface.h"
#include "why_string_interface.h"
#include "why_copy.h"

#include "why_memory.h"
#include "why_cstring.h"

Array* string_split(String* string, char delimiter)
{
    Array*      array;
    String*     element;
    int_signed  index;
    int_signed  length;

    array = array_create(copy_shallow, string_destroy);

    while ((length = string_length(string)))
    {
        index = string_index_of(string, delimiter);
        if (index > 0)
        {
            element = string_substring_allocated(string, 0, index);
            _string_shift(string, index + 1);
        }
        else if (index == NOT_FOUND)
        {
            element = string_substring_from_allocated(string, 0);
            _string_shift(string, length);
        }
        else
        {
            element = string_create("");
            _string_shift(string, 1);
        }
        array_push(array, element);
    }

    _string_rewind(string);
    return array;
}

Array* string_split_cstar(char* c_string, char delimiter)
{
    String* string;
    Array*  array;

    string = string_create(c_string);
    array = string_split(string, delimiter);
    string_destroy(string);

    return array;
}