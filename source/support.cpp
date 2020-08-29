#include "why_string.h"
#include "why_math.h"
#include "limits.h"

namespace why
{
    String integer_to_string(long number, unsigned char base)
    {
        String number_string;
        String sign_string;
        unsigned char current_digit;
        long complement;

        if (base > 16)
            base = 10;
        complement = get_absolute_value(LONG_MAX - number + 1);
        if (number < 0)
        {
            if (base == 10)
            {
                sign_string = "-";
                number = -number;
            }
            else
                number = complement;
        }
        while (number)
        {
            current_digit = DIGITS[number % base];
            number_string.append(current_digit);
            number = number / base;
        }
        number_string.reverse();

        return sign_string.append(number_string);
    }

    unsigned int get_cstring_length(const char *string)
    {
        unsigned int n;

        n = 0;
        while (string[n] != 0)
            n ++;
        
        return n;
    }

}