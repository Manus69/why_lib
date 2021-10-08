
#include "why_cstring.h"
#include "why_array_interface.h"
#include "why_copy.h"

Array* cstr_split(char* string, char delimiter)
{
    Array*      array;
    int_signed  index;
    int_signed  length;
    char*       substring;

    array = array_create(copy_shallow, memory_destroy);

    while (*string)
    {
        index = cstr_index_of(string, delimiter);
        if (index > 0)
        {
            substring = cstr_substring(string, index);
            string += index + 1;
        }
        else if (index == 0)
        {
            substring = cstr_copy("");
            string ++;
        }
        else
        {
            length = cstr_length(string);
            substring = cstr_substring(string, length);
            string += length;
        }

        array_push(array, substring);
    }

    return array;
}