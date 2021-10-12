#ifndef WHY_STRING_VIEW_INTERFACE_H
#define WHY_STRING_VIEW_INTERFACE_H

#include "why_definitions.h"
#include "why_string_interface.h"

typedef struct StringView StringView;

void string_view_init(StringView* view, const String* string);
void string_view_initB(StringView* view, char* buffer, int_signed length);
void string_view_shift(StringView* view, int_signed shift);
void string_view_rewind(StringView* view);
int_signed string_view_length(const StringView* view);
int_signed string_view_index_of(const StringView* view, char c);
String* string_view_substring(StringView* view, int_signed length);
String* string_view_substringE(StringView* view);
String* string_view_substring_shift(StringView* view, int_signed length);
String* string_view_substring_shiftE(StringView* view);

#endif
