#include "why_lib.h"

namespace why
{
    void *copy_memory(const void *source, unsigned int number_of_bytes)
    {
        unsigned int byte_number;
        unsigned char *current_byte_pointer;
        unsigned char *copy;

        copy = (unsigned char *)std::malloc(number_of_bytes);
        if (!copy)
            return NULL;
        byte_number = 0;
        current_byte_pointer = (unsigned char *)source;
        while (byte_number < number_of_bytes)
        {
            copy[byte_number] = *current_byte_pointer;
            byte_number ++;
            current_byte_pointer ++;
        }

        return (void *)copy;
    }

    void reproduce_memory(void *location, const void *source, unsigned int number_of_bytes)
    {
        unsigned int byte_number;
        unsigned char *location_pointer;
        unsigned char *source_pointer;

        byte_number = 0;
        location_pointer = (unsigned char *)location;
        source_pointer = (unsigned char *)source;
        while (byte_number < number_of_bytes)
        {
            *location_pointer = *source_pointer;
            location_pointer ++;
            source_pointer ++;
            byte_number ++;
        }

    }

    void *reallocate_memory(void *source, unsigned int number_of_bytes, unsigned int new_size)
    {
        unsigned char *copy;

        if (new_size < number_of_bytes)
            number_of_bytes = new_size;
        copy = (unsigned char *)std::malloc(new_size);
        if (!copy)
            return NULL;
        reproduce_memory(copy, source, number_of_bytes);
        std::free(source);

        return (void *)copy;        
    }

    void *get_n_zero_bytes(unsigned int number_of_bytes)
    {
        unsigned int n;
        unsigned char *bytes;

        bytes = (unsigned char *)std::malloc(number_of_bytes);
        if (!bytes)
            return NULL;
        n = 0;
        while (n < number_of_bytes)
        {
            bytes[n] = 0;
            n ++;
        }

        return (void *)bytes;
    }

    
}