#ifndef WHY_STRING_VIEW_H
#define WHY_STRING_VIEW_H

#include "why_definitions.h"

struct StringView
{
    char*       characters;
    char*       current;
    int_signed  length;
};

#endif