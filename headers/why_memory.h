#ifndef WHY_MEMORY_H
#define WHY_MEMORY_H

#include <cstdlib>

#define BITS_PER_BYTE 8

namespace why
{
    template <typename type>
    void swap(type &lhs, type &rhs)
    {
        type store;

        store = lhs;
        lhs = rhs;
        rhs = store;
    }

    void *copy_memory(const void *source, unsigned int number_of_bytes);
    void *get_n_zero_bytes(unsigned int number_of_bytes);
    void reproduce_memory(void *location, const void *source, unsigned int number_of_bytes);
    void *reallocate_memory(void *source, unsigned int number_of_bytes, unsigned int new_size);
}

#endif