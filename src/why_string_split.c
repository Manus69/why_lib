#include "why_array_interface.h"
#include "why_string_interface.h"
#include "why_string_view_interface.h"
#include "why_string_view.h"
#include "why_copy.h"

#include "why_memory.h"
#include "why_cstring.h"

Array* string_split(String* string, char delimiter)
{
    Array*      array;
    String*     element;
    StringView  view;
    int_signed  index;

    array = array_create(copy_shallow, string_destroy);
    string_view_init(&view, string);

    while (string_view_length(&view))
    {
        index = string_view_index_of(&view, delimiter);
        if (index > 0)
        {
            element = string_view_substring_shift(&view, index);

            // element = string_substring(string, 0, index);
            // _string_shift(string, index + 1);
        }
        else if (index == NOT_FOUND)
        {
            element = string_view_substring_shiftE(&view);

            // element = string_substring_end(string, 0);
            // _string_shift(string, length);
        }
        else
        {
            element = string_create("");
            string_view_shift(&view, 1);
        }
        array_push(array, element);
    }

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