#include "why_lib.h"

namespace why
{
    String represent_byte(unsigned char byte)
    {
        char bits[BITS_PER_BYTE];
        unsigned char mask;
        unsigned int n;

        mask = 1 << (BITS_PER_BYTE - 1);
        n = 0;
        while (n < BITS_PER_BYTE)
        {
            if (mask & byte)
                bits[n] = '1';
            else
                bits[n] = '0';
            n ++;
            mask = mask >> 1;
        }

        return String(bits);
    }

    //assumes that the lowest byte comes first
    String represent_object(void *object, unsigned int size)
    {
        unsigned char *current_byte;
        unsigned int byte_number;
        String byte_representation;
        String object_representation;

        current_byte = (unsigned char *)object;
        byte_number = 0;
        while (byte_number < size)
        {
            byte_representation = represent_byte(*current_byte);
            object_representation = why::concatenate(byte_representation, object_representation, ' ');
            current_byte ++;
            byte_number ++;
        }

        return object_representation;
    }
}