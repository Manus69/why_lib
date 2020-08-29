#ifndef WHY_LIB_H
#define WHY_LIB_H

#include "why_memory.h"
#include "why_string.h"
// #include "why_structures.h"
#include "why_stack.h"

namespace why
{

    //display?
    String represent_byte(unsigned char byte);
    String represent_object(void *object, unsigned int size);
    void print_thing(void *thing, char type);

    //support
    String integer_to_string(long number, unsigned char base = 10);
    
}

#endif