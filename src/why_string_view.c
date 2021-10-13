#include "why_string_view.h"
#include "why_string_view_interface.h"
#include "why_string_interface.h"
#include "why_cstring.h"

void string_view_init(StringView* view, const String* string)
{
    view->characters = string_get_characters(string);
    view->current = view->characters;
    view->length = string_length(string);
}

void string_view_initB(StringView* view, const char* buffer, int_signed length)
{
    view->characters = (char *)buffer;
    view->current = (char *)buffer;
    view->length = length;
}

void string_view_shift(StringView* view, int_signed shift)
{
    if (shift > view->length)
        shift = view->length;
    
    view->current += shift;
    view->length -= shift;
}

void string_view_rewind(StringView* view)
{
    view->length += (view->current - view->characters);
    view->current = view->characters;
}

int_signed string_view_length(const StringView* view)
{
    return view->length;
}

int_signed string_view_index_of(const StringView* view, char c)
{
    int_signed n;

    n = 0;
    while (n < view->length)
    {
        if (view->current[n] == c)
            return n;
        
        n ++;
    }

    return NOT_FOUND;
}

char* string_view_substringCSTR(StringView *view, int_signed length)
{
    if (length > view->length)
        length = view->length;

    return cstr_substring(view->current, length);
}

String* string_view_substring(StringView* view, int_signed length)
{
    if (length > view->length)
        length = view->length;
    
    return string_createFL(view->current, length);
}

char* string_view_substringCSTRE(StringView* view)
{
    return cstr_substring(view->current, view->length);
}

String* string_view_substringE(StringView* view)
{
    return string_createFL(view->current, view->length);
}

char* string_view_substring_shiftCSTR(StringView* view, int_signed length)
{
    char* substring;

    substring = string_view_substringCSTR(view, length);
    string_view_shift(view, length);

    return substring;
}

String* string_view_substring_shift(StringView* view, int_signed length)
{
    String* string;

    string = string_view_substring(view, length);
    string_view_shift(view, length);

    return string;
}

char* string_view_substring_shiftCSTRE(StringView* view)
{
    return string_view_substring_shiftCSTR(view, view->length);
}

String* string_view_substring_shiftE(StringView* view)
{
    return string_view_substring_shift(view, view->length);
}