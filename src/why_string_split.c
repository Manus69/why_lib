#include "why_array_interface.h"
#include "why_string_interface.h"
#include "why_string_view_interface.h"
#include "why_string_view.h"
#include "why_copy.h"

#include "why_memory.h"
#include "why_cstring.h"

Array* cstr_split(const char* string, char delimiter)
{
    Array*      array;
    StringView  view;
    int_signed  index;
    char*       substring;

    array = array_create(copy_shallow, memory_destroy);
    string_view_initB(&view, string, cstr_length(string));

    while (string_view_length(&view))
    {
        index = string_view_index_of(&view, delimiter);
        if (index > 0)
            substring = string_view_substring_shiftCSTR(&view, index);
        else if (index == NOT_FOUND)
            substring = string_view_substring_shiftCSTRE(&view);
        else
        {
            // substring = cstr_copy("");
            string_view_shift(&view, 1);
            continue ;
        }
        array_push(array, substring);
    }

    return array;
}

Array* string_split(const String* string, char delimiter)
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
            element = string_view_substring_shift(&view, index);
        else if (index == NOT_FOUND)
            element = string_view_substring_shiftE(&view);
        else
        {
            // element = string_create("");
            string_view_shift(&view, 1);
            continue ;
        }
        array_push(array, element);
    }

    return array;
}

Array* string_splitCSTR(const char* c_string, char delimiter)
{
    String* string;
    Array*  array;

    string = string_create(c_string);
    array = string_split(string, delimiter);
    string_destroy(string);

    return array;
}