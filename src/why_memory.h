
#ifndef WHY_MEMORY_H
#define WHY_MEMORY_H

#include <stdlib.h>

#include "why_definitions.h"

#ifdef __cplusplus
    extern "C" {
#endif
#ifdef __cplusplus
    void*   memory_init(void* destination, const void* source, int_unsigned size);
#else
    void*   memory_init(void* restrict destination, const void* restrict source, int_unsigned size);
#endif

void*   allocate(int_unsigned size);
void*   memory_set(void* object, byte value, int_unsigned size);
void*   reallocate(const void* item, int_unsigned current_size, int_unsigned extra_size);
void*   memory_zero(int_unsigned size);
void    memory_destroy(void* item);

#ifdef __cplusplus
    }
#endif

#endif
