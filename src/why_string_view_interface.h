#ifndef WHY_STRING_VIEW_INTERFACE_H
#define WHY_STRING_VIEW_INTERFACE_H

#include "why_definitions.h"
#include "why_string_interface.h"

typedef struct StringView StringView;

void        string_view_init(StringView* view, const String* string);
void        string_view_initB(StringView* view, const char* buffer, int_signed length);
void        string_view_shift(StringView* view, int_signed shift);
void        string_view_shrink(StringView* view, int_signed amount);
void        string_view_rewind(StringView* view);
int_signed  string_view_length(const StringView* view);
int_signed  string_view_index_of(const StringView* view, char c);
bool        string_view_starts_with(const StringView* view, char c);
bool        string_view_starts_with_any(const StringView* view, const char* set);
bool        string_view_ends_with_any(const StringView* view, const char* set);
bool        string_view_ends_with(const StringView* view, char c);
String*     string_view_substring(StringView* view, int_signed length);
String*     string_view_substringE(StringView* view);
String*     string_view_substring_shift(StringView* view, int_signed length);
String*     string_view_substring_shiftE(StringView* view);
char*       string_view_substringCSTR(StringView *view, int_signed length);
char*       string_view_substringCSTRE(StringView* view);
char*       string_view_substring_shiftCSTR(StringView* view, int_signed length);
char*       string_view_substring_shiftCSTRE(StringView* view);

#endif
