#include "why_lib.h"

int_signed cstr_length(const char* string)
{
    char* iterator;

    if (!string)
        return 0;

    iterator = (char* )string;
    while (*iterator)
        iterator ++;
    
    return iterator - string;    
}

char* cstr_substring(const char* string, int_unsigned length)
{
    char* substring;

    substring = allocate(length + 1);
    substring = memory_init(substring, string, length);
    substring[length] = '\0';

    return substring;
}

char* cstr_copy(const char* string)
{
    if (!string)
        return NULL;
    
    return cstr_substring(string, cstr_length(string));
}

void cstr_destroy(char* string)
{
    free(string);
}

int_signed cstr_compare_length(const char* lhs, const char* rhs, int_signed length)
{
    int_signed n;

    if (!lhs && !rhs)
        return 0;
    
    if (!rhs)
        return* lhs;
    if (!lhs)
        return* rhs;

    n = 0;
    while (n < length)
    {
        if (lhs[n] != rhs[n])
            return rhs[n] - lhs[n];
        
        n ++;
    }

    return 0;
}

int_signed cstr_compare(const char* lhs, const char* rhs)
{
    if (!lhs && !rhs)
        return 0;
    
    if (!rhs)
        return* lhs;
    if (!lhs)
        return* rhs;
    
    while (*lhs == *rhs && *lhs)
    {
        lhs ++;
        rhs ++;
    }

    return *rhs - *lhs;
}

char* cstr_concat_length(const char* lhs, int_signed lhs_len, const char* rhs, int_signed rhs_len)
{
    int_signed  total_len;
    char*       new_str;

    total_len = rhs_len + lhs_len;

    new_str = allocate(total_len + 1);
    
    memory_init(new_str, lhs, lhs_len);
    memory_init(new_str + lhs_len, rhs, rhs_len);
    new_str[total_len] = 0;

    return new_str;
}

char* cstr_concat(const char* lhs, const char* rhs)
{
    int_signed lhs_len;
    int_signed rhs_len;

    lhs_len = cstr_length(lhs);
    rhs_len = cstr_length(rhs);

    return cstr_concat_length(lhs, lhs_len, rhs, rhs_len);
}

int_signed cstr_index_of(const char* string, char c)
{
    int_signed n;

    n = 0;
    while (string[n])
    {
        if (string[n] == c)
            return n;
        n ++;
    }

    return NOT_FOUND;
}

int_signed cstr_index_of_any(const char* string, const char* set)
{
    int_signed n;

    n = 0;
    while (string[n])
    {
        if (cstr_index_of(set, string[n]) != NOT_FOUND)
            return n;
        
        n ++;
    }

    return NOT_FOUND;
}

static boolean _is_substring(const char* string, const char* substring)
{
    while (*substring && *string == *substring)
    {
        substring ++;
        string ++;
    }
    
    return *substring ? FALSE : TRUE;
}

int_signed cstr_index_of_substring(const char* haystack, const char* needle)
{
    int_signed n;

    n = 0;
    while (haystack[n])
    {
        if (_is_substring(&haystack[n], needle))
            return n;
        
        n ++;
    }

    return NOT_FOUND;
}

char cstr_char_to_lower(char c)
{
    if (id_upper(&c))
        return c + 'a' - 'A';
    
    return c;
}

void cstr_to_lower(char* string)
{
    int diff;

    if (!string)
        return;
    
    diff = 'a' - 'A';
    while (*string)
    {
        if (id_upper(string))
            *string = *string + diff;
        
        string ++;
    }
}

static char* _trim_left(const char* string)
{
    while (*string && id_whitespace(string))
        string ++;

    return cstr_copy(string);
}

char* cstr_trim(const char* string)
{
    char*       new_string;
    int_signed  length;

    new_string = _trim_left(string);
    length = cstr_length(new_string);
    length --;

    while (length >= 0)
    {
        if (!id_whitespace(new_string + length))
            break ;
        
        new_string[length] = '\0';
        length --;
    }

    return new_string;
}

boolean cstr_starts_with(const char*  restrict string, const char*  restrict start)
{
    if (!start)
        return FALSE;
    
    if (!*start)
        return TRUE;
    
    while (*string && *start)
    {
        if (*string == *start)
        {
            string ++;
            start ++;
        }
        else return FALSE;
    }

    return *start ? FALSE : TRUE;
}